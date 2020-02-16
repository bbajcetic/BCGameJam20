/*
** listener.c -- a datagram sockets "server" demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdbool.h>
#include <fcntl.h>
#include <time.h>
#include "custom.h"

#define MYPORT "4950"	// the port users will be connecting to

#define MAXBUFLEN 100

struct networkInfo {
    int sockfd;
    struct addrinfo* netInfo;
    struct sockaddr_storage client_addr;
};
struct networkInfo connection;

void connect() {
	struct addrinfo *p, hints, *servinfo;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	int rv;
	if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		exit(1);
	}

	// loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((connection.sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("listener: socket");
			continue;
		}
        if ((rv = fcntl(connection.sockfd, F_SETFL, O_NONBLOCK)) == -1) {
			perror("listener: fcntl");
			continue;
        }

		if (bind(connection.sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(connection.sockfd);
			perror("listener: bind");
			continue;
		}

		break;
	}
	freeaddrinfo(servinfo);

	if (p == NULL) {
		fprintf(stderr, "listener: failed to bind socket\n");
		exit(2);
	}
}

int main(void)
{
    connect();

	char buf[MAXBUFLEN];

	socklen_t addr_len = sizeof(connection.client_addr);
    //get client's address info
	int numbytes;
    do {
        numbytes = recvfrom(connection.sockfd, buf, MAXBUFLEN-1 , 0, (struct sockaddr *)&connection.client_addr, &addr_len);
    } while(numbytes == -1);

    int msg_no = 0;

    char msg[1024];
    strcpy(msg, "Hello from server ");
    snprintf(msg+strlen(msg), 1024, "%d\n", msg_no);

    while (true) {
	    struct sockaddr_storage temp;
        socklen_t temp_len;

        msg_no++;
        printf("About to send: %s\n", msg);

	    while ((numbytes = recvfrom(connection.sockfd, buf, MAXBUFLEN-1 , 0, (struct sockaddr *)&temp, &temp_len)) != -1) {
	        buf[numbytes] = '\0';
	        printf("listener: packet contains \"%s\"\n", buf);
	    }
        if (errno != EAGAIN && errno != EWOULDBLOCK) {
	    	perror("recvfrom");
        }


	    if ((numbytes = sendto(connection.sockfd, msg, strlen(msg), 0,
	    		 (const struct sockaddr *)&connection.client_addr, sizeof(connection.client_addr))) == -1) {
	    	perror("listener: sendto");
	    }

	    printf("listener: sent %d bytes\n", numbytes);

        wait(0, 10000);
    }


	close(connection.sockfd);

	return 0;
}

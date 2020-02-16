/*
** talker.c -- a datagram "client" demo
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

#define SERVERPORT "4950"	// the port users will be connecting to
#define MAXBUFLEN 100

struct networkInfo {
    int sockfd;
    struct addrinfo* netInfo;
    char server_ip[20];
};
struct networkInfo connection;

void connect() {
	struct addrinfo *p, hints, *servinfo;
    strcpy(connection.server_ip, "127.0.0.1");
    //strcpy(connection.server_ip, "206.87.203.1");

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

    int rv;
	if ((rv = getaddrinfo(connection.server_ip, SERVERPORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		exit(1);
	}

	// loop through all the results and make a socket
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((connection.sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("talker: socket");
			continue;
		}

        if ((rv = fcntl(connection.sockfd, F_SETFL, O_NONBLOCK)) == -1) {
			perror("listener: fcntl");
			continue;
        }

		break;
	}
	freeaddrinfo(servinfo);

	if (p == NULL) {
		fprintf(stderr, "talker: failed to create socket\n");
		exit(2);
	}
    connection.netInfo = p;
}
int main(int argc, char *argv[])
{
    connect();

    char first_msg[] = "client connect\n";
	int numbytes;
	if ((numbytes = sendto(connection.sockfd, first_msg, strlen(first_msg), 0,
			 connection.netInfo->ai_addr, connection.netInfo->ai_addrlen)) == -1) {
		perror("talker: sendto");
	}

    int msg_no = 0;
	char buf[MAXBUFLEN];

    char msg[1024];
    strcpy(msg, "Hello from client ");
    snprintf(msg+strlen(msg), 1024, "%d\n", msg_no);

    while (true) {
        msg_no++;
        printf("About to send: %s\n", msg);

	    if ((numbytes = sendto(connection.sockfd, msg, strlen(msg), 0,
	    		 connection.netInfo->ai_addr, connection.netInfo->ai_addrlen)) == -1) {
	    	perror("talker: sendto");
	    }
	    printf("talker: sent %d bytes\n", numbytes);

	    struct sockaddr_storage their_addr;
	    socklen_t addr_len = sizeof(their_addr);
	    while ((numbytes = recvfrom(connection.sockfd, buf, MAXBUFLEN-1 , 0, (struct sockaddr *)&their_addr, &addr_len)) != -1) {
	        buf[numbytes] = '\0';
	        printf("talker: packet = \"%s\"\n", buf);
	    }
        if (errno != EAGAIN && errno != EWOULDBLOCK) {
	    	perror("recvfrom");
        }

        wait(0, 10000);

    }

	close(connection.sockfd);

	return 0;
}

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
#include "server.h"

#define MYPORT "4950"	// the port users will be connecting to

#define MAXBUFLEN 100

static struct networkInfo connection;

void Server_initialize() {
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

void Server_connect() {
	char buf[MAXBUFLEN];
	socklen_t addr_len = sizeof(connection.client_addr);
    int numbytes;
    //get client's address info
    do {
        numbytes = recvfrom(connection.sockfd, buf, MAXBUFLEN-1 , 0, (struct sockaddr *)&connection.client_addr, &addr_len);
    } while(numbytes == -1);
}

int Server_receive(char* buf, int max_buf) {
	struct sockaddr_storage temp;
    socklen_t temp_len;
	int numbytes = recvfrom(connection.sockfd, buf, max_buf-1 , 0, (struct sockaddr *)&temp, &temp_len);
    return numbytes;
}

int Server_send(char* buf) {
    int numbytes = sendto(connection.sockfd, buf, strlen(buf), 0, 
            (const struct sockaddr *)&connection.client_addr, sizeof(connection.client_addr));
    return numbytes;
}

int main(void)
{
    Server_initialize();

    Server_connect();

    int msg_no = 0;

	char buf[MAXBUFLEN];
    char msg[1024];
	int numbytes;
    strcpy(msg, "Hello from server ");
    snprintf(msg+strlen(msg), 1024, "%d\n", msg_no);

    while (true) {

        msg_no++;
        printf("Sending: %s\n", msg);

        while ((numbytes = Server_receive(buf, MAXBUFLEN)) != -1) {
	        buf[numbytes] = '\0';
	        printf("Receiving: %s\n", buf);
	    }
        if (errno != EAGAIN && errno != EWOULDBLOCK) {
	    	perror("recvfrom");
        }


        if ((numbytes = Server_send(msg)) == -1) {
	    	perror("listener: sendto");
	    }

        wait(0, 10000);
    }


	close(connection.sockfd);

	return 0;
}

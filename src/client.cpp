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
#include "client.h"

#define SERVERPORT "4950"	// the port users will be connecting to
#define MAXBUFLEN 100

static struct networkInfo connection;

void Client_initialize() {
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

void Client_connect() {
    char first_msg[] = "Sending connection request\n";
	int numbytes;
	if ((numbytes = sendto(connection.sockfd, first_msg, strlen(first_msg), 0,
			 connection.netInfo->ai_addr, connection.netInfo->ai_addrlen)) == -1) {
		perror("talker: sendto");
	}
}

int Client_receive(char* buf, int max_buf) {
	struct sockaddr_storage temp;
	socklen_t temp_len = sizeof(temp);
	int numbytes = recvfrom(connection.sockfd, buf, max_buf-1 , 0, (struct sockaddr *)&temp, &temp_len);
    return numbytes;
}

int Client_send(char* buf) {
	int numbytes = sendto(connection.sockfd, buf, strlen(buf), 0,
            connection.netInfo->ai_addr, connection.netInfo->ai_addrlen);
    return numbytes;
}

int main(int argc, char *argv[])
{
    Client_initialize();

    Client_connect();


    int msg_no = 0;

	char buf[MAXBUFLEN];
    char msg[1024];
	int numbytes;
    strcpy(msg, "Hello from client ");
    snprintf(msg+strlen(msg), 1024, "%d\n", msg_no);

    while (true) {
        msg_no++;
        printf("Sending: %s\n", msg);

	    if ((numbytes = Client_send(msg)) == -1) {
	    	perror("talker: sendto");
	    }

        while (Client_receive(buf, MAXBUFLEN) != -1) {
	        buf[numbytes] = '\0';
	        printf("Receiving: %s\n", buf);
	    }
        if (errno != EAGAIN && errno != EWOULDBLOCK) {
	    	perror("recvfrom");
        }

        wait(0, 10000);

    }

	close(connection.sockfd);

	return 0;
}

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

#define SERVERPORT "4950"	// the port users will be connecting to
#define MAXBUFLEN 100

void wait(long seconds, long microseconds)
{
    struct timespec reqDelay = { seconds, microseconds * 1000};
    nanosleep(&reqDelay, (struct timespec*) NULL);
}


int main(int argc, char *argv[])
{
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;
	struct sockaddr_storage their_addr;
	char buf[MAXBUFLEN];
    //char* server_ip = "206.87.203.1";
    char server_ip[] = "127.0.0.1";
	socklen_t addr_len;
	char s[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if ((rv = getaddrinfo(server_ip, SERVERPORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	// loop through all the results and make a socket
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("talker: socket");
			continue;
		}

        if ((rv = fcntl(sockfd, F_SETFL, O_NONBLOCK)) == -1) {
			perror("listener: fcntl");
			continue;
        }

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "talker: failed to create socket\n");
		return 2;
	}

    char first_msg[] = "connect with me\n";
	if ((numbytes = sendto(sockfd, first_msg, strlen(first_msg), 0,
			 p->ai_addr, p->ai_addrlen)) == -1) {
		perror("talker: sendto");
		//exit(1);
	}

    int msg_no = 0;
    while (true) {
        msg_no++;
        char msg[1024];
        strcpy(msg, "Hello from client ");
        snprintf(msg+strlen(msg), 1024, "%d\n", msg_no);
        printf("About to send: %s\n", msg);

	    if ((numbytes = sendto(sockfd, msg, strlen(msg), 0,
	    		 p->ai_addr, p->ai_addrlen)) == -1) {
	    	perror("talker: sendto");
	    }
	    printf("talker: sent %d bytes\n", numbytes);

	    addr_len = sizeof their_addr;
	    while ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0, (struct sockaddr *)&their_addr, &addr_len)) != -1) {
	        buf[numbytes] = '\0';
	        printf("talker: packet = \"%s\"\n", buf);
	    }
        if (errno != EAGAIN && errno != EWOULDBLOCK) {
	    	perror("recvfrom");
        }

        wait(0, 10000);

    }

	freeaddrinfo(servinfo);
	close(sockfd);

	return 0;
}
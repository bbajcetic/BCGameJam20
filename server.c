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

#define MYPORT "4950"	// the port users will be connecting to

#define MAXBUFLEN 100

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;
	struct sockaddr_storage their_addr;
	char buf[MAXBUFLEN];
	socklen_t addr_len;
	char s[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	//if ((rv = getaddrinfo("127.0.0.1", MYPORT, &hints, &servinfo)) != 0) {
	if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	// loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("listener: socket");
			continue;
		}
        if ((rv = fcntl(sockfd, F_SETFL, O_NONBLOCK)) == -1) {
			perror("listener: fcntl");
			continue;
        }

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("listener: bind");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "listener: failed to bind socket\n");
		return 2;
	}

	freeaddrinfo(servinfo);

    addr_len = sizeof(their_addr);
    //get client's address info
    do {
        numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0, (struct sockaddr *)&their_addr, &addr_len);
    } while(numbytes == -1);

    int msg_no = 0;
    while (true) {
	    struct sockaddr_storage temp;
        socklen_t temp_len;

        msg_no++;
        char msg[1024];
        strcpy(msg, "Hello from server ");
        snprintf(msg+strlen(msg), 1024, "%d\n", msg_no);
        printf("About to send %s\n", msg);

	    while ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0, (struct sockaddr *)&temp, &temp_len)) != -1) {
	        printf("listener: got packet from %s\n", inet_ntop(their_addr.ss_family, 
                        get_in_addr((struct sockaddr *)&their_addr), s, sizeof s));
	        printf("listener: packet is %d bytes long\n", numbytes);
	        buf[numbytes] = '\0';
	        printf("listener: packet contains \"%s\"\n", buf);
	    }
        if (errno != EAGAIN && errno != EWOULDBLOCK) {
	    	perror("recvfrom");
	    	//exit(1);
        }


	    if ((numbytes = sendto(sockfd, msg, strlen(msg), 0,
	    		 (const struct sockaddr *)&their_addr, sizeof(their_addr)/*p->ai_addr, p->ai_addrlen*/)) == -1) {
	    	perror("listener: sendto");
	    	exit(1);
	    }

	    printf("listener: sent %d bytes\n", numbytes);
    }


	close(sockfd);

	return 0;
}

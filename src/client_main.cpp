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
#include "client.h"

#define MAXBUFLEN 100
int main(int argc, char *argv[])
{
    Client_initialize();

    Client_connect();



    //create message to send client
    int msg_no = 0;

	int numbytes;

    //client send/receive loop
    while (true) {
	    char buf[MAXBUFLEN] = {0};
        msg_no++;
        char msg[1024] = {0};
        strcpy(msg, "Hello from client ");
        snprintf(msg+strlen(msg), 1024, "%d\n", msg_no);
        msg[strlen(msg)] = '\0';
        printf("Sending: %s\n", msg);

	    if ((numbytes = Client_send(msg)) == -1) {
	    	perror("talker: sendto");
	    }

        while ((numbytes = Client_receive(buf, MAXBUFLEN)) != -1) {
	        buf[numbytes] = '\0';
	        printf("Receiving: %s\n", buf);
	    }
        if (errno != EAGAIN && errno != EWOULDBLOCK) {
	    	perror("recvfrom");
        }

        wait(0, 10000);

    }
    
    Client_clean();

	return 0;
}


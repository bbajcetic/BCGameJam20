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
#include "network.h"

#define MAXBUFLEN 100

int main(void)
{

    Network_chooseHost();

    printf("here\n");

    //create message to send client
    int msg_no = 0;

    //server send/receive loop
    while (true) {

	    char buf[MAXBUFLEN] = {0};
        msg_no++;

        char msg[1024] = {0};
        strcpy(msg, "Hello client ");
        snprintf(msg+strlen(msg), 1024, "%d\n", msg_no);
        msg[strlen(msg)] = '\0';

        printf("Sending: %s\n", msg);
        Network_update(msg, buf, MAXBUFLEN);
	    printf("Receiving: %s\n", buf);

        wait(0, 10000);
    }

    Server_clean();

	return 0;
}

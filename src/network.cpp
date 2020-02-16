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

static Connection connectionType;

void Network_initialize(Connection connection_type) {
    connectionType = connection_type;
    switch( connectionType ) {
        case Connection::Server:
            Server_initialize();
            Server_connect();
            break;
        case Connection::Client:
            Client_initialize();
            Client_connect();
            break;
    }
}

void Network_chooseHost() {
    char option;
    printf("Are you the client or the server?\n");
    while (option != 's' && option != 'c') {
        printf("Choose option ( s = server / c = client): ");
        scanf("%c", &option);
    }
    switch(option) {
        case 's':
            Network_initialize(Connection::Server);
            break;
        case 'c':
            Network_initialize(Connection::Client);
            break;
    }
}

/*
Call this function to share information with the other player.
    send_buf: char* full of your player's information
    recv_buf: empty char* to fill with other player's information(set buffer to null beforehand)
    recv_size: max buffer size of information to receive from other player
*/
void Network_update(char* send_buf, char* recv_buf, int recv_size) {
    int numbytes;
    switch(connectionType) {
        case Connection::Server:
            //receive
            while ((numbytes = Server_receive(recv_buf, recv_size)) != -1) {
                recv_buf[numbytes] = '\0';
            }
            if (errno != EAGAIN && errno != EWOULDBLOCK) {
	        	perror("recvfrom");
            }

            //send
            if ((numbytes = Server_send(send_buf)) == -1) {
	        	perror("listener: sendto");
	        }
            break;
        case Connection::Client:
            //send
	        if ((numbytes = Client_send(send_buf)) == -1) {
	        	perror("talker: sendto");
	        }

            //receive
            while ((numbytes = Client_receive(recv_buf, recv_size)) != -1) {
	            recv_buf[numbytes] = '\0';
	        }
            if (errno != EAGAIN && errno != EWOULDBLOCK) {
	        	perror("recvfrom");
            }
            break;
    }
}

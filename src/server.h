#ifndef SERVER_H
#define SERVER_H

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

struct serverInfo {
    int sockfd;
    struct addrinfo* netInfo;
    struct sockaddr_storage client_addr;
};

void Server_initialize();
void Server_connect();
int Server_receive(char* buf, int recv_size);
int Server_send(char* msg);
void Server_clean();

#endif

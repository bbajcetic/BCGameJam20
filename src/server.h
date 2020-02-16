#ifndef SERVER_H
#define SERVER_H

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

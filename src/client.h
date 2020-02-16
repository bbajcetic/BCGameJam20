#ifndef CLIENT_H
#define CLIENT_H

struct clientInfo {
    int sockfd;
    struct addrinfo* netInfo;
    char server_ip[20];
};

void Client_initialize();
void Client_connect();
int Client_send(char* msg);
int Client_receive(char* buf, int recv_size);

#endif

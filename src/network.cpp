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
void Network_clean() {
    switch( connectionType ) {
        case Connection::Server:
            Server_clean();
            break;
        case Connection::Client:
            Client_clean();
            break;
    }
}

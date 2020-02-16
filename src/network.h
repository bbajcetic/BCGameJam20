#ifndef NETWORK_H
#define NETWORK_H

#include "server.h"
#include "client.h"

enum class Connection { Server, Client };

void Network_initialize(Connection connection_type);
void Network_chooseHost();
void Network_update(char* send_buf, char* recv_buf, int recv_size);

#endif


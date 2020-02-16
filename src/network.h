#ifndef NETWORK_H
#define NETWORK_H

#include "server.h"
#include "client.h"

enum class Connection { Server, Client };

void Network_initialize(Connection connection_type);
void Network_chooseHost();

#endif


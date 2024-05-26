#include <iostream>
#include "server/server.h"
#include "client/client.h"

int main() {
    Server server;
    Client client;

    server.start();
    client.start();

    // Add test cases to validate functionality

    server.stop();
    client.stop();

    return 0;
}

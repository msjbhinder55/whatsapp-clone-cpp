#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>  // For sockaddr_in
#include <thread>        // For std::thread

// Constants
constexpr int SERVER_PORT = 9090;
constexpr int MAX_CLIENTS = 10;

// Function prototypes
void handleClient(int clientSocket);
void startServer();

#endif // SERVER_H

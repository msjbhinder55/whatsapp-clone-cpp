#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>  // For sockaddr_in
#include <thread>        // For std::thread

// Define the server port
constexpr int SERVER_PORT = 9090;
// Define the maximum number of clients that can connect to the server
constexpr int MAX_CLIENTS = 10;

// Function prototypes
void handleClient(int clientSocket);
void startServer();

#endif // SERVER_H

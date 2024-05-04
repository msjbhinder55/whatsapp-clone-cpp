#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <thread>
#include <vector>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

// Function to handle individual client connections
void handleClient(int clientSocket);

// Function to start the server
void startServer();

#endif // SERVER_H

// Header file for client handler

#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <string>

// Forward declaration of the Client struct
struct Client;

// Function to add a client to the list
void addClient(int clientSocket, const std::string& username);

// Function to remove a client from the list
void removeClient(int clientSocket);

// Function to broadcast a message to all clients except the sender
void broadcastMessage(const std::string& message, int senderSocket);

// This function handles each client connection
void handleClient(int clientSocket);

#endif // CLIENT_HANDLER_H

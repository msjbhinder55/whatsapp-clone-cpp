// Header file for message router

#ifndef MESSAGE_ROUTER_H
#define MESSAGE_ROUTER_H

#include <string>

// Function to route a message from one client to another
void routeMessage(int senderSocket, const std::string& message);

// Function to register a new client with the router
void registerClient(int clientSocket, const std::string& username);

// Function to remove a client from the router
void removeClient(int clientSocket);

#endif // MESSAGE_ROUTER_H

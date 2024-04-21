// Code for routing messages

#include "message_router.h"
#include <iostream>
#include <unordered_map>

// Assume Client structure and connection details are managed here
struct Client {
    int socket;
    std::string username;
};

// Using a map to keep track of clients by socket for easy lookup
static std::unordered_map<int, Client> clientsMap;

void routeMessage(int senderSocket, const std::string& message) {
    // Extracting recipient information from the message
    // For simplicity, assume the first word in the message is the recipient's username
    size_t pos = message.find(' ');
    if (pos == std::string::npos) {
        std::cerr << "Invalid message format.\n";
        return;
    }

    std::string recipient = message.substr(0, pos);
    std::string content = message.substr(pos + 1);

    // Find the recipient in the client map
    for (const auto& clientPair : clientsMap) {
        if (clientPair.second.username == recipient) {
            // Send message to the intended recipient
            if (send(clientPair.second.socket, content.c_str(), content.length(), 0) < 0) {
                std::cerr << "Failed to send message to " << recipient << ".\n";
            }
            break;
        }
    }
}

void registerClient(int clientSocket, const std::string& username) {
    // Add or update the client in the map
    clientsMap[clientSocket] = {clientSocket, username};
}

void removeClient(int clientSocket) {
    // Remove client from the map when disconnected
    clientsMap.erase(clientSocket);
}
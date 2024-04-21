// Code for managing client connections

#include "client_handler.h"
#include <iostream>
#include <vector>
#include <mutex>
#include <algorithm>

// A struct to represent a client
struct Client {
    int socket;
    std::string username;
};

// Vector to hold connected clients
std::vector<Client> clients;
// Mutex to ensure thread-safe access to the clients vector
std::mutex clientsMutex;

// Function to add a client to the list
void addClient(int clientSocket, const std::string& username) {
    std::lock_guard<std::mutex> lock(clientsMutex);
    clients.push_back({clientSocket, username});
    std::cout << "Added new client: " << username << std::endl;
}

// Function to remove a client from the list
void removeClient(int clientSocket) {
    std::lock_guard<std::mutex> lock(clientsMutex);
    auto it = std::find_if(clients.begin(), clients.end(), [clientSocket](const Client& client) {
        return client.socket == clientSocket;
    });
    if (it != clients.end()) {
        std::cout << "Removing client: " << it->username << std::endl;
        clients.erase(it);
    }
}

// Function to broadcast a message to all clients except the sender
void broadcastMessage(const std::string& message, int senderSocket) {
    std::lock_guard<std::mutex> lock(clientsMutex);
    for (const auto& client : clients) {
        if (client.socket != senderSocket) {
            // Placeholder for sending message logic
            std::cout << "Sending message to " << client.username << std::endl;
        }
    }
}

// This function handles each client connection
void handleClient(int clientSocket) {
    // Here, we could have the logic to initially get the client's username or other identification info
    std::string username = "Client" + std::to_string(clientSocket); // Placeholder for actual client identification

    addClient(clientSocket, username);

    // Placeholder for the main loop that reads messages from the client
    // In a real application, this would involve reading from the socket

    // Simulation of client disconnection
    removeClient(clientSocket);
}

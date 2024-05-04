#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include "server.h"

// Constants for the server
constexpr int SERVER_PORT = 12345;  // Server port number
constexpr int MAX_CLIENTS = 10;     // Maximum number of concurrent clients

void handleClient(int clientSocket) {
    char buffer[1024];  // Buffer to store client messages
    int bytesRead;

    // Communication loop
    while ((bytesRead = read(clientSocket, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytesRead] = '\0'; // Ensure string is null-terminated
        std::cout << "Received: " << buffer << std::endl;

        // Here you could add message routing or other processing logic
        // Echo message back to client
        write(clientSocket, buffer, bytesRead);
    }

    // Close the socket when done
    close(clientSocket);
    std::cout << "Client disconnected." << std::endl;
}

void startServer() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    // Create the server socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Set socket options if necessary (e.g., SO_REUSEADDR)

    // Bind the socket to an IP / port
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to bind to port." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(serverSocket, MAX_CLIENTS) < 0) {
        std::cerr << "Failed to listen on socket." << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Server is listening on port " << SERVER_PORT << std::endl;

    // Accept calls
    while ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen))) {
        if (clientSocket < 0) {
            std::cerr << "Failed to accept client connection." << std::endl;
            continue;
        }

        // Handle client in a separate thread
        std::thread clientThread(handleClient, clientSocket);
        clientThread.detach(); // Detach the thread to handle multiple clients
    }

    // Close the listening socket
    close(serverSocket);
}

int main() {
    // Start the server
    startServer();
    return 0;
}

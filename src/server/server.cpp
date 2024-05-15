#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <algorithm>
#include <unordered_map>
#include <cstring> // For memset
#include <arpa/inet.h> // For inet_ntoa
#include <fcntl.h> // For non-blocking sockets
#include <cerrno> // For errno
#include <stdexcept> // For std::runtime_error
#include <chrono> // For timestamps

// Constants for the server
constexpr int SERVER_PORT = 12345; // Server port number
constexpr int MAX_CLIENTS = 10; // Maximum number of concurrent clients
constexpr int BUFFER_SIZE = 1024; // Size of the message buffer

// Encryption key for Caesar cipher
constexpr int ENCRYPTION_KEY = 3;

// Timeout for receiving messages (in seconds)
constexpr int RECEIVE_TIMEOUT_SEC = 3600;

static int clientCounter = 1; // Static counter for generating unique usernames

// A struct to represent a client
struct Client {
    int socket;
    std::string username;
    std::string ip_address; // Client IP address
    std::chrono::steady_clock::time_point last_activity; // Timestamp of last activity
    std::string current_room; // Current chat room the client is in
};

// Vector to hold connected clients
std::vector<Client> clients;
// Mutex to ensure thread-safe access to the clients vector
std::mutex clientsMutex;

// Function to set socket to non-blocking mode
void setNonBlocking(int socket) {
    int flags = fcntl(socket, F_GETFL, 0);
    if (flags == -1) {
        throw std::runtime_error("\nFailed to get socket flags");
    }
    if (fcntl(socket, F_SETFL, flags | O_NONBLOCK) == -1) {
        throw std::runtime_error("\nFailed to set non-blocking mode for socket");
    }
}

// Function to add a client to the list
void addClient(int clientSocket, const std::string& username) {
    std::lock_guard<std::mutex> lock(clientsMutex);
    // Set socket to non-blocking mode
    setNonBlocking(clientSocket);
    // Get client IP address
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    getpeername(clientSocket, (struct sockaddr *)&addr, &len);
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &addr.sin_addr, ip, INET_ADDRSTRLEN);
    clients.push_back({
        clientSocket,
        username,
        ip,
        std::chrono::steady_clock::now(),
        "" // Initialize current_room to empty string
    });
    std::cout << "\nAdded new client: " << username << " (" << ip << ")" << ", Socket: " << clientSocket << std::endl;
}

// Function to remove a client from the list
void removeClient(int clientSocket) {
    std::lock_guard<std::mutex> lock(clientsMutex);
    auto it = std::find_if(clients.begin(), clients.end(), [clientSocket](const Client& client) {
        return client.socket == clientSocket;
    });
    if (it != clients.end()) {
        std::cout << "\nRemoving client: " << it->username << " (" << it->ip_address << ")" << std::endl;
        clients.erase(it);
    }
}

// Function to send a message to a specific client
void sendMessageToClient(int clientSocket, const std::string& message) {
    if (send(clientSocket, message.c_str(), message.size(), 0) < 0) {
        std::cerr << "\nFailed to send message to client." << std::endl;
    }
}

// Function to broadcast a message to all clients in a room
void broadcastToRoom(const std::string& roomName, const std::string& message) {
    std::lock_guard<std::mutex> lock(clientsMutex);
    for (const auto& client : clients) {
        if (client.current_room == roomName) {
            // Encrypt the message before sending
            std::string encryptedMessage = message;
            for (char& c : encryptedMessage) {
                if (isalpha(c)) {
                    c = std::isupper(c) ? 'A' + (c - 'A' + ENCRYPTION_KEY) % 26 : 'a' + (c - 'a' + ENCRYPTION_KEY) % 26;
                }
            }
            sendMessageToClient(client.socket, encryptedMessage);
        }
    }
}

// Function to get the current room of a client
std::string getCurrentRoom(int clientSocket) {
    std::lock_guard<std::mutex> lock(clientsMutex);
    for (const auto& client : clients) {
        if (client.socket == clientSocket) {
            return client.current_room;
        }
    }
    return ""; // Return an empty string if client's current room is not found
}

// Function to show the admin panel
void showAdminPanel() {
    std::cout << "\n===== ADMIN PANEL =====" << std::endl;
    std::cout << "1. View Connected Clients" << std::endl;
    std::cout << "2. Broadcast Message to All Clients" << std::endl;
    std::cout << "Enter your choice (0 to exit): ";
}

// Function to handle admin actions
void handleAdminActions() {
    int choice;
    do {
        showAdminPanel();
        std::cin >> choice;
        switch (choice) {
            case 1:
                // View connected clients
                {
                    std::lock_guard<std::mutex> lock(clientsMutex);
                    std::cout << "\n===== CONNECTED CLIENTS =====" << std::endl;
                    for (const auto& client : clients) {
                        std::cout << "Username: " << client.username << ", IP: " << client.ip_address << std::endl;
                    }
                    std::cout << "==============================" << std::endl;
                }
                break;
            case 2:
                // Broadcast message to all clients
                {
                    std::string message;
                    std::cout << "\nEnter the message to broadcast: ";
                    std::cin.ignore(); // Clear input buffer
                    std::getline(std::cin, message);
                    broadcastToRoom("", "[ADMIN]: " + message);
                    std::cout << "\nMessage broadcasted to all clients." << std::endl;
                }
                break;
            case 0:
                std::cout << "\nExiting admin panel." << std::endl;
                break;
            default:
                std::cout << "\nInvalid choice. Please try again." << std::endl;
                break;
        }
    } while (choice != 0);
}

// This function handles each client connection
void handleClient(int clientSocket) {
    // Increment client counter and generate username
    std::string username = "\nClient" + std::to_string(clientCounter++);

    addClient(clientSocket, username);

    char buffer[BUFFER_SIZE]; // Buffer to store client messages
    int bytesRead;

    // Communication loop
    while (true) {
        // Receive message from client
        memset(buffer, 0, sizeof(buffer));
        bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0'; // Ensure string is null-terminated
            std::cout << "\nReceived from " << username << ": " << buffer << std::endl;

            // Broadcast message to all clients except the sender
            std::lock_guard<std::mutex> lock(clientsMutex);
            for (const auto& client : clients) {
                if (client.socket != clientSocket) {
                    sendMessageToClient(client.socket, username + ": " + std::string(buffer));
                }
            }
        } else if (bytesRead == 0) {
            // Client disconnected
            std::cout << "\nClient disconnected: " << username << std::endl;
            removeClient(clientSocket);
            break;
        } else {
            // Handle error (non-blocking mode)
            if (errno != EWOULDBLOCK && errno != EAGAIN) {
                std::cerr << "\nError receiving data from client: " << strerror(errno) << std::endl;
                removeClient(clientSocket);
                break;
            }
        }

        // Check for inactivity timeout
        std::lock_guard<std::mutex> lock(clientsMutex);
        auto it = std::find_if(clients.begin(), clients.end(), [clientSocket](const Client& client) {
            return client.socket == clientSocket;
        });
        if (it != clients.end()) {
            auto currentTime = std::chrono::steady_clock::now();
            auto lastActivity = it->last_activity;
            if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastActivity).count() > RECEIVE_TIMEOUT_SEC) {
                std::cerr << "\nClient timeout: " << it->username << std::endl;
                removeClient(clientSocket);
                break;
            }
        }

        // Sleep to avoid busy-waiting
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Close the socket
    ::close(clientSocket);
}

// Function to start the server
void startServer() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    // Create the server socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "\nFailed to create socket." << std::endl;
        exit(EXIT_FAILURE);
    }
    // Set socket options if necessary (e.g., SO_REUSEADDR)

    // Bind the socket to an IP / port
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "\nFailed to bind to port." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Start listening for connections
    if (listen(serverSocket, MAX_CLIENTS) < 0) {
        std::cerr << "\nFailed to listen for connections." << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Server started. Listening on port " << SERVER_PORT << std::endl;

    // Start admin panel in a separate thread
    std::thread adminThread(handleAdminActions);
    adminThread.detach();

    // Server loop
    while (true) {
        // Accept a client connection
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket < 0) {
            std::cerr << "\nFailed to accept client connection." << std::endl;
            continue;
        }

        // Handle client connection in a separate thread
        std::thread clientThread(handleClient, clientSocket);
        clientThread.detach();
    }

    // Close the server socket
    ::close(serverSocket);
}

int main() {
    startServer();
    return 0;
}

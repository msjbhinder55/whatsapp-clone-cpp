#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <thread>
#include <fstream> // Added for file stream
#include <unordered_map>

constexpr int SERVER_PORT = 12345;
constexpr int BUFFER_SIZE = 1024;

void receiveMessages(int socket) {
    char buffer[BUFFER_SIZE];
    int bytesRead;
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        bytesRead = recv(socket, buffer, sizeof(buffer), 0);
        if (bytesRead > 0) {
            std::cout << "\nReceived: " << buffer << std::endl;
        } else if (bytesRead == 0) {
            std::cout << "\nDisconnected from server." << std::endl;
            break;
        } else {
            std::cerr << "\nError receiving data from server." << std::endl;
            break;
        }
    }
}

void sendMessage(int socket, const std::string& message) {
    if (send(socket, message.c_str(), message.size(), 0) < 0) {
        std::cerr << "\nFailed to send message." << std::endl;
    }
}

void shareMedia(int socket, const std::string& mediaPath) {
    std::cout << "\nSharing media: " << mediaPath << std::endl;
    std::ifstream file(mediaPath, std::ios::binary);
    if (!file) {
        std::cerr << "\nFailed to open media file." << std::endl;
        return;
    }

    // Determine the size of the file
    file.seekg(0, std::ios::end);
    int fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Read the file content into a buffer
    std::string fileContent;
    fileContent.resize(fileSize);
    file.read(&fileContent[0], fileSize);

    // Send the file content to the server
    if (send(socket, fileContent.c_str(), fileSize, 0) < 0) {
        std::cerr << "\nFailed to send media file." << std::endl;
    }

    file.close();
}

void downloadFile(int socket, const std::string& filename) {
    std::cout << "\nDownloading file: " << filename << std::endl;
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "\nFailed to create file." << std::endl;
        return;
    }

    char buffer[BUFFER_SIZE];
    int bytesRead;
    while ((bytesRead = recv(socket, buffer, sizeof(buffer), 0)) > 0) {
        file.write(buffer, bytesRead);
    }

    if (bytesRead < 0) {
        std::cerr << "\nError downloading file." << std::endl;
    }

    file.close();
}

void initiateGroupChat(int socket) {
    std::string groupName;
    std::cout << "\nEnter group name: ";
    std::getline(std::cin, groupName);

    // Send the group name to the server
    sendMessage(socket, "\nINITIATE_GROUP_CHAT:" + groupName);
}


void shareStatus(int socket, const std::string& status) {
    std::cout << "\nSharing status: " << status << std::endl;
    // Placeholder for sharing status logic
    // You can implement code to send status to the server
    std::string message = "\nSTATUS:" + status;
    sendMessage(socket, message);
}

void viewStatus(int socket) {
    std::cout << "\nViewing status of other users..." << std::endl;
    // Placeholder for viewing status logic
    // You can implement code to request and display status from the server
    sendMessage(socket, "REQUEST_STATUS");
}

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "\nFailed to create socket." << std::endl;
        return EXIT_FAILURE;
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "\nFailed to connect to server." << std::endl;
        close(clientSocket);
        return EXIT_FAILURE;
    }
    std::cout << "\nConnected to server." << std::endl;

    // Start receiving messages in a separate thread
    std::thread receiveThread(receiveMessages, clientSocket);
    receiveThread.detach();

    // User interface loop
    std::string input;
    while (true) {
        std::cout << "\nOptions:\n";
        std::cout << "1. Send Text Message\n";
        std::cout << "2. Share Media\n";
        std::cout << "3. Download File\n";
        std::cout << "4. Initiate Group Chat\n";
        std::cout << "5. Share Status\n";
        std::cout << "6. View Status\n";
        std::cout << "7. Quit\n";
        std::cout << "Enter your choice: ";
        std::getline(std::cin, input);

        if (input == "1") {
            std::string message;
            std::cout << "\nEnter message: ";
            std::getline(std::cin, message);
            sendMessage(clientSocket, message);
        } else if (input == "2") {
            std::string mediaPath;
            std::cout << "\nEnter media path: ";
            std::getline(std::cin, mediaPath);
            shareMedia(clientSocket, mediaPath);
        } else if (input == "3") {
            std::string filename;
            std::cout << "\nEnter filename to download: ";
            std::getline(std::cin, filename);
            sendMessage(clientSocket, "\nDOWNLOAD:" + filename);
        } else if (input == "4") {
            initiateGroupChat(clientSocket);
        } else if (input == "5") {
            std::string status;
            std::cout << "\nEnter status: ";
            std::getline(std::cin, status);
            shareStatus(clientSocket, status);
        } else if (input == "6") {
            viewStatus(clientSocket);
        } else if (input == "7") {
            std::cout << "\nExiting..." << std::endl;
            break;
        } else {
            std::cout << "\nInvalid input. Please try again." << std::endl;
        }
    }

    // Close socket
    close(clientSocket);

    return 0;
}

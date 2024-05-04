#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>  // For inet_addr()
#include <unistd.h>     // For close()
#include <thread>

constexpr int SERVER_PORT = 12345;
constexpr char SERVER_IP[] = "127.0.0.1";

class ChatClient {
private:
    int sock;
    struct sockaddr_in server;

    bool connectToServer() {
        this->sock = socket(AF_INET, SOCK_STREAM, 0);
        if (this->sock == -1) {
            std::cerr << "Could not create socket" << std::endl;
            return false;
        }

        server.sin_addr.s_addr = inet_addr(SERVER_IP);
        server.sin_family = AF_INET;
        server.sin_port = htons(SERVER_PORT);

        if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
            perror("Connect failed. Error");
            return false;
        }

        std::cout << "Connected to server" << std::endl;
        return true;
    }

    void sendMessage(const std::string& message) {
        if (send(sock, message.c_str(), message.size(), 0) < 0) {
            std::cerr << "Send failed" << std::endl;
            return;
        }
    }

    std::string receiveMessage() {
        char buffer[2000];
        if (recv(sock, buffer, sizeof(buffer), 0) < 0) {
            std::cerr << "recv failed" << std::endl;
            return "";
        }
        return std::string(buffer);
    }

public:
    ChatClient() : sock(-1) {
        memset(&server, 0, sizeof(server));
    }

    ~ChatClient() {
        close(sock);
    }

    void run() {
        if (!connectToServer()) {
            return;
        }

        std::string input;
        while (true) {
            std::cout << "Enter command ('message', 'status', 'file', 'exit'): ";
            std::getline(std::cin, input);

            if (input == "exit") {
                break;
            } else if (input == "message") {
                std::cout << "Enter your message: ";
                std::getline(std::cin, input);
                sendMessage("MSG:" + input);
            } else if (input == "status") {
                std::cout << "Enter your status: ";
                std::getline(std::cin, input);
                sendMessage("STATUS:" + input);
            } else if (input == "file") {
                std::cout << "Enter file path: ";
                std::getline(std::cin, input);
                // Implement file sending (this is a placeholder)
                sendMessage("FILE:" + input);
            }

            std::string reply = receiveMessage();
            std::cout << "Server reply: " << reply << std::endl;
        }
    }
};

int main() {
    ChatClient client;
    client.run();
    return 0;
}

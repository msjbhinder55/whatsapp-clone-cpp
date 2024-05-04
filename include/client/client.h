#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>  // For inet_addr()
#include <unistd.h>     // For close()

class ChatClient {
private:
    int sock;
    struct sockaddr_in server;

    bool connectToServer();
    void sendMessage(const std::string& message);
    std::string receiveMessage();

public:
    ChatClient();
    ~ChatClient();
    void run();
};

#endif // CLIENT_H

// Header file for server

#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

// Define your message structure
struct Message {
    std::string sender;
    std::string recipient;
    std::string content;
};

// Define your server class
class Server {
private:
    std::vector<std::thread> clientThreads;
    std::mutex mtx;

    // Method for handling incoming connections from clients
    void handleClientConnection(int clientID);

    // Method for routing messages to their intended recipients
    void routeMessage(Message msg);

public:
    // Constructor
    Server();

    // Destructor
    ~Server();

    // Method for starting the server
    void start();

    // Method for stopping the server
    void stop();

    // Method for handling incoming messages
    void handleMessage(Message msg);
};

#endif // SERVER_H

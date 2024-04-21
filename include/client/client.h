// Header file for client

#ifndef CLIENT_H
#define CLIENT_H

#include <string>

// Function to handle receiving messages from the server
void receiveMessages();

// Function to send a message to the server
void sendMessage(const std::string& message);

// Function to handle user input for sending messages
void handleUserInput();

#endif // CLIENT_H

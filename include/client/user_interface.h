// Header file for user interface

#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <string>

// Function to handle displaying received messages
void displayMessage(const std::string& sender, const std::string& message);

// Function to handle sending messages
void sendMessage(const std::string& message);

// Function to handle updating user status
void updateStatus(const std::string& status);

// Function to start the user interface
void startUserInterface();

#endif // USER_INTERFACE_H

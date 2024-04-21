// Code for user interface

#include "user_interface.h"
#include <iostream>
#include <thread>
#include <unistd.h> // For sleep(), optional

// Function to handle displaying received messages
void displayMessage(const std::string& sender, const std::string& message) {
    std::cout << sender << ": " << message << "\n";
}

// Function to handle sending messages
void sendMessage(const std::string& message) {
    // Placeholder for sending message to the server
    std::cout << "Sending message: " << message << "\n";
}

// Function to handle updating user status
void updateStatus(const std::string& status) {
    // Placeholder for updating user status
    std::cout << "Updating status: " << status << "\n";
}

// Function to handle user input for sending messages
void handleUserInput() {
    while (true) {
        std::string message;
        std::getline(std::cin, message);
        sendMessage(message);
    }
}

// Function to start the user interface
void startUserInterface() {
    std::thread inputThread(handleUserInput);
    inputThread.detach(); // Detach thread to run in background

    // Placeholder for GUI initialization (if applicable)
    std::cout << "User interface initialized.\n";

    // Simulating message reception and status update (remove this in actual implementation)
    displayMessage("Sender", "Hello, world!");
    sleep(2);
    updateStatus("Busy");
}

int main() {
    // Start the user interface
    startUserInterface();

    // Placeholder for running the user interface loop (if applicable)
    // The user interface may run in its own loop, handling events and updating the GUI

    return 0;
}

// Definition of message structure

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <chrono> // For timestamp

struct Message {
    std::string sender;
    std::string recipient;
    std::chrono::system_clock::time_point timestamp;
    std::string content;
    // Add any other relevant metadata here

    // Constructor to initialize the message
    Message(const std::string& sender, const std::string& recipient, const std::string& content)
        : sender(sender), recipient(recipient), content(content) {
        // Initialize timestamp with current time
        timestamp = std::chrono::system_clock::now();
    }
};

#endif // MESSAGE_H

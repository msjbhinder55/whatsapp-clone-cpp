// Header file for chat manager

#ifndef CHAT_MANAGER_H
#define CHAT_MANAGER_H

#include <string>

// Function to send a text message to another user or group
void sendTextMessage(const std::string& recipient, const std::string& message);

// Function to share multimedia content (images, videos, documents)
void shareMedia(const std::string& recipient, const std::string& mediaPath);

// Function to handle group chat messages
void sendGroupMessage(const std::string& groupName, const std::string& message);

// Function to handle multimedia content in group chats
void shareMediaInGroup(const std::string& groupName, const std::string& mediaPath);

#endif // CHAT_MANAGER_H

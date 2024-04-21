// Header file for group chat manager

#ifndef GROUP_CHAT_MANAGER_H
#define GROUP_CHAT_MANAGER_H

#include <string>

// Function to create a new group
void createGroup(const std::string& groupName);

// Function to add a client to a group
void addClientToGroup(const std::string& groupName, int clientSocket);

// Function to remove a client from a group
void removeClientFromGroup(const std::string& groupName, int clientSocket);

// Function to broadcast a message to all members of a group
void broadcastGroupMessage(const std::string& groupName, const std::string& message);

// Function to delete a group
void deleteGroup(const std::string& groupName);

#endif // GROUP_CHAT_MANAGER_H

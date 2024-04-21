// Code for managing group chats

#include "group_chat_manager.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <mutex>

// Struct to represent a group
struct Group {
    std::vector<int> members; // Vector to store member socket descriptors
};

// Using a map to keep track of groups by name
static std::unordered_map<std::string, Group> groupsMap;
// Mutex to ensure thread-safe access to the groups map
std::mutex groupsMutex;

// Function to create a new group
void createGroup(const std::string& groupName) {
    std::lock_guard<std::mutex> lock(groupsMutex);
    groupsMap[groupName] = {};
    std::cout << "Group '" << groupName << "' created.\n";
}

// Function to add a client to a group
void addClientToGroup(const std::string& groupName, int clientSocket) {
    std::lock_guard<std::mutex> lock(groupsMutex);
    groupsMap[groupName].members.push_back(clientSocket);
}

// Function to remove a client from a group
void removeClientFromGroup(const std::string& groupName, int clientSocket) {
    std::lock_guard<std::mutex> lock(groupsMutex);
    auto& members = groupsMap[groupName].members;
    members.erase(std::remove(members.begin(), members.end(), clientSocket), members.end());
}

// Function to broadcast a message to all members of a group
void broadcastGroupMessage(const std::string& groupName, const std::string& message) {
    std::lock_guard<std::mutex> lock(groupsMutex);
    const auto& group = groupsMap[groupName];
    for (int memberSocket : group.members) {
        // Send message to each member of the group
        // Placeholder for actual sending logic
        std::cout << "Sending message to group member: " << memberSocket << std::endl;
    }
}

// Function to delete a group
void deleteGroup(const std::string& groupName) {
    std::lock_guard<std::mutex> lock(groupsMutex);
    groupsMap.erase(groupName);
    std::cout << "Group '" << groupName << "' deleted.\n";
}

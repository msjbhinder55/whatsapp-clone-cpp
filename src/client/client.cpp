#include "client.h"
#include "connection_manager.h"
#include "user_interface.h"
#include "chat_manager.h"
#include "security.h"

Client::Client() 
    : connectionManager(new ConnectionManager()),
      userInterface(new UserInterface()),
      chatManager(new ChatManager()),
      security(new Security()) {}

Client::~Client() {
    stop();
    delete connectionManager;
    delete userInterface;
    delete chatManager;
    delete security;
}

void Client::start() {
    // Start client and connect to server
}

void Client::stop() {
    // Clean up and stop the client
}

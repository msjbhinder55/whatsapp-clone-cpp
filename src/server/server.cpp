#include "server.h"
#include "client_handler.h"
#include "message_router.h"
#include "group_chat_manager.h"

Server::Server() 
    : clientHandler(std::make_unique<ClientHandler>()),
      messageRouter(std::make_unique<MessageRouter>()),
      groupChatManager(std::make_unique<GroupChatManager>()) {}

Server::~Server() {
    stop();
}

void Server::start() {
    // Start server and manage client connections
}

void Server::stop() {
    // Clean up and stop the server
}

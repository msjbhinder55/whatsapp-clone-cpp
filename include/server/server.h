#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <memory>

class ClientHandler;
class MessageRouter;
class GroupChatManager;

class Server {
public:
    Server();
    ~Server();
    void start();
    void stop();

private:
    std::unique_ptr<ClientHandler> clientHandler;
    std::unique_ptr<MessageRouter> messageRouter;
    std::unique_ptr<GroupChatManager> groupChatManager;
};

#endif // SERVER_H

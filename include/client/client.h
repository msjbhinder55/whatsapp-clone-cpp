#ifndef CLIENT_H
#define CLIENT_H

class ConnectionManager;
class UserInterface;
class ChatManager;
class Security;

class Client {
public:
    Client();
    ~Client();
    void start();
    void stop();

private:
    ConnectionManager* connectionManager;
    UserInterface* userInterface;
    ChatManager* chatManager;
    Security* security;
};

#endif // CLIENT_H

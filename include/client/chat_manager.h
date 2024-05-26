#ifndef CHAT_MANAGER_H
#define CHAT_MANAGER_H

#include <string>

class ChatManager {
public:
    ChatManager();
    void sendMessage(const std::string& message);
    void receiveMessage();
};

#endif // CHAT_MANAGER_H

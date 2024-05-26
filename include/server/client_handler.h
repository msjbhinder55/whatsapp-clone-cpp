#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <string>

class ClientHandler {
public:
    ClientHandler();
    void handleClient(int clientSocket);
};

#endif // CLIENT_HANDLER_H

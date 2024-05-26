#ifndef CONNECTION_MANAGER_H
#define CONNECTION_MANAGER_H

class ConnectionManager {
public:
    ConnectionManager();
    void connectToServer(const char* serverAddress, int port);
};

#endif // CONNECTION_MANAGER_H

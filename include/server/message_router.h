#ifndef MESSAGE_ROUTER_H
#define MESSAGE_ROUTER_H

#include <string>

class MessageRouter {
public:
    MessageRouter();
    void routeMessage(const std::string& message);
};

#endif // MESSAGE_ROUTER_H

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

struct Message {
    std::string sender;
    std::string recipient;
    std::string content;
};

#endif // MESSAGE_H

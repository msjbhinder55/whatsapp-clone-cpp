// Common constants and configurations

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace Constants {
    // Server configuration
    constexpr int SERVER_PORT = 8080;
    constexpr char SERVER_ADDRESS[] = "127.0.0.1"; // Change to actual server address

    // Message limits
    constexpr int MAX_MESSAGE_LENGTH = 1000;

    // File paths
    const std::string MEDIA_DIRECTORY = "media/";

    // Encryption keys
    const std::string ENCRYPTION_KEY = "your_encryption_key_here";

    // Other constants...
}

#endif // CONSTANTS_H

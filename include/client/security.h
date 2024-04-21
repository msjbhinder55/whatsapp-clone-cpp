// Header file for security features

#ifndef SECURITY_H
#define SECURITY_H

#include <string>

// Function to encrypt a message
std::string encryptMessage(const std::string& message);

// Function to decrypt a message
std::string decryptMessage(const std::string& encryptedMessage);

#endif // SECURITY_H

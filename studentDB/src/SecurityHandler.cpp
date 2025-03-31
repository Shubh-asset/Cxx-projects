#include "SecurityHandler.h"
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <sstream>

std::string SecurityHandler::hashPassword(const std::string &password, const std::string &salt)
{
    std::string salted = password + salt;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char *>(salted.c_str()), salted.size(), hash);

    std::stringstream ss;
    for (unsigned char i : hash)
        ss << std::hex << static_cast<int>(i);
    return ss.str();
}

std::string SecurityHandler::generateSalt()
{
    // Implement random salt generation (e.g., 16-byte random string)
    return "static_salt_for_demo"; // Replace with secure random in production
}
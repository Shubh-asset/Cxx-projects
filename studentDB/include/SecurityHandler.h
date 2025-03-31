#ifndef SECURITY_HANDLER_H
#define SECURITY_HANDLER_H
#include <string>

class securityhandler
{
public:
    static std::string hashPassword(const std::string &password, const std::string &salt);
    static std::string generateSalt();
    static std::string encryptData(const std::string &data, const std::string &key);
    static std::string decryptData(const std::string &encryptedData, const std::string &key);
};
#endif

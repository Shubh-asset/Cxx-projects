#include "DatabaseManager.h"
#include <iostream>

DatabaseManager::DatabaseManager(const std::string &host, const std::string &user, const std::string &pass)
{
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect(host, user, pass);
    con->setSchema("student_db");
}

bool DatabaseManager::authenticateUser(const std::string &username, const std::string &password, std::string &role)
{
    sql::PreparedStatement *stmt = con->prepareStatement(
        "SELECT password_hash, salt, role FROM Users WHERE username = ?");
    stmt->setString(1, username);
    sql::ResultSet *res = stmt->executeQuery();

    if (res->next())
    {
        std::string storedHash = res->getString("password_hash");
        std::string salt = res->getString("salt");
        role = res->getString("role");
        std::string inputHash = SecurityHandler::hashPassword(password, salt);
        return (inputHash == storedHash);
    }
    return false;
}
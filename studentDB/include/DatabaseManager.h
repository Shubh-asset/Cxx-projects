#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H
#include <mysql_driver.h>
#include <cppconn/driver.h>
#include <mysql_connection.h>
#include <mysql_error.h>
#include <cppconn/prepared_statement.h>

class DatabaseManager
{
private:
    sql::mysql::MySQL_Driver *driver;
    ;
    sql::Connection *con;

public:
    DatabaseManager(const std::string &host, const std::string &user, const std::string &pass);
    bool authenticateUser(const std::string &username, const std::string &password, std::string &role);
    void executeQuery(const std::string &query);
};

#endif
#ifdef USER_H
#define USER_H
#include <string>
#include "DatabaseManager.h"
#include "SecurityHandler.h"

class User
{
protected:
    int user_id;
    std::string username;
    std::string role;

public:
    virtual bool login(DatabaseManager &db, SecurityHandler &security) = 0;
    virtual void showMenu() = 0;
};
#endif
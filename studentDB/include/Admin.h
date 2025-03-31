#ifndef ADMIN_H
#define ADMIN_H
#include "User.h"

class Admin : public User
{
public:
    // bool login(DatabaseManager& db, SecurityHandler& security) override;
    bool Admin::login(DatabaseManager &db, SecurityHandler &security)
    {
        // implementation of the login function goes here
    }
    void Admin::showMenu() override;
    void Admin::addStudent(DatabaseManager &db) override;
    // void removeStudent(DatabaseManager &db); // New method added
};

#endif
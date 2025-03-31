#include <iostream>
#include "DatabaseManager.h"
#include "SecurityHandler.h"
#include "Admin.h"
#include "Student.h"

int main()
{
    try
    {
        // Initialize database connection
        DatabaseManager db("tcp://127.0.0.1:3306", "root", "your_mysql_password");
        SecurityHandler security;

        // User login
        std::string username, password, role;
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;

        if (db.authenticateUser(username, password, role))
        {
            User *user = nullptr;

            if (role == "admin")
            {
                user = new Admin();
            }
            else if (role == "student")
            {
                user = new Student();
            }

            if (user)
            {
                user->showMenu(); // Role-specific menu
                delete user;
            }
        }
        else
        {
            std::cout << "Authentication failed!\n";
        }
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "MySQL Error: " << e.what() << std::endl;
    }
    return 0;
}
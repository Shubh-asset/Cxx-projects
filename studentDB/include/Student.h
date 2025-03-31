#ifdef STUDENT_H
#define STUDENT_H
#include "User.h"

class Student : public User
{
public:
    bool login(DatabaseManager &db, SecurityHandler &security) override;
    void showMenu() override;
    void viewGrades(DatabaseManager &db);
};
#endif
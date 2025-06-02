#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

class Contact
{
private:
    string phoneNo, name, address, description;

public:
    Contact(string phone, string n, string addr, string desc) : phoneNo(move(phone)), name(move(n)), address(move(addr)), description(move(desc))
    {
    }
    // getters
    string getPhone() const
    {
        return phoneNo;
    }
    string getName() const
    {
        return name;
    }
    string getAddress() const
    {
        return address;
    }
    string getDescription()
    {
        return description;
    }

    // display constact information
    void display() const
    {
        cout << "\nPhone number: " << phoneNo
             << "\nName: " << name
             << "\nAddress: " << address
             << "\nDescription: " << description << endl;
    }

}

class ContactManager
{
private:
    vector<Contact> contacts;
    static unique_ptr<ContactManager> instance;

    // private constructor for singleton
    ContactManager() = default;

public:
    // singleton access
    static ContactManager &singleton()
    {
        if (!instance)
        {
            instance = make_unique<ContactManager>();
        }
        return *instance;
    }
}

int
main()
{
    return 0;
}
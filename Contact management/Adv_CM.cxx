#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>

#include <memory>
#include <regex>

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
    string getDescription() const
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
};

class ContactManager
{
private:
    vector<Contact> contacts;
    static unique_ptr<ContactManager> instance;

    // private constructor for singleton
    ContactManager() = default;

public:
    friend typename std::_MakeUniq<ContactManager>::__single_object
    std::make_unique<ContactManager>();
    // singleton access
    static ContactManager &singleton()
    {
        if (!instance)
        {
            instance = make_unique<ContactManager>();
            instance->loadFromFile();
        }
        return *instance;
    }

    ContactManager(const ContactManager &) = delete;
    ContactManager &operator=(const ContactManager &) = delete;

    void addContact()
    {
        string phone, name, address, desc;

        cout << "Enter your Phone no.: " << endl;
        getline(cin, phone);
        if (!validatePhone(phone))
        {
            throw invalid_argument("Invalid phone number");
        }

        cout << "Enter Name:";
        getline(cin, name);
        if (name.empty())
        {
            throw invalid_argument("Name cannot be empty");
        }

        cout << "Enter your address: " << endl;
        getline(cin, address);

        cout << "Enter the Description: " << endl;
        getline(cin, desc);

        contacts.emplace_back(phone, name, address, desc);
        saveToFile();
    }

    void showAll()
    {
        if (contacts.empty())
        {
            cout << "No contacts found";
            return;
        }
        // for each contact in the contacts list, do this
        for (const auto &contact : contacts)
        {
            contact.display();
        }
    }

    void searchContact() const
    {
        string search;
        cout << "Enter phone number to search: ";
        getline(cin, search);

        for (const auto &contact : contacts)
        {
            if (contact.getPhone() == search)
            {
                contact.display();
                return;
            }
        }
        cout << "Contact not found";
    }

private:
    // phone number validation using regex
    bool validatePhone(const string &phone) const
    {
        regex pattern(R"(\+?\d{10,15})");
        return regex_match(phone, pattern);
    }

    // RAII file handling
    void saveToFile()
    {
        ofstream file("contacts.dat", ios::binary);

        if (!file)
        {
            throw runtime_error("Failed to save contacts");
        }

        for (const auto &contact : contacts)
        {
            file << contact.getPhone() << '\n'
                 << contact.getName() << '\n'
                 << contact.getAddress() << '\n'
                 << contact.getDescription() << '\n';
        }
    }

    void loadFromFile()
    {
        ifstream file("contacts.dat", ios::binary);

        if (!file)
        {
            return;
        }
        string phone, name, address, desc;

        while (getline(file, phone) && getline(file, name) && getline(file, address) && getline(file, desc))
        {
            contacts.emplace_back(phone, name, address, desc);
        }
    }
};

unique_ptr<ContactManager> ContactManager::instance = nullptr;

int main()
{
    try
    {
        auto &manager = ContactManager::singleton();

        while (true)
        {
            cout << "\n******Contact Manager******\n"
                 << "1. Add Contact\n"
                 << "2. Show All Contacts\n"
                 << "3. Search Contact\n"
                 << "4. Exit\n"
                 << "Choose option: ";

            int choice;
            cin >> choice;
            cin.ignore(); // clear newline

            switch (choice)
            {
            case 1:
                manager.addContact();
                break;
            case 2:
                manager.showAll();
                break;
            case 3:
                manager.searchContact();
                break;
            case 4:
                return 0;

            default:
                cout << "Invalid choice!\n";
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

   
}
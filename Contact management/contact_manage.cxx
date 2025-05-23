#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class temp
{
    string phoneNo, name, address, description, search;
    fstream file;

public:
    void addContact();
    void showAll();
    void searchContact();
} obj;

int main()
{
    // obj.addContact();
    // obj.showAll();
    obj.searchContact();
    return 0;
}

void temp ::addContact()
{
    cout << "Enter your Phone number: ";
    getline(cin, phoneNo);
    cout << "Enter your Name: ";
    // cin.getline(name, 20);
    getline(cin, name);
    cout << "Enter your Address: ";
    getline(cin, address);
    cout << "Enter your Description: ";
    getline(cin, description);

    file.open("data.csv", ios ::out | ios ::app);
    // csv extension = spreadsheet file
    // out for write
    // app = append mode
    // we use comma to move between cells
    if (file.is_open())
    {
        file << phoneNo << "," << name << "," << address << "," << description << "\n";
        file.close();
        cout << "Opened successfully";
    }
    else
    {
        cout << "Error: Could not open file for writing\n";
    }
}

void temp ::showAll()
{
    file.open("data.csv", ios ::in);
    // getline(file, phoneNo, ",");
    // getline(file, name, ",");
    // getline(file, address, ",");
    // getline(file, description, "\n");

    while (getline(file, phoneNo, ',') &&
           getline(file, name, ',') &&
           getline(file, address, ',') &&
           getline(file, description, '\n'))
    {
        cout << "Phone number: " << phoneNo << endl;
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Description: " << description << endl;
    }
    file.close();
}

void temp::searchContact()
{
    cout << "Enter the phone number: ";
    getline(cin, search);

    file.open("data.csv", ios ::in);
    // getline(file, phoneNo, ",");
    // getline(file, name, ",");
    // getline(file, address, ",");
    // getline(file, description, "\n");

    while (getline(file, phoneNo, ',') &&
           getline(file, name, ',') &&
           getline(file, address, ',') &&
           getline(file, description, '\n'))
    {
        if (phoneNo == search)
        {
            cout << "Phone number: " << phoneNo << endl;
            cout << "Name: " << name << endl;
            cout << "Address: " << address << endl;
            cout << "Description: " << description << endl;
        }
    }
    file.close();
}
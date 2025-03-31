#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void register_user()
{
    string username, password;

    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your Password: ";
    cin >> password;

    ofstream outFile("students.txt", ios::app);
    if (outFile.is_open())
    {
        outFile << username << " " << password << "\n";
        outFile.close();
        cout << "Registration successful";
    }
    else
    {
        cout << "Error: Unable to open the file to write\n";
    }
}
void login_user()
{
    string username, password, fileUsername, filePassword;
    bool loginSuccess = false;

    cout << "=============Login============\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    ifstream inFile("students.txt");
    if (inFile.is_open())
    {
        while (inFile >> fileUsername >> filePassword)
        {
            if (fileUsername == username && filePassword == password)
            {
                loginSuccess = true;
                break;
            }
        }

        inFile.close();

        if (loginSuccess = true)
        {
            cout << "login Successful! Welcome, " << username;
        }
        else
        {
            cout << "Wrong credentials!";
        }
    }
    else
    {
        cout << "Error: Unable to operate on file";
    }
}

void menu()
{
    int choice;
    do
    {
        cout << "\n===============+===============\n";
        cout << "**Student management system**\n";
        cout << "===============+===============\n";
        cout << "1. Register\n2. Login\n3. Exit";
        cout << "\nEnter your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            register_user();
            break;
        case 2:
            login_user();
            break;
        case 3:
            cout << "Thank you for using this system";
            break;
        default:
            cout << "Kindly enter the right choice!";
            break;
        }

    } while (choice != 3);
}

int main()
{

    menu();

    return 0;
}
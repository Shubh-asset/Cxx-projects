#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

class temp
{
    string userName, Email, passWord;
    string searchName, searchPass, searchEmail;

    fstream file;

public:
    void login();
    void signUP();
    void forgot();
    void clearInputBuffer();
} obj;

int main()
{
    char choice;
    do
    {
        cout << "\n1. Login";
        cout << "\n2. Sign-up";
        cout << "\n3. Forgot password";
        cout << "\n4. Exit";
        cout << "\nEnter your Choice: ";

        cin >> choice;

        switch (choice)
        {
        case '1':
            obj.login();
            break;
        case '2':
            obj.signUP();
            break;
        case '3':
            obj.forgot();
            break;
        case '4':
            return 0;
            break;
        default:
            cout << "Invalid choice!";
        }
        obj.clearInputBuffer();
    } while (choice != '4');

    return 0;
}

void temp ::signUP()
{
    clearInputBuffer();
    cout << "\nEnter your Name: ";
    getline(cin, userName);
    cout << "Enter your email address: ";
    getline(cin, Email);
    cout << "Enter your Password: ";
    getline(cin, passWord);

    file.open("loginData.txt", ios ::out | ios ::app);
    if (file.is_open())
    {
        file << userName << "*" << Email << "*" << passWord << endl;
        file.close();
        cout << "Registration is sucessfull!";
    }
    else
    {
        cout << "Unable to open file for writing!\n";
    }
}

void temp ::login()
{
    clearInputBuffer();
    cout << "*********Login*********" << endl;
    cout << "Enter your username: ";
    getline(cin, searchName);
    cout << "Enter your Password: ";
    getline(cin, searchPass);

    bool found = false;

    file.open("loginData.txt", ios::in);
    if (file.is_open())
    {
        while (getline(file, userName, '*') &&
               getline(file, Email, '*') &&
               getline(file, passWord, '\n'))
        {
            if (userName == searchName && passWord == searchPass)
            {
                found = true;
                break;
            }
        }
        file.close();

        if (found)
        {
            cout << "\naccount login is successful!!";
            cout << "\nUsername: " << userName << endl;
            cout << "Email: " << Email << endl;
        }
        else
        {
            cout << "Password or username is incorrect";
        }
    }
    else
    {
        cout << "Error: unable to open file for reading!\n";
    }
}

//     while (!file.eof())
//     {
//         if (userName == searchName)
//         {
//             if (passWord == searchPass)
//             {
//                 cout << "\nAccount login is Successful!!";
//                 cout << "\nUsename: " << userName << endl;
//                 cout << "\nEmail: " << Email << endl;
//             }
//             else
//             {
//                 cout << "Password or Username is incorrect!";
//             }
//         }
//         getline(file, userName, '*');
//         getline(file, Email, '*');
//         getline(file, passWord, '\n');
//     }
//     file.close();
// }

void temp ::forgot()
{
    clearInputBuffer();
    cout << "\nEnter your Username: ";
    getline(cin, searchName);
    cout << "\nEnter you email address: ";
    getline(cin, searchEmail);

    bool found = false;

    file.open("loginData.txt", ios::in); // to check if the data is present in file or not

    if (file.is_open())
    {
        while (getline(file, userName, '*') &&
               getline(file, Email, '*') &&
               getline(file, passWord, '\n'))
        {
            if (userName == searchName && Email == searchEmail)
            {
                found = true;
                break;
            }
        }
        file.close();

        if (found)
        {
            cout << "\nAccount found...";
            cout << "\nYour password: " << passWord << endl;
        }
        else
        {
            cout << "Account not found!\n";
        }
    }
    else
    {
        cout << "Error: unable to open file for reading!\n";
    }

    // getline(file, userName, '*');
    // getline(file, Email, '*');
    // getline(file, passWord, '\n');

    // while (!file.eof())
    // {
    //     if (userName == searchName)
    //     {
    //         if (Email == searchEmail)
    //         {
    //             cout << "\nAccount found...!" << endl;
    //             cout << "Your Password : " << passWord << endl;
    //         }
    //         else
    //         {
    //             cout << "Not found...";
    //         }
    //     }
    //     else
    //     {
    //         cout << "\nNote found...!\n";
    //     }
    // }

    file.close();
}
void temp ::clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

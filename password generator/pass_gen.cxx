#include <iostream>
#include <cstdlib> // random function usage
#include <ctime>   //time ke accordingly random number generation
#include <string>

using namespace std;

string getPassword(int length)
{
    string Password = "";
    string characters = "aquickbrownfoxjumpsoverthelazydogAQUICKBROWNFOXJUMPSOVERTHELAZEDOG0123456789";
    int charSize = characters.size(); // Total available characters (26 lowercase + 26 uppercase + 10 digits = 62)
    srand(time(0));                   // Seeds the randomizer with current time to ensure different passwords each run
    int randomIndex;
    for (int i = 0; i < length; i++)
    {
        randomIndex = rand() % charSize;               // Random index within the character pool
        Password = Password + characters[randomIndex]; // Append a random character
    }
    return Password; // Returns the generated password
}

int main()
{
    int length;
    cout << "Enter the length of your password: ";
    cin >> length;

    string password = getPassword(length);
    cout << "Generated password: " << password;

    return 0;
}
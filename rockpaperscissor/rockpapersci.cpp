#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// typedef struct
// {
//     int player;
//     int computer;
//     int draw;
// } Game;

string choice;

void display_intro();
void game_play();

string determine_winner(string choice, string computer_ch);
string computer_ch();

int main()
{
    srand(time(0));

    display_intro();
    // game_play();
    game_play();

    return 0;
}
void display_intro()
{

    cout << "**Welcome to the Game!!**" << endl;
    cout << "1. Rock\n2. Paper\n3. Scissors\n4. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    /*for(char &c : choice)
    {
        c = tolower(c);
    }*/
}
void game_play()
{
    string computchoice = computer_ch();
    cout << "computer chose:" << computchoice << endl;

    string result = determine_winner(choice, computchoice);
    cout << result << endl;
}
// void game_play()
// {
//     switch (choice)
//     {
//     case 1:
//         cout << "Chose rock";
//         break;
//     case 2:
//         cout << "Chose Paper";
//         break;
//     case 3:
//         cout << "Scissors";
//         break;
//     case 4:
//         cout << "Thank you for playing, Come again";
//         break;
//     default:
//         cout << "kindly enter correct choice!";
//         break;
//     }
// }
string computer_ch()
{
    int choice = rand() % 3;
    if (choice == 0)
    {
        return "rock";
    }
    if (choice == 1)
    {
        return "Paper";
    }
    else
    {
        return "scissors";
    }
}
string determine_winner(string player, string computer)
{
    if (player == computer)
    {
        cout << "Its a tie" << endl;
    }
    else if (
        (player == "rock" && computer == "scissors") || (player == "paper" && computer == "rock" || player == "scissors" && computer == "paper"))
    {
        cout << "You Win!!" << endl;
    }
    else
    {
        return "computer wins!";
    }
}
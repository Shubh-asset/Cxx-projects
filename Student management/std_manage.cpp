#include <iostream>
#include <conio.h> //console input output
#include <limits>
using namespace std;

int i = 0;

struct Student
{
    int id;
    string name, grade;
    float marks, perc;
} s[25];

void clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void show()
{
    system("cls");
    cout << "\n\n\t\t\t *** Showing Record ***";
    if (i == 0)
    {
        cout << "\n\n *** No Record Found ***";
    }
    else
    {
        for (int a = 0; a < i; a++)
        {
            cout << "\n\n Student Id: " << s[a].id;
            cout << "\n\n Name: " << s[a].name;
            cout << "\n\n Marks: " << s[a].marks;
            cout << "\n\n Percentage: " << s[a].perc << "%";
            cout << "\n\n Grade: " << s[a].grade;
            cout << "\n\n ******************************";
        }
    }
}

void del()
{
    system("cls");
    cout << "\n\n\t\t\t *** Delete Record ***";
    if (i == 0)
    {
        cout << "\n\n *** No Record Found ***";
        getch();
        return;
    }

    int id;
    bool found = false;
    cout << "\n\n Enter Student Id to delete: ";

    // Input validation
    while (!(cin >> id))
    {
        cout << "Invalid input. Please enter a numeric ID: ";
        clearInputBuffer();
    }

    for (int a = 0; a < i; a++)
    {
        if (id == s[a].id)
        {
            // Shift all elements after the found one left by one
            for (int m = a; m < i - 1; m++)
            {
                s[m] = s[m + 1]; // This copies the entire struct at once
            }
            i--; // Decrement the global counter
            cout << "\n\n *** Record Deleted Successfully ***";
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\n *** Student ID not found!! ***";
    }
    getch();
}

// void del()
// {
//     system("cls");
//     cout << "\n\n\t\t\t *** Delete Record ***";
//     if (i == 0)
//     {
//         cout << "\n\n *** No Record Found ***";
//     }
//     else
//     {
//         int id, found = 0;
//         cout << "\n\n Enter Student Id: ";
//         cin >> id;

//         for (int a = 0; a < i; a++)
//         {
//             if (id == s[a].id)
//             {
//                 for (int m = a; m < i - 1; m++)
//                 {
//                     s[m].id = s[m + 1].id;
//                     s[m].name = s[m + 1].name;
//                     s[m].marks = s[m + 1].marks;
//                     s[m].perc = s[m + 1].perc;
//                     s[m].grade = s[m + 1].grade;
//                 }
//                 cout << "\n\n *** Record Deleted Successfully ***";
//                 found++;
//                 break;
//             }
//         }
//     }
// }

void update()
{
    system("cls");
    cout << "\n\n\t\t\t *** Update Record ***";
    if (i == 0)
    {
        cout << "\n\n *** No Record Found ***";
    }
    else
    {
        int id, found = 0;
        cout << "\n\n Enter Student Id: ";
        cin >> id;
        for (int a = 0; a < i; a++)
        {
            if (id == s[a].id)
            {
                cout << "\n Enter Student Name: ";
                cin >> s[a].name;
                cout << "\n Enter Student Marks: ";
                cin >> s[a].marks;

                s[a].perc = (s[a].marks / 100) * 100;

                if (s[a].perc >= 85 && s[a].perc <= 100)
                {
                    s[a].grade = "A+";
                }
                else if (s[a].perc >= 75 && s[a].perc <= 85)
                {
                    s[a].grade = "A";
                }
                else if (s[a].perc >= 65 && s[a].perc <= 75)
                {
                    s[a].grade = "B+";
                }
                else if (s[a].perc >= 50 && s[a].perc <= 65)
                {
                    s[a].grade = "B";
                }
                else if (s[a].perc >= 40 && s[a].perc <= 50)
                {
                    s[a].grade = "C";
                }
                else if (s[a].perc >= 33 && s[a].perc <= 40)
                {
                    s[a].grade = "D";
                }
                else if (s[a].perc < 33 && s[a].perc >= 0)
                {
                    s[a].grade = "F";
                }
                else
                {
                    cout << "Invalid Marks!";
                }

                found++;
            }
        }
        if (found == 0)
        {
            cout << "\n *** Student ID not found!! ***";
        }
    }
}

void search()
{
    system("cls");
    cout << "\n\n\t\t\t *** Search Record ***";
    if (i == 0)
    {
        cout << "\n\n *** No Record Found ***";
    }
    else
    {
        int id, found = 0;
        cout << "\n\n Enter Student Id: ";
        cin >> id;
        for (int a = 0; a < i; a++)
        {
            if (id == s[a].id)
            {
                cout << "\n  Name: " << s[a].name;
                cout << "\n  Marks: " << s[a].marks;
                cout << "\n  Percentage: " << s[a].perc;
                cout << "\n Grade: " << s[a].grade;
                found++;
            }
        }
        if (found == 0)
        {
            cout << "\n *** Student ID not found!! ***";
        }
    }
}

void insert()
{
    cout << "\n\n\t\t\t *** Insert Record ***";
    cout << "\n Enter Student Id: ";
    cin >> s[i].id;
    cout << "\n Enter Student Name: ";
    cin >> s[i].name;
    cout << "\n Enter Student Marks: ";
    cin >> s[i].marks;

    s[i].perc = (s[i].marks / 100) * 100;

    if (s[i].perc >= 85 && s[i].perc <= 100)
    {
        s[i].grade = "A+";
    }
    else if (s[i].perc >= 75 && s[i].perc <= 85)
    {
        s[i].grade = "A";
    }
    else if (s[i].perc >= 65 && s[i].perc <= 75)
    {
        s[i].grade = "B+";
    }
    else if (s[i].perc >= 50 && s[i].perc <= 65)
    {
        s[i].grade = "B";
    }
    else if (s[i].perc >= 40 && s[i].perc <= 50)
    {
        s[i].grade = "C";
    }
    else if (s[i].perc >= 33 && s[i].perc <= 40)
    {
        s[i].grade = "D";
    }
    else if (s[i].perc < 33 && s[i].perc >= 0)
    {
        s[i].grade = "F";
    }
    else
    {
        cout << "Invalid Marks!";
    }

    i++;
    cout << "\n\n *** Record Inserted Successfully ***";
}

int main()
{
p: // label
    system("cls");
    int choice;
    cout << "\n\n\t\t\t*** Student Management System ***";
    cout << "\n\n 1. Insert record";
    cout << "\n\n 2. Search Record";
    cout << "\n\n 3. Update Record";
    cout << "\n\n 4. Delete Record";
    cout << "\n\n 5. Show Record";
    cout << "\n\n 6. Exit";
    cout << "\n\n Enter your Choice -> ";

    cin >> choice;

    switch (choice)
    {
    case 1:
        insert();
        break;
    case 2:
        search();
        break;
    case 3:
        update();
        break;
    case 4:
        del();
        break;
    case 5:
        show();
        break;
    case 6:
        exit(0);
    default:
        cout << "\n\n*** Invalid Choice ***";
    }
    getch();
    goto p;

    return 0;
}
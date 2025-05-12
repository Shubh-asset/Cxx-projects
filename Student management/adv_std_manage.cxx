#include <iostream>
#include <conio.h>
#include <limits> // for input validation
using namespace std;

int i = 0; // Global counter for students

struct Student
{
    int id;
    string name, grade;
    float marks, perc;
} s[25]; // Fixed-size array for simplicity

// Function to clear input buffer
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
            cout << "\n Name: " << s[a].name;
            cout << "\n Marks: " << s[a].marks;
            cout << "\n Percentage: " << s[a].perc << "%";
            cout << "\n Grade: " << s[a].grade;
            cout << "\n ******************************";
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

void update()
{
    system("cls");
    cout << "\n\n\t\t\t *** Update Record ***";
    if (i == 0)
    {
        cout << "\n\n *** No Record Found ***";
        getch();
        return;
    }

    int id;
    bool found = false;
    cout << "\n\n Enter Student Id to update: ";

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
            cout << "\n Enter Student Name: ";
            clearInputBuffer();
            getline(cin, s[a].name);

            cout << "\n Enter Student Marks (0-100): ";
            while (!(cin >> s[a].marks) || s[a].marks < 0 || s[a].marks > 100)
            {
                cout << "Invalid marks. Enter value between 0-100: ";
                clearInputBuffer();
            }

            s[a].perc = s[a].marks; // Direct assignment since marks are out of 100

            // Simplified grade assignment
            if (s[a].perc >= 85)
                s[a].grade = "A+";
            else if (s[a].perc >= 75)
                s[a].grade = "A";
            else if (s[a].perc >= 65)
                s[a].grade = "B+";
            else if (s[a].perc >= 50)
                s[a].grade = "B";
            else if (s[a].perc >= 40)
                s[a].grade = "C";
            else if (s[a].perc >= 33)
                s[a].grade = "D";
            else
                s[a].grade = "F";

            cout << "\n\n *** Record Updated Successfully ***";
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

void search()
{
    system("cls");
    cout << "\n\n\t\t\t *** Search Record ***";
    if (i == 0)
    {
        cout << "\n\n *** No Record Found ***";
        getch();
        return;
    }

    int id;
    bool found = false;
    cout << "\n\n Enter Student Id to search: ";

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
            cout << "\n\n Student Id: " << s[a].id;
            cout << "\n Name: " << s[a].name;
            cout << "\n Marks: " << s[a].marks;
            cout << "\n Percentage: " << s[a].perc << "%";
            cout << "\n Grade: " << s[a].grade;
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

void insert()
{
    system("cls");
    cout << "\n\n\t\t\t *** Insert Record ***";

    if (i >= 25)
    {
        cout << "\n\n *** Database full! Cannot add more records ***";
        getch();
        return;
    }

    cout << "\n Enter Student Id: ";
    while (!(cin >> s[i].id))
    {
        cout << "Invalid input. Please enter a numeric ID: ";
        clearInputBuffer();
    }

    cout << "\n Enter Student Name: ";
    clearInputBuffer();
    getline(cin, s[i].name);

    cout << "\n Enter Student Marks (0-100): ";
    while (!(cin >> s[i].marks) || s[i].marks < 0 || s[i].marks > 100)
    {
        cout << "Invalid marks. Enter value between 0-100: ";
        clearInputBuffer();
    }

    s[i].perc = s[i].marks; // Direct assignment since marks are out of 100

    // Simplified grade assignment
    if (s[i].perc >= 85)
        s[i].grade = "A+";
    else if (s[i].perc >= 75)
        s[i].grade = "A";
    else if (s[i].perc >= 65)
        s[i].grade = "B+";
    else if (s[i].perc >= 50)
        s[i].grade = "B";
    else if (s[i].perc >= 40)
        s[i].grade = "C";
    else if (s[i].perc >= 33)
        s[i].grade = "D";
    else
        s[i].grade = "F";

    i++;
    cout << "\n\n *** Record Inserted Successfully ***";
    getch();
}

int main()
{
    while (true)
    {
        system("cls");
        int choice;
        cout << "\n\n\t\t\t*** Student Management System ***";
        cout << "\n\n 1. Insert record";
        cout << "\n\n 2. Search Record";
        cout << "\n\n 3. Update Record";
        cout << "\n\n 4. Delete Record";
        cout << "\n\n 5. Show All Records";
        cout << "\n\n 6. Exit";
        cout << "\n\n Enter your Choice -> ";

        // Input validation for menu choice
        while (!(cin >> choice) || choice < 1 || choice > 6)
        {
            cout << "Invalid choice. Please enter 1-6: ";
            clearInputBuffer();
        }

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
            getch();
            break;
        case 6:
            exit(0);
        }
    }

    return 0;
}

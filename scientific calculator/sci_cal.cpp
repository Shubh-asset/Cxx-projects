#include <iostream>
#include <cmath>
using namespace std;

int num1, num2;

int enter_nu()
{
    cout << "Enter your numbers:\n";
    cout << "Number 1: ";
    cin >> num1;
}
int expo_nent()
{
    cout << "\nRaises one to the power of another" << endl;
    enter_nu();
    cout << "Number 2: ";
    cin >> num2;
    int result = pow(num1, num2);
    cout << "Result: " << result << endl;
}
int square_root()
{
    cout << "\nFinds square root of a number if it exists." << endl;
    enter_nu();
    int result = sqrt(num1);
    cout << "Result: " << result << endl;
}
double nat_exp()
{
    cout << "\nRaises the digit to the power of 'e'\n";
    enter_nu();
    float result = exp(num1);
    cout << "Result: " << result << endl;
}
double logarithmic()
{
    int choice;
    cout << "\nFinds the logarithmic value of number to the base 10\n";
    enter_nu();
    cout << "Choose the Base value\n1. base 10\n2. base 2" << endl;
    cin >> choice;

    if (choice == 1)
    {
        float result = log10(num1);
        cout << "Result: " << result;
    }
    else if (choice == 2)
    {
        float result = log2(num1);
        cout << "Result: " << result;
    }
    else
    {
        float result = log10(num1);
        cout << "Result: " << result;
    }
}
double trigono_met()
{
    int choice, result;
    cout << "\nLet's find trigometric questions in C++";
    cout << "Select the operations please:";
    cout << "\n1. Sine\n2. Cosine\n3. Tangent\n4. Inverse sine\n5. Inverse Cosine\n6. Inverse Tangent";
    cout << "\nEnter your choice: ";
    cin >> choice;
    enter_nu();
    switch (choice)
    {
    case 1:
        result = sin(num1);
        cout << "Result: " << result;
        break;
    case 2:
        result = cos(num1);
        cout << "Result: " << result;
        break;
    case 3:
        result = tan(num1);
        cout << "Result: " << result;
        break;
    case 4:
        result = asin(num1);
        cout << "Result: " << result;
        break;
    case 5:
        result = acos(num1);
        cout << "Result: " << result;
        break;
    case 6:
        result = atan(num1);
        cout << "Result: " << result;
        break;
    default:
        cout << "Enter Correct choice please!";
        break;
    }
}

int main()
{
    int oper;
    do
    {
        cout << "\nWelcome to the scientific calculator" << endl;
        cout << "\nOperation you can choose from" << endl;
        cout << "1. Exponentiation(power)\n2. Square root\n3. Natural exponent\n4. Logarithms\n5. Trigonometric functions\n6. Exit";

        cout << "\nEnter your operation: ";
        cin >> oper;

        switch (oper)
        {
        case 1:
            expo_nent();
            break;
        case 2:
            square_root();
            break;
        case 3:
            nat_exp();
            break;
        case 4:
            logarithmic();
            break;
        case 5:
            trigono_met();
            break;
        case 6:
            cout << "Exiting the program, come again!!";
            break;
        default:
            cout << "Enter correct choice";
            break;
        }
    } while (oper != 6);

    return 0;
}
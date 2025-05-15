#include <iostream>
#include <fstream>

using namespace std;

class temp
{

    string itemID, itemName;
    int itemQuantity, itemPrice;
    fstream file, file1; // updated data resides in new file
    int totalamount, quantity, itemrate;
    string search;
    char _choice;

public:
    void addProduct(void);
    void viewProduct(void);
    void buyProduct(void);

} obj;

int main()
{
    char choice;
    cout << "press 1 --> Start Shopping" << endl;
    cout << "press 0 --> Exit" << endl;
    cin >> choice;

    switch (choice)
    {
    case 'A':
        obj.addProduct();
        break;

    case 1:
        obj.viewProduct();
        obj.buyProduct();
        break;

    case 0:
        system("exit");
        break;

    default:
        cout << "Invalid Selection...!";
        break;
    }

    return 0;
}

void temp ::addProduct()
{
    cout << "Enter the Product ID: ";
    cin >> itemID;
    cout << "Enter the Product Name: ";
    cin >> itemName;
    cout << "Enter the Product Quantity: ";
    cin >> itemQuantity;
    cout << "Enter the Product Price: ";
    cin >> itemPrice;

    file.open("productdet.txt", ios::out | ios::app);
    file << itemID << "*" << itemName << "*" << itemQuantity << "*" << itemPrice << endl;

    file.close();
}

void temp ::viewProduct()
{
    file.open("productdet.txt", ios::in);
    while (!file.eof())
    {
        file >> itemID >> itemName >> itemQuantity >> itemPrice;
        cout << "--------------------------------------------" << endl;
        cout << "Product ID\t\tProduct Name\t\tProduct Quantity\t\tProduct Price" << endl;
        cout << itemID << "\t\t" << itemName << "\t\t" << itemQuantity << "\t\t" << itemPrice;
        cout << "--------------------------------------------" << endl;
    }
    file.close();
}

void temp ::buyProduct()
{
    _choice == 'y';

    while (_choice == 'y')
    {

        file.open("productdet.txt", ios ::in);
        file1.open("productdet1.txt", ios ::out | ios ::app);

        file >> itemID >> itemName >> itemQuantity >> itemPrice;

        cout << "Enter product ID: ";
        cin >> search;
        cout << "Enter the Quantity you want to buy: ";
        cin >> quantity;

        while (!file.eof())
        {
            if (itemID == search)
            {
                itemQuantity = itemQuantity - quantity;
                file1 << itemID << "\t" << itemName << "\t" << itemQuantity << "\t" << itemPrice << endl;

                itemrate = quantity * itemPrice;
                totalamount = totalamount + itemrate;

                cout << "-----------product amount-----------";
                cout << "Total Purchase amount :: " << totalamount << endl;
                cout << "------------------------------------" << endl;
            }
            else
            {
                file1 << itemID << "\t" << itemName << "\t" << itemQuantity << "\t" << itemPrice << endl;
            }
            file >> itemID >> itemName >> itemQuantity >> itemPrice;
        }
        file.close();
        file1.close();
        remove("productdet.txt");
        rename("productdet1.txt", "productdet.txt");

        cout << "Continue shopping (Y/N)?" << endl;
        cin >> _choice;
    }
}
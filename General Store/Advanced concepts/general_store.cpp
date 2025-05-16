#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <memory> //unique pointer lib
#include <algorithm>
#include <stdexcept>
#include <iomanip>

using namespace std;

class Product
{
    string id;    // member variables
    string name;  // member variables
    int quantity; // member variables
    double price; // member variables

public:
    Product(string &id, string &name, int &quantity, double &price)
    {
        this->id = id;
        this->name = name;
        this->quantity = quantity;
        this->price = price;
    }
    // functions: Getters
    // by using 'const', This function does not modify any member variables of the object.
    string getId() const { return id; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }

    // Setters
    void setQuantity(int q)
    {
        quantity = q;
    }
    void setPrice(double p)
    {
        price = p;
    }
    void display() const // this function prints the product details in and aligned and formatted way using I/O manipulators from the <iomanip> header
    {
        cout << left << setw(15) << id
             << setw(25) << name
             << setw(10) << quantity
             << "$" << fixed << setprecision(2) << price << endl;
    }
    // left aligned
    // each column is fixed width
};

class Inventory
{
    vector<unique_ptr<Product>> products;
    // ifstream file;
    string filename = "inventory.dat";

    void loadfromFile()
    {
        // ifstream file(filename, ios::binary)
        ifstream file(filename, ios::binary);
        if (!file)
            return; // check if the file is opened successfully

        string id, name;
        int quantity;
        double price;

        while (file >> id >> name >> quantity >> price) // reading from a file
        {
            products.push_back(make_unique<Product>(id, name, quantity, price));
        }
    }
    void saveToFile() // This function writes product data to a file (most likely inventory.dat) from a vector of unique_ptr<Product>.
    {
        ofstream file(filename, ios::binary);
        for (const auto &product : products)
        {
            file << product->getId() << " "
                 << product->getName() << " "
                 << product->getQuantity() << " "
                 << product->getPrice() << "\n";
        }
    }

public:
    Inventory() // constructor
    {
        loadfromFile(); // loading product data from the file
    }
    ~Inventory() // destructor|called automatically when inventory object is destroyed
    {
        saveToFile(); // so that all the current product data saved to a file
    }

    void addProduct()
    {
        string id, name;
        int quantity;
        double price;

        cout << "\nEnter Product ID: ";
        cin >> id;
        cout << "Enter Product Name: ";
        cin.ignore(); // clears the leftover newline character from the input buffer
        getline(cin, name);
        cout << "Enter Quantity: ";
        cin >> quantity;
        cout << "Enter Price: $";
        cin >> price;

        products.push_back(make_unique<Product>(id, name, quantity, price));
        cout << "Product added successfully!\n";
    }

    void displayALL() const
    {
        if (products.empty())
        {
            cout << "\nNo products have been found\n";
            return;
        }
        else
        {
            cout << "\n"
                 << string(70, '-') << "\n"
                 << left << setw(15) << "ID"
                 << setw(25) << "Name"
                 << setw(10) << "Quantity"
                 << "Price" << endl;
            cout << string(70, '-') << "\n";

            for (const auto &product : products)
            {
                product->display();
            }
            cout << string(70, '-') << "\n";
        }
    }
    // search utility inside the inventory class, it looks for the product and returns a pointer to it if found
    Product *findProduct(const string &id)
    { // find_if: standard algorithm from library <algorithm>
        // it loops through the vector and applies the lambda function to each element
        auto i = find_if(products.begin(), products.end(),
                         [&id](const unique_ptr<Product> &p)
                         { return p->getId() == id; });
        /*lambda: [&id]*/

        return (i != products.end()) ? i->get() : nullptr;
        // i=iterator, if it didnt reach the end we found a match
        // it->get()
    }

    void processOrder()
    {
        vector<pair<Product *, int>> cart; // cart: stores item being purchased
        char choice;
        double total = 0.0;
        do
        {
            string id;
            int quantity;

            displayALL();
            cout << "\nEnter Product ID to purchase: ";
            cin >> id;
            Product *product = findProduct(id);
            if (!product)
            {
                cout << "Product not found!\n";
                continue;
            }
            cout << "Enter Quantity: ";
            cin >> quantity;
            if (quantity <= 0)
            {
                cout << "Invalid quantity!";
                continue;
            }
            if (quantity > product->getQuantity()) // checks if the requested quantity exceeds whats available
            {
                cout << "Insufficient stock! Available: " << product->getQuantity() << endl;
                continue;
            }
            // emplace_back: adds a new item to the vector
            cart.emplace_back(product, quantity);
            total += quantity * product->getPrice();
            // product is pointer to the selected Product
            // quantity: how many number of products user wants to buy
            cout << "\nAdd another product? (y/n)";
            cin >> choice;
        } while (toupper(choice) == 'Y');

        // process the order
        if (!cart.empty())
        {
            cout << "\n\nReceipt:\n";
            cout << string(50, '-') << "\n";
            cout << left << setw(25) << "Product"
                 << setw(10) << "Qty"
                 << setw(15) << "Price"
                 << "Total" << endl;
            cout << string(50, '-') << "\n";
            // for loop processes each item in the shopping cart, displays a detailed bill and updatess inventory accordingly
            for (const auto &item : cart) // iterates through each product in shopping cart
            {
                // extract product and quantity
                Product *product = item.first; // pointer to the product
                int qty = item.second;         // quantity purchased
                double itemTotal = qty * product->getPrice();

                cout << left << setw(25) << product->getName()
                     << setw(10) << qty
                     << "$" << setw(14) << fixed << setprecision(2) << product->getPrice()
                     << "$" << itemTotal << endl;
                product->setQuantity(product->getQuantity() - qty);
            }

            cout << string(50, '-') << "\n";
            cout << right << setw(45) << "TOTAL: $" << total << endl;
            cout << string(50, '-') << "\n";
            cout << "Thank you for your purchase!\n";
        }
    }
};

class StoreManager
{
private:
    Inventory inventory;

public:
    void showMenu()
    {
        while (true)
        {
            cout << "\n===== Store Management System =====\n";
            cout << "1. Add Product\n";
            cout << "2. View Inventory\n";
            cout << "3. Process Order\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";

            int choice;
            cin >> choice;

            try // wraps a code that might throw an exception
            {
                switch (choice)
                {
                case 1:
                    inventory.addProduct();
                    break;
                case 2:
                    inventory.displayALL();
                    break;
                case 3:
                    inventory.processOrder();
                    break;
                case 4:
                    cout << "Exiting system...\n";
                    return;
                default:
                    throw invalid_argument("Invalid choice!"); // exception handling
                }
            }
            catch (const exception &e)
            {
                cerr << "Error: " << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flushes the input buffer using cin.ignore() so the next input works cleanly
            }
        }
    }
};

int main()
{
    StoreManager manager;
    manager.showMenu();
    return 0;
}
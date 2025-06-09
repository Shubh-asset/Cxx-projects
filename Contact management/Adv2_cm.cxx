#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <mysql/mysql.h>
#include <termios.h>
#include <unistd.h>

using namespace std;

// Database configuration - adjust these for your MySQL setup
const string DB_HOST = "localhost";
const string DB_USER = "root";
const string DB_PASS = "password";
const string DB_NAME = "contact_manager";

// Helper function for secure password input
string getPassword(const string& prompt = "Enter password: ") {
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    cout << prompt;
    string password;
    getline(cin, password);
    cout << endl;

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return password;
}

// Contact class with enhanced features
class Contact {
private:
    int id;
    string phone;
    string name;
    string email;
    string address;
    string notes;

public:
    Contact(int i, string ph, string n, string e, string addr, string nt)
        : id(i), phone(move(ph)), name(move(n)), email(move(e)), 
          address(move(addr)), notes(move(nt)) {}

    // Factory method pattern
    static Contact createFromInput() {
        string phone, name, email, address, notes;

        cout << "Enter phone number: ";
        getline(cin, phone);

        cout << "Enter name: ";
        getline(cin, name);

        cout << "Enter email: ";
        getline(cin, email);

        cout << "Enter address: ";
        getline(cin, address);

        cout << "Enter notes: ";
        getline(cin, notes);

        return Contact(0, phone, name, email, address, notes);
    }

    void display() const {
        cout << "\nID: " << id
             << "\nName: " << name
             << "\nPhone: " << phone
             << "\nEmail: " << email
             << "\nAddress: " << address
             << "\nNotes: " << notes << "\n\n";
    }

    // Getters
    int getId() const { return id; }
    string getPhone() const { return phone; }
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getAddress() const { return address; }
    string getNotes() const { return notes; }
};

// Database connection handler using RAII
class Database {
private:
    MYSQL* connection;

public:
    Database() {
        connection = mysql_init(nullptr);
        if (!mysql_real_connect(connection, DB_HOST.c_str(), DB_USER.c_str(), 
                               DB_PASS.c_str(), DB_NAME.c_str(), 0, nullptr, 0)) {
            throw runtime_error("MySQL connection error: " + string(mysql_error(connection)));
        }
    }

    ~Database() {
        mysql_close(connection);
    }

    MYSQL* getConnection() { return connection; }
};

// Singleton Contact Manager
class ContactManager {
private:
    static unique_ptr<ContactManager> instance;
    Database db;

    ContactManager() {
        createTableIfNotExists();
    }

    void createTableIfNotExists() {
        const char* query = "CREATE TABLE IF NOT EXISTS contacts ("
                            "id INT AUTO_INCREMENT PRIMARY KEY,"
                            "phone VARCHAR(20) NOT NULL UNIQUE,"
                            "name VARCHAR(100) NOT NULL,"
                            "email VARCHAR(100),"
                            "address TEXT,"
                            "notes TEXT)";
        
        if (mysql_query(db.getConnection(), query)) {
            throw runtime_error("Table creation failed: " + string(mysql_error(db.getConnection())));
        }
    }

public:
    static ContactManager& getInstance() {
        if (!instance) {
            instance = make_unique<ContactManager>();
        }
        return *instance;
    }

    // Delete copy operations
    ContactManager(const ContactManager&) = delete;
    ContactManager& operator=(const ContactManager&) = delete;

    void addContact(const Contact& contact) {
        string query = "INSERT INTO contacts (phone, name, email, address, notes) VALUES ('" +
                      escapeString(contact.getPhone()) + "', '" +
                      escapeString(contact.getName()) + "', '" +
                      escapeString(contact.getEmail()) + "', '" +
                      escapeString(contact.getAddress()) + "', '" +
                      escapeString(contact.getNotes()) + "')";

        if (mysql_query(db.getConnection(), query.c_str())) {
            throw runtime_error("Insert failed: " + string(mysql_error(db.getConnection())));
        }
    }

    vector<Contact> getAllContacts() {
        vector<Contact> contacts;
        string query = "SELECT * FROM contacts ORDER BY name";
        
        if (mysql_query(db.getConnection(), query.c_str())) {
            throw runtime_error("Query failed: " + string(mysql_error(db.getConnection())));
        }

        MYSQL_RES* result = mysql_store_result(db.getConnection());
        if (!result) return contacts;

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result))) {
            contacts.emplace_back(
                stoi(row[0]), // id
                row[1] ? row[1] : "", // phone
                row[2] ? row[2] : "", // name
                row[3] ? row[3] : "", // email
                row[4] ? row[4] : "", // address
                row[5] ? row[5] : ""  // notes
            );
        }
        mysql_free_result(result);
        return contacts;
    }

    vector<Contact> searchContacts(const string& term) {
        vector<Contact> results;
        string query = "SELECT * FROM contacts WHERE name LIKE '%" + escapeString(term) + 
                       "%' OR phone LIKE '%" + escapeString(term) + "%'";
        
        if (mysql_query(db.getConnection(), query.c_str())) {
            throw runtime_error("Search failed: " + string(mysql_error(db.getConnection())));
        }

        MYSQL_RES* result = mysql_store_result(db.getConnection());
        if (!result) return results;

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result))) {
            results.emplace_back(
                stoi(row[0]), // id
                row[1] ? row[1] : "", // phone
                row[2] ? row[2] : "", // name
                row[3] ? row[3] : "", // email
                row[4] ? row[4] : "", // address
                row[5] ? row[5] : ""  // notes
            );
        }
        mysql_free_result(result);
        return results;
    }

private:
    string escapeString(const string& input) {
        char* output = new char[input.length() * 2 + 1];
        mysql_real_escape_string(db.getConnection(), output, input.c_str(), input.length());
        string result(output);
        delete[] output;
        return result;
    }
};

unique_ptr<ContactManager> ContactManager::instance = nullptr;

// Improved UI with clear sections
void displayMenu() {
    cout << "\n===== Contact Manager =====\n"
         << "1. Add New Contact\n"
         << "2. View All Contacts\n"
         << "3. Search Contacts\n"
         << "4. Exit\n"
         << "==========================\n"
         << "Enter your choice: ";
}

int main() {
    try {
        // Initialize MySQL connection
        cout << "Connecting to database...\n";
        auto& manager = ContactManager::getInstance();
        cout << "Connected successfully!\n";

        while (true) {
            displayMenu();
            int choice;
            cin >> choice;
            cin.ignore(); // Clear input buffer

            switch (choice) {
                case 1: {
                    Contact contact = Contact::createFromInput();
                    manager.addContact(contact);
                    cout << "Contact added successfully!\n";
                    break;
                }
                case 2: {
                    auto contacts = manager.getAllContacts();
                    if (contacts.empty()) {
                        cout << "No contacts found.\n";
                    } else {
                        cout << "\n=== All Contacts ===\n";
                        for (const auto& contact : contacts) {
                            contact.display();
                        }
                    }
                    break;
                }
                case 3: {
                    cout << "Enter search term: ";
                    string term;
                    getline(cin, term);
                    auto results = manager.searchContacts(term);
                    if (results.empty()) {
                        cout << "No matching contacts found.\n";
                    } else {
                        cout << "\n=== Search Results ===\n";
                        for (const auto& contact : results) {
                            contact.display();
                        }
                    }
                    break;
                }
                case 4:
                    cout << "Goodbye!\n";
                    return 0;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}
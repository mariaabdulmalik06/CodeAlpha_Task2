// LOGIN SYSTEM.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
using namespace std;

// File to store credentials
const string USER_FILE = "users.txt";

// Load users from file into a map
unordered_map<string, string> loadUsers() {
    unordered_map<string, string> users;
    ifstream infile(USER_FILE);
    string line, username, password;

    while (getline(infile, line)) {
        istringstream iss(line);
        if (getline(iss, username, ',') && getline(iss, password)) {
            users[username] = password;
        }
    }

    infile.close();
    return users;
}

// Save a new user to the file
void saveUser(const string& username, const string& password) {
    ofstream outfile(USER_FILE, ios::app);
    outfile << username << "," << password << endl;
    outfile.close();
}

// Registration function
void registerUser() {
    string username, password;
    unordered_map<string, string> users = loadUsers();

    cout << "\n--- User Registration ---\n";
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

    // Input validation
    if (username.empty() || password.empty()) {
        cout << " Username and password cannot be empty.\n";
        return;
    }

    // Check for duplicate username
    if (users.find(username) != users.end()) {
        cout << " Username already exists. Try a different one.\n";
        return;
    }

    // Save the user
    saveUser(username, password);
    cout << " Registration successful!\n";
}

// Login function
void loginUser() {
    string username, password;
    unordered_map<string, string> users = loadUsers();

    cout << "\n--- User Login ---\n";
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

    if (users.find(username) != users.end() && users[username] == password) {
        cout << " Login successful! Welcome, " << username << "!\n";
    } else {
        cout << " Invalid username or password.\n";
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
	int choice;

    while (true) {
        cout << "\n===== User System Menu =====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore(); // clear buffer

        if (choice == 1) {
            registerUser();
        } else if (choice == 2) {
            loginUser();
        } else if (choice == 3) {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << " Invalid option. Try again.\n";
        }
    }
	system("pause");
	return 0;
}


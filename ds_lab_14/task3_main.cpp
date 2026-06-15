/*
 * File    : main.cpp
 * Task    : Task 3 — User ID-Password System
 * Desc    : Menu-driven driver that demonstrates the MaxHeap (ID storage)
 *           and AVLTree (ID-Password pair storage) working together.
 * Section : D20 | Spring 2026
 */

#include <iostream>
#include <iomanip>
#include <string>
#include "MaxHeap.h"
#include "AVLTree.h"
using namespace std;

// ======================== GLOBAL INSTANCES ========================

MaxHeap ID;
AVLTree password;

// ======================== MENU FUNCTIONS ========================

void addUser() {
    string id, pw;
    cout << "\n  Enter User ID   : ";  cin >> id;

    if (ID.contains(id)) {
        cout << "  [!] User ID already exists.\n";
        return;
    }

    cout << "  Enter Password  : ";  cin >> pw;
    ID.insert(id);
    password.insert(id, pw);
    cout << "  [+] User '" << id << "' added successfully.\n";
}

void removeUser() {
    string id;
    cout << "\n  Enter User ID to remove: ";  cin >> id;

    bool fromHeap = ID.remove(id);
    bool fromTree = password.remove(id);

    if (fromHeap && fromTree)
        cout << "  [-] User '" << id << "' removed successfully.\n";
    else
        cout << "  [!] User ID not found.\n";
}

void searchPassword() {
    string id;
    cout << "\n  Enter User ID to search: ";  cin >> id;

    string pw = password.searchPassword(id);
    if (pw.empty())
        cout << "  [!] User ID not found.\n";
    else
        cout << "  [✓] Password for '" << id << "': " << pw << "\n";
}

void displayTable() {
    const int MAX = 200;
    string ids[MAX], pws[MAX];
    int count = 0;
    password.getAllSorted(ids, pws, count);

    if (count == 0) { cout << "\n  No users registered.\n"; return; }

    const int W = 22;
    string sep(W * 2 + 7, '-');

    cout << "\n  " << sep << "\n";
    cout << "  | " << left << setw(W) << "User ID"
         << " | "  << setw(W) << "Password" << " |\n";
    cout << "  " << sep << "\n";
    for (int i = 0; i < count; i++) {
        cout << "  | " << left << setw(W) << ids[i]
             << " | "  << setw(W) << pws[i] << " |\n";
    }
    cout << "  " << sep << "\n";
}

// ======================== MAIN ========================

int main() {
    int choice;
    do {
        cout << "\n======= User ID-Password System =======\n";
        cout << "  1. Add User\n";
        cout << "  2. Remove User\n";
        cout << "  3. Search Password by User ID\n";
        cout << "  4. Display All Users\n";
        cout << "  0. Exit\n";
        cout << "=======================================\n";
        cout << "  Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addUser();        break;
            case 2: removeUser();     break;
            case 3: searchPassword(); break;
            case 4: displayTable();   break;
            case 0: cout << "  Goodbye!\n"; break;
            default: cout << "  [!] Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}

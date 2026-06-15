/*
 * File    : main.cpp
 * Task    : Task 5 — Hash Table of BSTs
 * Desc    : Tests add, search, and remove on a Node*[] hash table.
 *           Each bucket holds the root of an independent BST.
 *           Demonstrates collision handling (multiple strings in one bucket)
 *           and correctness of search before and after removal.
 * Section : D20 | Spring 2026
 */

#include <iostream>
#include <string>
#include "BST.h"
#include "HashBST.h"
using namespace std;

// ======================== MAIN ========================

int main() {
    cout << "===== Task 5: Hash Table of BSTs =====\n";

    const int TABLE_SIZE = 7;
    Node* table[TABLE_SIZE] = {nullptr};

    // --- add ---
    cout << "\n-- add --\n";
    add(table, TABLE_SIZE, "apple");
    add(table, TABLE_SIZE, "mango");
    add(table, TABLE_SIZE, "banana");
    add(table, TABLE_SIZE, "cherry");
    add(table, TABLE_SIZE, "grape");
    add(table, TABLE_SIZE, "kiwi");
    add(table, TABLE_SIZE, "melon");
    add(table, TABLE_SIZE, "apricot");   // collision → same bucket as another string, stored in same BST
    add(table, TABLE_SIZE, "plum");

    displayTable(table, TABLE_SIZE);

    // --- search ---
    cout << "\n-- search --\n";
    string queries[] = {"banana", "grape", "orange", "kiwi", "xyz"};
    for (const string& q : queries) {
        cout << "  search(\"" << q << "\") -> "
             << (search(table, TABLE_SIZE, q) ? "FOUND" : "NOT FOUND") << "\n";
    }

    // --- remove ---
    cout << "\n-- remove --\n";
    string toRemove[] = {"banana", "orange", "grape"};
    for (const string& r : toRemove) {
        string result = remove(table, TABLE_SIZE, r);
        if (result.empty())
            cout << "  remove(\"" << r << "\") -> NOT FOUND\n";
        else
            cout << "  remove(\"" << r << "\") -> removed \"" << result << "\"\n";
    }

    displayTable(table, TABLE_SIZE);

    // --- search after removal ---
    cout << "\n-- search after removal --\n";
    cout << "  search(\"banana\") -> "
         << (search(table, TABLE_SIZE, "banana") ? "FOUND" : "NOT FOUND") << "\n";
    cout << "  search(\"grape\")  -> "
         << (search(table, TABLE_SIZE, "grape")  ? "FOUND" : "NOT FOUND") << "\n";
    cout << "  search(\"apple\")  -> "
         << (search(table, TABLE_SIZE, "apple")  ? "FOUND" : "NOT FOUND") << "\n";

    return 0;
}

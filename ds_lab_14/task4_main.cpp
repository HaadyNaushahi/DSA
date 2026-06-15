/*
 * File    : main.cpp
 * Task    : Task 4 — Hashing Utility Functions
 * Desc    : Tests every function from HashFunctions.h with clear labeled output.
 * Section : D20 | Spring 2026
 */

#include <iostream>
#include <string>
#include "HashFunctions.h"
using namespace std;

// ======================== MAIN ========================

int main() {
    cout << "===== Task 4: Hashing Functions =====\n";

    // --- getIndex ---
    cout << "\n-- getIndex --\n";
    cout << "  getIndex(25, 7)  = " << getIndex(25, 7)  << "  (25 % 7 = 4)\n";
    cout << "  getIndex(100, 9) = " << getIndex(100, 9) << "  (100 % 9 = 1)\n";

    // --- getLinearKey ---
    cout << "\n-- getLinearKey --\n";
    cout << "  getLinearKey(25, 7, 2) = " << getLinearKey(25, 7, 2) << "  ((4+2)%7 = 6)\n";
    cout << "  getLinearKey(25, 7, 5) = " << getLinearKey(25, 7, 5) << "  ((4+5)%7 = 2)\n";

    // --- getQuardKey ---
    cout << "\n-- getQuardKey --\n";
    cout << "  getQuardKey(25, 7, 2) = " << getQuardKey(25, 7, 2) << "  ((4+4)%7 = 1)\n";
    cout << "  getQuardKey(25, 7, 3) = " << getQuardKey(25, 7, 3) << "  ((4+9)%7 = 6)\n";

    // --- getCode ---
    cout << "\n-- getCode --\n";
    cout << "  getCode(25, 7, 2) = " << getCode(25, 7, 2)
         << "  ((4 + 2*getQuardKey(25,7,1)) % 7)\n";

    // --- getHashCode ---
    cout << "\n-- getHashCode --\n";
    char s1[] = "hello";
    char s2[] = "abc";
    char s3[] = "haady";
    cout << "  getHashCode(\"hello\") = " << getHashCode(s1) << "  (532 % 5 = 2)\n";
    cout << "  getHashCode(\"abc\")   = " << getHashCode(s2) << "  (294 % 3 = 0)\n";
    cout << "  getHashCode(\"haady\") = " << getHashCode(s3) << "\n";

    // --- insert / retrieve (int array) ---
    cout << "\n-- insert / retrieve  [int array, size=10] --\n";
    const int SZ = 10;
    int intTable[SZ] = {0};
    insert(intTable, SZ, 0, 25);
    insert(intTable, SZ, 0, 36);
    insert(intTable, SZ, 0, 15);
    insert(intTable, SZ, 0, 45);

    cout << "  Table  : [ ";
    for (int i = 0; i < SZ; i++) cout << intTable[i] << " ";
    cout << "]\n";
    cout << "  retrieve(offset=5) = " << retrieve(intTable, SZ, 5) << "\n";

    // --- insert / retrieve (string array) ---
    cout << "\n-- insert / retrieve  [string array, size=11] --\n";
    const int SSZ = 11;
    string strTable[SSZ];
    insert(strTable, SSZ, 0, "apple");
    insert(strTable, SSZ, 0, "banana");
    insert(strTable, SSZ, 0, "cherry");
    insert(strTable, SSZ, 0, "date");

    cout << "  Table  : [ ";
    for (int i = 0; i < SSZ; i++)
        cout << (strTable[i].empty() ? "_" : strTable[i]) << " ";
    cout << "]\n";
    cout << "  retrieve(offset=0) = \"" << retrieve(strTable, SSZ, 0) << "\"\n";
    cout << "  retrieve(offset=3) = \"" << retrieve(strTable, SSZ, 3) << "\"\n";

    return 0;
}

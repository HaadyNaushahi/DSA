/*
 * File    : HashFunctions.h
 * Task    : Task 4 — Hashing Utility Functions
 * Desc    : Provides index computation (modulo, linear, quadratic, double-hash),
 *           a string hash code function, and insert/retrieve operations for
 *           both integer arrays and string arrays using those hash functions.
 *           getHashCode uses recursion to accumulate the ASCII sum.
 *           insert (int) uses recursion to probe for an empty slot.
 * Section : D20 | Spring 2026
 */

#ifndef HASHFUNCTIONS_H
#define HASHFUNCTIONS_H

#include <iostream>
#include <string>
using namespace std;

// ======================== INDEX FUNCTIONS ========================

// Returns the base hash index: value % size
int getIndex(int value, int size) {
    return value % size;
}

// Linear probing index: (base + offset) % size
int getLinearKey(int value, int size, int offset) {
    return (getIndex(value, size) + offset) % size;
}

// Quadratic probing index: (base + offset²) % size
int getQuardKey(int value, int size, int offset) {
    return (getIndex(value, size) + offset * offset) % size;
}

// Double-hash style index: (base + offset * quadKey(OFFSET=1)) % size
int getCode(int value, int size, int offset) {
    return (getIndex(value, size) + offset * getQuardKey(value, size, 1)) % size;
}

// ======================== STRING HASH ========================

// Recursive ASCII accumulator helper
// Base case    : index == len → return 0 (no more characters to add)
// Recursive case: add ASCII of str[index] to the recursive sum of the rest
static int asciiSum(const char* str, int index, int len) {
    if (index == len) return 0;
    return (int)str[index] + asciiSum(str, index + 1, len);
}

// Returns sum(ASCII of each character) % length(str)
int getHashCode(char* str) {
    int len = 0;
    while (str[len] != '\0') len++;
    if (len == 0) return 0;
    return asciiSum(str, 0, len) % len;
}

// ======================== INT ARRAY: INSERT / RETRIEVE ========================

// Recursive quadratic-probe insert for int arrays
// 0 is used as the empty-slot sentinel
// Base case    : probe == size → table is full, cannot insert
// Recursive case: if slot at getQuardKey(value, size, offset+probe) is empty → store;
//                 otherwise increment probe and recurse
static void insertHelper(int* a, int size, int value, int baseOffset, int probe) {
    if (probe == size) {
        cout << "  [!] Table full — could not insert " << value << "\n";
        return;
    }
    int idx = getQuardKey(value, size, baseOffset + probe);
    if (a[idx] == 0) {
        a[idx] = value;
        cout << "  Inserted " << value << " at index " << idx << "\n";
        return;
    }
    insertHelper(a, size, value, baseOffset, probe + 1);
}

// Inserts value into int array a using quadratic probing starting at offset
void insert(int* a, int size, int offset, int value) {
    insertHelper(a, size, value, offset, 0);
}

// Returns the value at getQuardKey(0, size, offset) in array a
int retrieve(int* a, int size, int offset) {
    return a[getQuardKey(0, size, offset)];
}

// ======================== STRING ARRAY: INSERT / RETRIEVE ========================

// Recursive linear-probe insert for string arrays (using getHashCode as base)
// Base case    : probe == size → table is full, cannot insert
// Recursive case: if slot at (hash + offset + probe) % size is empty → store;
//                 otherwise increment probe and recurse
static void insertStrHelper(string* a, int size, int base, int offset, int probe, const string& str) {
    if (probe == size) {
        cout << "  [!] Table full — could not insert \"" << str << "\"\n";
        return;
    }
    int idx = (base + offset + probe) % size;
    if (a[idx].empty()) {
        a[idx] = str;
        cout << "  Inserted \"" << str << "\" at index " << idx << "\n";
        return;
    }
    insertStrHelper(a, size, base, offset, probe + 1, str);
}

// Inserts str into string array a; uses getHashCode for the base index
void insert(string* a, int size, int offset, string str) {
    char buf[512];
    int i = 0;
    while (i < 511 && str[i] != '\0') { buf[i] = str[i]; i++; }
    buf[i] = '\0';
    int base = getHashCode(buf);
    insertStrHelper(a, size, base, offset, 0, str);
}

// Returns the string at index (0 + offset) % size in array a
string retrieve(string* a, int size, int offset) {
    return a[offset % size];
}

#endif

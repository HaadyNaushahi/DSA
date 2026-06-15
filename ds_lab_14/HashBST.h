/*
 * File    : HashBST.h
 * Task    : Task 5 — Hash Table of BSTs
 * Desc    : A fixed-size array of Node* (BST root pointers).
 *           getHashCode maps a string to a bucket index.
 *           add, search, and remove match the exact signatures from the task spec:
 *             void   add   (Node** a, int size, string str)
 *             bool   search(Node** a, int size, string str)
 *             string remove(Node** a, int size, string str)
 *           getHashCode uses recursive ASCII accumulation (same as Task 4).
 *           All BST operations delegate to the recursive functions in BST.h.
 * Section : D20 | Spring 2026
 */

#ifndef HASHBST_H
#define HASHBST_H

#include <iostream>
#include <string>
#include "BST.h"
using namespace std;

// ======================== HASH FUNCTION ========================

// Recursive ASCII sum helper
// Base case    : index == len → return 0
// Recursive case: ASCII of str[index] + recursive sum of the rest
static int asciiSum(const char* str, int index, int len) {
    if (index == len) return 0;
    return (int)str[index] + asciiSum(str, index + 1, len);
}

// Returns sum(ASCII of each char) % length(str)
static int getHashCode(const string& str) {
    int len = (int)str.size();
    if (len == 0) return 0;
    char buf[512];
    for (int i = 0; i < len && i < 511; i++) buf[i] = str[i];
    buf[len < 511 ? len : 511] = '\0';
    return asciiSum(buf, 0, len) % len;
}

// Maps hash to a valid bucket: getHashCode(str) % size
static int bucketIndex(const string& str, int size) {
    return getHashCode(str) % size;
}

// ======================== BST NODE OPERATIONS ========================
// These operate directly on Node* to match the task's Node** array spec.
// They reuse the recursive helpers from BST.h by wrapping via BST::setRoot / getRoot.

// Recursive insert directly on a Node* subtree (mirrors BST::insert internals)
// Base case    : node is null → create and return new leaf
// Recursive case: go left or right; return updated node
static Node* nodeInsert(Node* node, const string& str) {
    if (!node) return new Node(str);
    if      (str < node->data) node->left  = nodeInsert(node->left,  str);
    else if (str > node->data) node->right = nodeInsert(node->right, str);
    return node;
}

// Recursive search directly on a Node* subtree
// Base case    : node is null (false) OR node->data == str (true)
// Recursive case: go left or right based on comparison
static bool nodeSearch(Node* node, const string& str) {
    if (!node)             return false;
    if (node->data == str) return true;
    if (str < node->data)  return nodeSearch(node->left,  str);
    return nodeSearch(node->right, str);
}

// Leftmost node in subtree (in-order successor helper)
// Base case    : node->left is null → this is the minimum
// Recursive case: keep going left
static Node* nodeMin(Node* node) {
    return node->left ? nodeMin(node->left) : node;
}

// Recursive remove directly on a Node* subtree; fills removed with deleted value
// Base case    : node is null → not found
// Recursive case: navigate to target; handle 0/1/2 children on the way back up
static Node* nodeRemove(Node* node, const string& str, string& removed) {
    if (!node) { removed = ""; return nullptr; }

    if (str < node->data) {
        node->left  = nodeRemove(node->left,  str, removed);
    } else if (str > node->data) {
        node->right = nodeRemove(node->right, str, removed);
    } else {
        removed = node->data;
        if (!node->left && !node->right) { delete node; return nullptr; }
        if (!node->left)  { Node* r = node->right; delete node; return r; }
        if (!node->right) { Node* l = node->left;  delete node; return l; }

        Node* succ = nodeMin(node->right);
        node->data = succ->data;
        string dummy;
        node->right = nodeRemove(node->right, succ->data, dummy);
    }
    return node;
}

// ======================== TASK 5 REQUIRED FUNCTIONS ========================

// Hashes str to get bucket index; inserts str into the BST rooted at a[idx]
void add(Node** a, int size, string str) {
    int idx  = bucketIndex(str, size);
    a[idx]   = nodeInsert(a[idx], str);
    cout << "  add(\"" << str << "\") -> bucket[" << idx << "]\n";
}

// Hashes str to get bucket index; searches the BST at a[idx]
bool search(Node** a, int size, string str) {
    int idx = bucketIndex(str, size);
    return nodeSearch(a[idx], str);
}

// Hashes str to get bucket index; removes str from the BST at a[idx]
// Returns the removed string, or "" if not found
string remove(Node** a, int size, string str) {
    int idx = bucketIndex(str, size);
    string removed;
    a[idx] = nodeRemove(a[idx], str, removed);
    return removed;
}

// ======================== DISPLAY HELPER ========================

// Recursive in-order print of a BST rooted at node
// Base case    : node is null → nothing to print
// Recursive case: print left, print current, print right
static void printBST(Node* node) {
    if (!node) return;
    printBST(node->left);
    cout << node->data << " ";
    printBST(node->right);
}

void displayTable(Node** a, int size) {
    cout << "\n  ---- Hash Table of BSTs ----\n";
    for (int i = 0; i < size; i++) {
        cout << "  Bucket[" << i << "]: ";
        if (!a[i]) cout << "(empty)";
        else       printBST(a[i]);
        cout << "\n";
    }
    cout << "  ----------------------------\n";
}

#endif

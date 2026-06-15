/*
 * File    : BST.h
 * Task    : Task 5 — Hash Table of BSTs
 * Desc    : Binary Search Tree of strings.
 *           insert, search, and remove are all fully recursive.
 *           The Node struct is exposed publicly so the hash table
 *           in HashBST.h can store raw Node* root pointers.
 * Section : D20 | Spring 2026
 */

#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
using namespace std;

// ======================== NODE ========================

struct Node {
    string data;
    Node*  left;
    Node*  right;

    Node(const string& s) : data(s), left(nullptr), right(nullptr) {}
};

// ======================== CLASS ========================

class BST {
    Node* root;

    // Recursively inserts str into the subtree rooted at node
    Node* insert(Node* node, const string& str);

    // Recursively searches for str in the subtree rooted at node
    bool search(Node* node, const string& str) const;

    // Returns the leftmost node in a subtree (in-order successor helper)
    Node* minNode(Node* node) const;

    // Recursively removes str from the subtree; returns new subtree root
    Node* remove(Node* node, const string& str, string& removed);

    // Recursively frees all nodes in the subtree
    void destroy(Node* node);

    // Recursive in-order print for display
    void inorder(Node* node) const;

public:
    BST();
    ~BST();

    // Inserts str into the BST
    void insert(const string& str);

    // Returns true if str exists in the BST
    bool search(const string& str) const;

    // Removes str from BST; returns the removed value or "" if not found
    string remove(const string& str);

    // Returns the raw root pointer (needed by HashBST to store in its array)
    Node* getRoot() const;

    // Sets the root (needed by HashBST to restore after external mutation)
    void setRoot(Node* node);

    // Prints BST contents in sorted order
    void print() const;
};

// ======================== IMPLEMENTATION ========================

BST::BST() : root(nullptr) {}

BST::~BST() { destroy(root); }

// Base case    : node is null → insert here, return new leaf
// Recursive case: go left if str < node, right if str > node; return updated node
Node* BST::insert(Node* node, const string& str) {
    if (!node) return new Node(str);
    if      (str < node->data) node->left  = insert(node->left,  str);
    else if (str > node->data) node->right = insert(node->right, str);
    // duplicate: do nothing
    return node;
}

// Base case    : node is null → not found (false); node->data == str → found (true)
// Recursive case: go left or right based on comparison
bool BST::search(Node* node, const string& str) const {
    if (!node)              return false;
    if (node->data == str)  return true;
    if (str < node->data)   return search(node->left,  str);
    return search(node->right, str);
}

// Base case    : node->left is null → this is the minimum
// Recursive case: keep going left
Node* BST::minNode(Node* node) const {
    return node->left ? minNode(node->left) : node;
}

// Base case    : node is null → str not found, removed = ""
// Recursive case: go left/right to find str; on match handle 0/1/2 children
Node* BST::remove(Node* node, const string& str, string& removed) {
    if (!node) { removed = ""; return nullptr; }

    if (str < node->data) {
        node->left  = remove(node->left,  str, removed);
    } else if (str > node->data) {
        node->right = remove(node->right, str, removed);
    } else {
        removed = node->data;
        if (!node->left && !node->right) { delete node; return nullptr; }
        if (!node->left)  { Node* r = node->right; delete node; return r; }
        if (!node->right) { Node* l = node->left;  delete node; return l; }

        // Two children: replace with in-order successor, then delete successor
        Node* succ  = minNode(node->right);
        node->data  = succ->data;
        string dummy;
        node->right = remove(node->right, succ->data, dummy);
    }
    return node;
}

// Base case    : node is null → nothing to free
// Recursive case: destroy left, destroy right, delete current
void BST::destroy(Node* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

// Base case    : node is null → nothing to print
// Recursive case: print left subtree, print current, print right subtree
void BST::inorder(Node* node) const {
    if (!node) return;
    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
}

void BST::insert(const string& str) {
    root = insert(root, str);
}

bool BST::search(const string& str) const {
    return search(root, str);
}

string BST::remove(const string& str) {
    string removed;
    root = remove(root, str, removed);
    return removed;
}

Node* BST::getRoot() const { return root; }

void BST::setRoot(Node* node) { root = node; }

void BST::print() const {
    if (!root) { cout << "(empty)"; return; }
    inorder(root);
}

#endif

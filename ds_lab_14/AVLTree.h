/*
 * File    : AVLTree.h
 * Task    : Task 3 — User ID-Password System
 * Desc    : AVL Tree storing ID-Password pairs as string[2] nodes,
 *           keyed and balanced on the ID (pair[0]).
 *           All insert, remove, and search operations are fully recursive.
 *           Rotations restore AVL balance after every mutation.
 * Section : D20 | Spring 2026
 */

#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <string>
using namespace std;

// ======================== NODE ========================

struct AVLNode {
    string pair[2];   // pair[0] = ID,  pair[1] = Password
    int     height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(const string& id, const string& pw)
        : height(1), left(nullptr), right(nullptr) {
        pair[0] = id;
        pair[1] = pw;
    }
};

// ======================== CLASS ========================

class AVLTree {
    AVLNode* root;

    // Returns height of a node (0 for null)
    int height(AVLNode* n);

    // Returns balance factor: height(left) - height(right)
    int bf(AVLNode* n);

    // Updates the stored height of a node from its children
    void updateHeight(AVLNode* n);

    // Single right rotation around y
    AVLNode* rotateRight(AVLNode* y);

    // Single left rotation around x
    AVLNode* rotateLeft(AVLNode* x);

    // Applies the correct rotation(s) and returns the new subtree root
    AVLNode* balance(AVLNode* n);

    // Recursively inserts id/pw; updates/balances on the way back up
    AVLNode* insert(AVLNode* node, const string& id, const string& pw);

    // Returns pointer to the leftmost (minimum) node in a subtree
    AVLNode* minNode(AVLNode* n);

    // Recursively removes the node with the given id; balances on the way back up
    AVLNode* remove(AVLNode* node, const string& id);

    // Recursively searches for a node by id
    AVLNode* search(AVLNode* node, const string& id) const;

    // In-order traversal — fills ids[] and pws[] in sorted order
    void inorder(AVLNode* node, string* ids, string* pws, int& idx) const;

    // Recursively frees all nodes
    void destroy(AVLNode* node);

public:
    AVLTree();
    ~AVLTree();

    // Inserts an ID-Password pair (updates password if ID already exists)
    void insert(const string& id, const string& pw);

    // Removes the node for the given ID; returns false if not found
    bool remove(const string& id);

    // Returns the password for a given ID, or "" if not found
    string searchPassword(const string& id) const;

    // Fills ids[] and pws[] with all pairs in sorted ID order; sets count
    void getAllSorted(string* ids, string* pws, int& count) const;
};

// ======================== IMPLEMENTATION ========================

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() { destroy(root); }

int AVLTree::height(AVLNode* n) {
    return n ? n->height : 0;
}

int AVLTree::bf(AVLNode* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

void AVLTree::updateHeight(AVLNode* n) {
    if (n) n->height = 1 + max(height(n->left), height(n->right));
}

AVLNode* AVLTree::rotateRight(AVLNode* y) {
    AVLNode* x  = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left  = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

AVLNode* AVLTree::rotateLeft(AVLNode* x) {
    AVLNode* y  = x->right;
    AVLNode* T2 = y->left;
    y->left  = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

AVLNode* AVLTree::balance(AVLNode* n) {
    updateHeight(n);
    int b = bf(n);

    if (b > 1  && bf(n->left)  >= 0) return rotateRight(n);          // LL
    if (b > 1  && bf(n->left)  <  0) {                                // LR
        n->left = rotateLeft(n->left);
        return rotateRight(n);
    }
    if (b < -1 && bf(n->right) <= 0) return rotateLeft(n);           // RR
    if (b < -1 && bf(n->right) >  0) {                                // RL
        n->right = rotateRight(n->right);
        return rotateLeft(n);
    }
    return n;
}

// Base case    : node is null → create and return a new leaf
// Recursive case: go left or right based on ID comparison; balance on the way back up
AVLNode* AVLTree::insert(AVLNode* node, const string& id, const string& pw) {
    if (!node) return new AVLNode(id, pw);

    if      (id < node->pair[0]) node->left  = insert(node->left,  id, pw);
    else if (id > node->pair[0]) node->right = insert(node->right, id, pw);
    else                          node->pair[1] = pw;   // update password on duplicate

    return balance(node);
}

// Base case    : node is null → minimum is the node itself
// Recursive case: keep going left
AVLNode* AVLTree::minNode(AVLNode* n) {
    return n->left ? minNode(n->left) : n;
}

// Base case    : node is null → ID not found, return nullptr
// Recursive case: go left/right; on match handle 0/1/2 children; balance on way back up
AVLNode* AVLTree::remove(AVLNode* node, const string& id) {
    if (!node) return nullptr;

    if      (id < node->pair[0]) node->left  = remove(node->left,  id);
    else if (id > node->pair[0]) node->right = remove(node->right, id);
    else {
        if (!node->left || !node->right) {
            AVLNode* child = node->left ? node->left : node->right;
            delete node;
            return child;
        }
        // Two children: replace with in-order successor then delete successor
        AVLNode* succ  = minNode(node->right);
        node->pair[0]  = succ->pair[0];
        node->pair[1]  = succ->pair[1];
        node->right    = remove(node->right, succ->pair[0]);
    }
    return balance(node);
}

// Base case    : node is null (not found) OR node->pair[0] == id (found)
// Recursive case: go left or right based on comparison
AVLNode* AVLTree::search(AVLNode* node, const string& id) const {
    if (!node || node->pair[0] == id) return node;
    if (id < node->pair[0])           return search(node->left,  id);
    return search(node->right, id);
}

// Base case    : node is null → nothing to visit
// Recursive case: visit left subtree, record current node, visit right subtree
void AVLTree::inorder(AVLNode* node, string* ids, string* pws, int& idx) const {
    if (!node) return;
    inorder(node->left, ids, pws, idx);
    ids[idx] = node->pair[0];
    pws[idx] = node->pair[1];
    idx++;
    inorder(node->right, ids, pws, idx);
}

// Base case    : node is null → nothing to free
// Recursive case: free left subtree, free right subtree, delete current node
void AVLTree::destroy(AVLNode* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

void AVLTree::insert(const string& id, const string& pw) {
    root = insert(root, id, pw);
}

bool AVLTree::remove(const string& id) {
    if (!search(root, id)) return false;
    root = remove(root, id);
    return true;
}

string AVLTree::searchPassword(const string& id) const {
    AVLNode* n = search(root, id);
    return n ? n->pair[1] : "";
}

void AVLTree::getAllSorted(string* ids, string* pws, int& count) const {
    count = 0;
    inorder(root, ids, pws, count);
}

#endif

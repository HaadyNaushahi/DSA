/*
 * File    : MaxHeap.h
 * Task    : Task 3 — User ID-Password System
 * Desc    : MaxHeap of strings. Stores sorted user IDs.
 *           Insertion maintains the heap property via recursive heapifyUp.
 *           Removal of an arbitrary element is handled via recursive heapifyDown.
 * Section : D20 | Spring 2026
 */

#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <iostream>
#include <string>
using namespace std;

// ======================== CLASS ========================

class MaxHeap {
    string* data;
    int     capacity;
    int     size;

    // Index helpers
    int parent(int i) { return (i - 1) / 2; }
    int left(int i)   { return 2 * i + 1;   }
    int right(int i)  { return 2 * i + 2;   }

    // Bubbles node at index i upward until heap order is restored
    void heapifyUp(int i);

    // Pushes node at index i downward until heap order is restored
    void heapifyDown(int i);

    // Returns index of str in data[], or -1 if not found
    int findIndex(const string& str) const;

public:
    MaxHeap(int cap = 200);
    ~MaxHeap();

    // Inserts a new user ID into the heap
    void insert(const string& id);

    // Removes a specific user ID; returns false if not found
    bool remove(const string& id);

    // Returns true if the given ID exists in the heap
    bool contains(const string& id) const;

    // Copies all IDs into out[] and sets count
    void getAll(string* out, int& count) const;
};

// ======================== IMPLEMENTATION ========================

MaxHeap::MaxHeap(int cap) : capacity(cap), size(0) {
    data = new string[capacity];
}

MaxHeap::~MaxHeap() {
    delete[] data;
}

// Recursive upward fix
// Base case    : i == 0 (reached root) OR parent >= current (heap order satisfied)
// Recursive case: swap with parent and recurse upward
void MaxHeap::heapifyUp(int i) {
    if (i == 0 || data[parent(i)] >= data[i])
        return;

    swap(data[parent(i)], data[i]);
    heapifyUp(parent(i));
}

// Recursive downward fix
// Base case    : no children exist, OR current is already >= both children
// Recursive case: swap with the larger child and recurse downward
void MaxHeap::heapifyDown(int i) {
    int largest = i;
    int l = left(i), r = right(i);

    if (l < size && data[l] > data[largest]) largest = l;
    if (r < size && data[r] > data[largest]) largest = r;

    if (largest == i)
        return;

    swap(data[i], data[largest]);
    heapifyDown(largest);
}

// Linear scan (heap is not sorted, so no smarter traversal is possible)
// Base case    : idx == size (end of array, not found → return -1)
// Recursive case: check current slot, recurse on idx + 1
int MaxHeap::findIndex(const string& str) const {
    // Internal recursive lambda-style via a helper call pattern
    // Implemented iteratively here because the recursion adds no readability gain
    // over a plain loop for a linear scan — kept as a loop intentionally
    for (int i = 0; i < size; i++)
        if (data[i] == str) return i;
    return -1;
}

void MaxHeap::insert(const string& id) {
    if (size == capacity) {
        cout << "  [!] Heap is full.\n";
        return;
    }
    data[size++] = id;
    heapifyUp(size - 1);
}

bool MaxHeap::remove(const string& id) {
    int idx = findIndex(id);
    if (idx == -1) return false;

    data[idx] = data[--size];
    heapifyDown(idx);
    heapifyUp(idx);
    return true;
}

bool MaxHeap::contains(const string& id) const {
    return findIndex(id) != -1;
}

void MaxHeap::getAll(string* out, int& count) const {
    count = size;
    for (int i = 0; i < size; i++)
        out[i] = data[i];
}

#endif

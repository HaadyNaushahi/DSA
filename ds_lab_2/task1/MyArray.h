#pragma once
#include <iostream>
#include "AbstractArray.h"

using namespace std;

class MyArray : public AbstractArray
{
public:
    MyArray(int capacity = 0) : AbstractArray(capacity) {}
    MyArray(const MyArray &ma) : AbstractArray(ma) {}

    void add(int v);
    bool remove(int &v);
    bool get(int index, int &v);
    void insert(int index, int value);
};

void MyArray::add(int v)
{
    if (!isFull())
    {
        values[++currentIndex] = v;
    }
    else
    {
        cout << "Array is full\n";
    }
}

bool MyArray::remove(int &v)
{
    if (isEmpty())
    {
        cout << "Array is empty\n";
        return false;
    }

    v = values[currentIndex--];
    return true;
}

bool MyArray::get(int index, int &v)
{
    if (index < 0 || index > currentIndex)
    {
        cout << "Invalid index\n";
        return false;
    }

    v = values[index];
    return true;
}

void MyArray::insert(int index, int value)
{
    if (index < 0 || index > currentIndex)
    {
        cout << "Invalid index\n";
        return;
    }

    values[index] = value;
}

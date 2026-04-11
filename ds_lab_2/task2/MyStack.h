
#pragma once
#include <iostream>
#include "Stack.h"

using namespace std;

class MyStack : public Stack
{
public:
    MyStack(int capacity = 0) : Stack(capacity) {}
    MyStack(const Stack &ma) : Stack(ma) {}

    void push(int v);
    bool pop(int &v);
};

void MyStack::push(int v)
{
    if (!isFull())
    {
        values[++currentIndex] = v;
    }
    else
    {
        cout << "Stack is full\n";
    }
}

bool MyStack::pop(int &v)
{
    if (!isEmpty())
    {
        v = values[currentIndex--];
        return true;
    }

    return false;
}

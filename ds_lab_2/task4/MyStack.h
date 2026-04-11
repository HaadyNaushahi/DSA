
#pragma once
#include <iostream>
#include <string>
#include "Stack.h"
using namespace std;

template <typename T>

class MyStack : public Stack
{
public:
    MyStack(int capacity = 0) : Stack(capacity) {}
    MyStack(const Stack &ma) : Stack(ma) {}

    void push(string v);
    bool pop(string &v);
};

void MyStack::push(string v)
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

bool MyStack::pop(string &v)
{
    if (!isEmpty())
    {
        v = values[currentIndex--];
        return true;
    }

    return false;
}

#pragma once
#include <string>
using namespace std;

template<typename T>

class Stack
{
protected:
    int currentIndex;
    int maxCapacity;
    T *values;
public:
    Stack(int _maxCapacity = 0);
    Stack(const Stack &AA);
    virtual ~Stack();

    virtual void push(T v) = 0; 
    // increments currentIndex and adds value if not full

    virtual bool pop(T &value) = 0; 
    // if not empty returns the value at currentIndex and decrements currentIndex

    bool isEmpty();
    bool isFull();
    string top();
};

Stack::Stack(int _maxCapacity)
{
    currentIndex = -1;
    maxCapacity = _maxCapacity > 0 ? _maxCapacity : 1;
    values = new T[maxCapacity];
}

Stack::Stack(const Stack &AA)
{
    maxCapacity = AA.maxCapacity;
    currentIndex = AA.currentIndex;

    values = new string[maxCapacity];

    for (int i = 0; i <= currentIndex; i++)
    {
        values[i] = AA.values[i];
    }
}

Stack::~Stack()
{
    delete[] values;
}

bool Stack::isEmpty()
{
    return (currentIndex < 0);
}

bool Stack::isFull()
{
    return (currentIndex == maxCapacity - 1);
}
string Stack::top() 
{
    if (currentIndex > 0) {
	return values[currentIndex];
    }
    return "";
}

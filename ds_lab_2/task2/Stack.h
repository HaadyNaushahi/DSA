#pragma once

class Stack
{
protected:
    int currentIndex;
    int *values;
    int maxCapacity;
public:
    Stack(int _maxCapacity = 0);
    Stack(const Stack &AA);
    virtual ~Stack();

    virtual void push(int v) = 0; 
    // increments currentIndex and adds value if not full

    virtual bool pop(int &value) = 0; 
    // if not empty returns the value at currentIndex and decrements currentIndex

    bool isEmpty();
    bool isFull();
};

Stack::Stack(int _maxCapacity)
{
    currentIndex = -1;
    maxCapacity = _maxCapacity;
    values = new int[maxCapacity]{0};
}

Stack::Stack(const Stack &AA)
{
    maxCapacity = AA.maxCapacity;
    currentIndex = AA.currentIndex;

    values = new int[maxCapacity];

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

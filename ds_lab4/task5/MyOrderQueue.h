#pragma once
#include "OrderQueue.h"
#include <iostream>
using namespace std;

class MyQueue : public Queue {
public:
  MyQueue(int s) : Queue(s) {
    if (s != 0) {
      values = new Order[maxCapacity];
    }
  }
  MyQueue(const Queue &mq) : Queue(mq) {
    if (maxCapacity != 0 || values == nullptr) {
      values = new Order[maxCapacity];
      for (int i = 0; i < count; i++) {
        values[i] = mq.values[i];
      }
    }
  }

  ~MyQueue() {
    if (values != nullptr) {
      delete[] values;
      values = nullptr;
    }
  }
 void enqueue(const Order & value);
 Order dequeue();
 void display(ostream &) const;
    
};

void MyQueue::enqueue(const Order & value)
{
    if (isFull())
    {
        throw "cannot add to filled queue";
    }
    if (startOfQIndex == -1)
    {
        startOfQIndex = 0;
        topOfQIndex = 0;
    }
    else
    {
        topOfQIndex = (topOfQIndex + 1) % maxCapacity; // wraps around
    }
    values[topOfQIndex] = value;
    count++;
}

Order MyQueue::dequeue()
{
    if (isEmpty())
    {
        throw "cannot remove from empty queue";
    }
    Order removed = values[startOfQIndex];
    startOfQIndex = (startOfQIndex + 1) % maxCapacity; // wraps around
    count--;
    if (count == 0)
    {
        startOfQIndex = -1;
        topOfQIndex = -1;
    }
    return removed;
}

void MyQueue::display(ostream &out)const{
    if(isEmpty()){
        out << "Empty nothing to prinr \n";
    }
    for (int i = startOfQIndex ; i <= topOfQIndex; i++){
        out << values[i] << " ";
    }
    out << endl;
}

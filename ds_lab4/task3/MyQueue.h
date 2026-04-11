#pragma once
#include "Queue.h"
#include <iostream>
using namespace std;

class MyQueue : public Queue {
public:
  MyQueue(int s) : Queue(s) {
    if (s != 0) {
      values = new int[maxCapacity]{0};
    }
  }
  MyQueue(const Queue &mq) : Queue(mq) {
    if (maxCapacity != 0 || values == nullptr) {
      values = new int[maxCapacity]{0};
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
 void enqueue(const int & value);
 int dequeue();
 void display(ostream &) const;
    
};


void MyQueue::enqueue(const int &value){
    if(isFull()){
        throw "cannot add to filled queue";
    }

    if(startOfQIndex == -1){
        startOfQIndex = 0;
        topOfQIndex = 0;
    } else {
        topOfQIndex++;
    }

    values[topOfQIndex] = value;
    count++;
}

int MyQueue::dequeue(){
    if(isEmpty()){
        throw "cannot remove from empty queue";
    }

    int removed = values[startOfQIndex];
    startOfQIndex++;
    count--;

    if (count == 0){
        topOfQIndex = -1;
        startOfQIndex = -1;
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

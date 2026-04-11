#include <algorithm>
#include <iostream>
#include "MyQueue.h"
#include "MyStack.h"
#include "Queue.h"
#include "Stack.h"
using namespace std;

int MAX_SIZE = 10;

void display(Queue *q, ostream &out) {
    Queue *copyQ = new MyQueue(*q);
    Order val;
    while (!copyQ->isEmpty()) {
        val = copyQ->dequeue();
        out << val << endl;
    }
    out << endl;
    delete copyQ;

}  // Display the values in the Queue


int main() {
    Queue *q = new MyQueue(MAX_SIZE);

    Order Burger("Burger", 200, 20);
    Order Sandwich("Sandwich", 250, 30);
    Order FrenchFries("French Fries", 100, 10);
    Order FriedChickens("Fried Chickens", 400, 40);
    Order Pizza("Pizza", 350, 40);

    q->enqueue(Burger);
    q->enqueue(Sandwich);
    q->enqueue(FrenchFries);
    q->enqueue(FriedChickens);
    q->enqueue(Pizza);
    cout << "Order: " << endl;
    display(q, cout);


    return 0;
}

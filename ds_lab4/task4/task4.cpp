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
    int val;
    while (!copyQ->isEmpty()) {
        val = copyQ->dequeue();
        out << val << " ";
    }
    out << endl;
    delete copyQ;

}  // Display the values in the Queue

/*
 * make a copy of the original queue to preserve it and extract the values of the copied queue by dequeuing and store it in a stack till the kth index
 * by popping the values in the stack, the values will be given in reverse order
 * enqueue these values in the destination queue
 * enqueue the remaining values of the copied queue (if any remaining) back into the original (modified) queue in the original order
*/
void reverseFirstKElements(Queue *q, int k) {
    Queue *copyQ = new MyQueue(*q);
    
    int val;
    while (!q->isEmpty()) { val = q->dequeue(); }
    
    int counter = 0;
    Stack *reverseOrderElements = new MyStack(MAX_SIZE);

    while (!copyQ->isEmpty() && counter < k) {
	val = copyQ->dequeue();
	reverseOrderElements->push(val);
	counter += 1;
    }
    
    while (!reverseOrderElements->isEmpty() && !q->isFull()) {
	reverseOrderElements->pop(val);
	q->enqueue(val);
    }

    while (!copyQ->isEmpty() && !q->isFull()) {
	val = copyQ->dequeue();
	q->enqueue(val);
    }

    delete copyQ;
}

int main() {
    Queue *q = new MyQueue(MAX_SIZE);
    q->enqueue(10);
    q->enqueue(9);
    q->enqueue(2);
    q->enqueue(5);
    q->enqueue(-7);
    cout << " Queue A Values: ";
    display(q, cout);

    reverseFirstKElements(q, 3);

    display(q, cout);

    return 0;
}

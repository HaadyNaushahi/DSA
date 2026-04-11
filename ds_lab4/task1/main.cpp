#include "MyQueue.h"
#include "MyStack.h"
#include "Queue.h"
#include "Stack.h"
#include <iostream>
using namespace std;

const int MAX_SIZE = 5;

/*
 * implement a while loop with the condition "until the queue is full" and take input from user and enqueue
*/
void read(Queue *Q, istream &in) {
    int value = 0;
    while (!Q->isFull()) {
        cout << "Enter value: ";
        in >> value;
        Q->enqueue(value);
    }
}

/*
 * make a copy of the queue to preserve it and extract the values by dequeueing and print them
*/
void display(Queue *Q, ostream &out) {
    Queue *copyQ = new MyQueue(*Q);
    int val;
    while (!copyQ->isEmpty()) {
        val = copyQ->dequeue();
        out << val << " ";
    }
    out << endl;
    delete copyQ;
}

/*
 * make a copy of the original queue to preserve it and extract the values of the copied queue by dequeuing and enqueue to the destination queue
 * it is important that the destination queue has enough space for the values to be added and the loop should also check if the copied queue is not empty so an infinite loop doesn't occur
*/
void append(Queue *src, Queue *dst) {
    Queue *copySrc = new MyQueue(*src);
    int val;
    while (!copySrc->isEmpty() && !dst->isFull()) {
        val = copySrc->dequeue();
        dst->enqueue(val);
    }
    delete copySrc;
}

int queueSize(Queue *q) {
    Queue *copyQ = new MyQueue(*q);
    int count = 0;
    while (!copyQ->isEmpty()) {
        copyQ->dequeue();
        count++;
    }
    delete copyQ;
    return count;
}

/*
 * make a copy of the original queue to preserve it and extract the values of the copied queue by dequeuing and enqueue to the destination queue
 * it is important that the destination queue has enough space for the values to be added and the loop should also check if the copied queue is not empty so an infinite loop doesn't occur
 * in this case, we also need a counter for the number of values to be enqueued in the destination queue
*/
void append(Queue *src, Queue *dst, int no) {
    Queue *copySrc = new MyQueue(*src);
    int counter = 0;
    int val;
    while (!copySrc->isEmpty() && !dst->isFull() && counter < no) {
        val = copySrc->dequeue();
        dst->enqueue(val);
        counter++;
    }
    delete copySrc;
}

/*
 * make a copy of the original queue to preserve it and extract the values of the copied queue by dequeuing and store it in a stack 
 * by popping the values in the stack, the values will be given in reverse order
 * enqueue these values in the destinatio queue
*/
void reverseAppend(Queue *src, Queue *dst) {
    Stack *reverseSrcCopy = new MyStack(MAX_SIZE);
    Queue *copySrc = new MyQueue(*src);
    int val;
    while (!copySrc->isEmpty()) {
        val = copySrc->dequeue();
        reverseSrcCopy->push(val);
    }
    while (!reverseSrcCopy->isEmpty() && !dst->isFull()) {
        reverseSrcCopy->pop(val);
        dst->enqueue(val);
    }
    delete reverseSrcCopy;
    delete copySrc;
}

/*
 * make a copy of the original queue to preserve it and extract the values of the copied queue by dequeuing
 * as the values are being extracted, add these values to the sum 
 * get the average by diviing the sum by the number of values in the queue
*/
void stats(Queue *q, int &sum, float &average) {
    Queue *copyQ = new MyQueue(*q);
    sum = 0;
    int count = 0;
    int val;
    while (!copyQ->isEmpty()) {
        val = copyQ->dequeue();
        sum += val;
        count++;
    }
    average = (count == 0) ? 0 : (float)sum / count;
    delete copyQ;
}

/*
 * make two copies for each of the queues and also get the size of each queueSize
 * check if the sizes are equal, if not, return false
 * if sizes are equal then extract values one by one consecutively and check for equality
*/
bool isEqual(Queue *q1, Queue *q2) {
    Queue *copyQ1 = new MyQueue(*q1);
    Queue *copyQ2 = new MyQueue(*q2);

    while (!copyQ1->isEmpty() && !copyQ2->isEmpty()) {
        int val1 = copyQ1->dequeue();
        int val2 = copyQ2->dequeue();
        if (val1 != val2) {
            delete copyQ1;
            delete copyQ2;
            return false;
        }
    }

    bool equal = copyQ1->isEmpty() && copyQ2->isEmpty();

    delete copyQ1;
    delete copyQ2;
    return equal;
}

int main() {
    Queue *A = new MyQueue(MAX_SIZE);
    read(A, cin);
    cout << " Queue A Values: ";
    display(A, cout);

    Queue *B = new MyQueue(MAX_SIZE);
    append(A, B);
    cout << " Queue B Values: ";
    display(B, cout);

    Queue *C = new MyQueue(MAX_SIZE);
    C->enqueue(9);
    C->enqueue(7);
    C->enqueue(5);
    append(A, C, 2);
    cout << "Queue C Values after append of 2 values from A: ";
    display(C, cout);

    Queue *D = new MyQueue(MAX_SIZE);
    reverseAppend(C, D);
    cout << "Queue D Values after reverse append from V: ";
    display(D, cout);

    int mx = 0;
    float ag = 0.0;
    stats(A, mx, ag);
    cout << "Queue A Values: ";
    display(A, cout);
    cout << "Average is " << ag << " maximum is " << mx << endl;

    Queue *M = new MyQueue(MAX_SIZE);
    Queue *N = new MyQueue(MAX_SIZE);
    Queue *P = new MyQueue(MAX_SIZE);

    append(A, M);
    append(M, N);
    append(N, P);

    if (!isEqual(A, M)) {
        cout << "Not Equal:\n";
    } else {
        cout << "Equal:\n";
    }

    if (!isEqual(A, P)) {
        cout << "Not Equal:\n";
    } else {
        cout << "Equal:\n";
    }

    delete A;
    delete B;
    delete C;
    delete D;
    delete M;
    delete N;
    delete P;

    return 0;
}

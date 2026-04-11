#include <cinttypes>
#include <filesystem>
#include <iostream>
using namespace std;
#include "MyQueue.h"
#include "MyStack.h"
#include "Queue.h"
#include "Stack.h"

const int MAX_SIZE = 10;

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
 * make a copy of the original queue to preserve it
 * empty the copy queue and set a counter till the queue is emptied
 * that counter will be the size or the number of values present in the queue
*/
int getSize(Queue *q) {
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
 * firstly, make individual copies of the two queues along with saving their sizes in two variables
 * empty the destination queue and then enqueue the values back into it till the position given in the parameter
 * so for example if the dst queue was 1 2 3 4 5 and pos was 2 then it would now be 1 2 
 * then, empty the src copy queue and add its values to the dst queue
 * so for example if the src queue was 10 20 30 then dst queue would now be 1 2 10 20 30
 * add the remaining values of the dst copy queue back to the dst queue
 * finally, dst queue would look like this: 1 2 10 20 30 3 4 5
*/
void insert(Queue *src, Queue *dst, int pos) {
    int dstSize = getSize(dst);
    int valsAfterPos = dstSize - pos;

    Queue *copyDst = new MyQueue(*dst);
    Queue *copySrc = new MyQueue(*src);
    
    while (!dst->isEmpty()) {
	int val = dst->dequeue();
    }
    if (pos > dstSize) {
	pos = dstSize;	
    }
    for (int i = 0; i < pos; i++) {
	int val = copyDst->dequeue();
	dst->enqueue(val);
    }
    while (!copySrc->isEmpty() && !dst->isFull()) {
	int val = copySrc->dequeue();
	dst->enqueue(val);
    }
    while (!copyDst->isEmpty() && !dst->isFull()) {
	int val = copyDst->dequeue();
	dst->enqueue(val);
    }
    delete copyDst;
    delete copySrc;
}

/*
 * firstly, make individual copies of the two queues along with saving their sizes in two variables
 * empty the destination queue and then enqueue the values back into it till the position given in the parameter
 * so for example if the dst queue was 1 2 3 4 5 and pos was 2 then it would now be 1 2 
 * then, add the parameter value to the dst queue
 * so for example if the parameter value was 10 then dst queue would now be 1 2 10
 * add the remaining values of the dst copy queue back to the dst queue
 * finally, dst queue would look like this: 1 2 10 3 4 5
*/
void insert(Queue *q, int v, int pos) {
    int qSize = getSize(q);
    int valsAfterPos = qSize - pos;

    Queue *copyQ = new MyQueue(*q);
    
    while (!q->isEmpty()) {
	int val = q->dequeue();
    }
    if (pos > qSize) {
	pos = qSize;	
    }
    for (int i = 0; i < pos; i++) {
	int val = copyQ->dequeue();
	q->enqueue(val);
    }
    q->enqueue(v);
    while (!copyQ->isEmpty() && !q->isFull()) {
	int val = copyQ->dequeue();
	q->enqueue(val);
    }
    delete copyQ;
} // insert a value in the queue at the given position

int getQueueValAtPos(Queue *q, int pos) {
    int qSize = getSize(q);
    Queue *copyQ = new MyQueue(*q);

    if (pos > qSize) {
	pos = qSize;	
    }
    for (int i = 0; i < pos; i++) {
	int val = copyQ->dequeue();
    }
    int returnVal = copyQ->dequeue();
    return returnVal;
}

/*
 * get the value at the position from which we have to shift the queue
 * by inserting the value at the position given by the parameter, the queue will essentially be shifted right
 * 1 2 3 4 5 -> shift from pos 2 (get val at pos 2 which is 3)
 * so, insert 3 at pos 2 hence the queue will look like this: 1 2 3 3 4 5
*/
void shiftRight(Queue *q, int pos) {
    int valAtPos = getQueueValAtPos(q, pos);
    insert(q, valAtPos, pos);
}
/*
 * make a copy of the queue
 * empty the original queue
 * add the values back into the original queue till the position
 * dequeue (waste) one value (which is the value at the position given in the parameter) from the copied queue
 * add the remaining values back to the original queue
*/
void shiftLeft(Queue *q, int pos) {
    Queue *copyQ = new MyQueue(*q);
    int val;

    while (!q->isEmpty()) {
	val = q->dequeue();
    }

    for (int i = 0; i < pos; i++) {
	val = copyQ->dequeue();
	q->enqueue(val);
    }
    val = copyQ->dequeue();

    while (!copyQ->isEmpty() && !q->isFull()) {
	val = copyQ->dequeue();
	q->enqueue(val);
    }
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
  A->enqueue(10);
  A->enqueue(9);
  A->enqueue(2);
  A->enqueue(5);
  A->enqueue(-7);
  cout << " Queue A Values: ";
  display(A, cout);
  Queue *B = new MyQueue(MAX_SIZE);
  insert(B, -100, 2);
  cout << " Queue B Values after insert: ";
  display(B, cout);
  insert(A, B, 2);
  cout << " Queue B Values after insert: ";
  display(B, cout);
  shiftRight(B, 2);
  cout << " Queue B Values after shiftRight from pos 2: ";
  display(B, cout);
  shiftLeft(B, 2);
  cout << " Queue B Values after shiftLeft from pos 2: ";
  display(B, cout);

  return 0;
}

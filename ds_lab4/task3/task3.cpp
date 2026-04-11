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
 * enqueue these values in the destination queue
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
int get(Queue * q, int pos) {
    int qSize = getSize(q);
    Queue *copyQ = new MyQueue(*q);
    
    while (!q->isEmpty()) { int val = q->dequeue(); }

    if (pos > qSize) {
	pos = qSize;	
    }
    for (int i = 0; i < pos; i++) {
	int val = copyQ->dequeue();
	q->enqueue(val);
    }
    int returnVal = q->dequeue();
    while (!copyQ->isEmpty() && !q->isFull()) {
	int val = copyQ->dequeue();
	q->enqueue(val);
    }
    delete copyQ;
    return returnVal;
} // get from the queue the value at the given position after removing from the Queue

void sort(Queue *q) {

} // Sort the values in the queue in ascending order

bool isPalindrome(int num) {
    string number = to_string(num);
    
    int strlen = number.length();

    for (int i = 0; i < strlen; i++) {
	if (number[i] != number[strlen - i - 1]) {
	    return false;
	}
    }
    return true;
}

bool isPalindrome(Queue *q) {
    Queue *copyQ = new MyQueue(*q);
    while (!copyQ->isEmpty()) {
	int val = copyQ->dequeue();
	if (!isPalindrome(val)) return false;
    }
    return true;
} // check if the values in the queue are Palindrome

/*
 * by extracting the values from the queue, concatenate them and form an integer and check if that integer is a palindrome
*/
void isPalindrome(Queue *q, bool &palindrome) {
    Queue *copyQ = new MyQueue(*q);
    int num = 0;

    while (!copyQ->isEmpty()) {
	int val = copyQ->dequeue();
	num = num*10 + val;
    }
    palindrome = isPalindrome(palindrome);
} //where single digits are stored and you can’t use any other Queue or Stack or ADT

void rotateLeft (Queue * q, int pos) {
    Queue *copyQ = new MyQueue(*q);

    while (!q->isEmpty()) {int val = q->dequeue(); }

    for (int i = 0; i < pos; i++) {
	int val = copyQ->dequeue();
	q->enqueue(val);
    }

    int rotationValue = copyQ->dequeue();
    
    while (!copyQ->isEmpty() && !q->isFull()) {
	int val = copyQ->dequeue();
	q->enqueue(val);
    }
    q->enqueue(rotationValue);

    delete copyQ;
}
void rotateRight (Queue * q, int pos) {
    Queue *copyQ = new MyQueue(*q);

    while (!q->isEmpty()) {int val = q->dequeue(); }

    for (int i = 0; i < pos; i++) {
	int val = copyQ->dequeue();
	q->enqueue(val);
    }

    int rotationValue = copyQ->dequeue();
    
    while (!copyQ->isEmpty() && !q->isFull()) {
	int val = copyQ->dequeue();
	q->enqueue(val);
    }
    q->enqueue(rotationValue);

    delete copyQ;

}

int main() {
    Queue* A = new MyQueue(MAX_SIZE);
    A->enqueue(10);
    A->enqueue(9);
    A->enqueue(2);
    A->enqueue(5);
    A->enqueue(-7);
    cout << " Queue A Values: ";
    display(A, cout);

    rotateRight(A, 2);
    cout << " Queue A Values after rotateRight from pos 2";
    display(A, cout);
    rotateLeft(A, 2);
    cout << " Queue B Values after rotateLeft from pos 2: ";
    display(A, cout);
    int v = get(A, 3);
    cout << "Value at pos 3: " << v << endl;
    cout << " Queue A Values after get from pos 3: ";
    display(A, cout);
    if(isPalindrome(A))
    {
    cout << "A is a Palindrome\n";
    }
    else
    {
    cout << "A is NOT a Palindrome\n";
    }
    Queue* B = new MyQueue(MAX_SIZE);
    B->enqueue(234);
    B->enqueue(56);
    B->enqueue(786);
    B->enqueue(56);
    B->enqueue(234);
    if(isPalindrome(B))
    {
    cout << "C is a Palindrome\n";
    }
    else
    {
    cout << "C is NOT a Palindrome\n";
    }
    Queue* C = new MyQueue(MAX_SIZE);
    C->enqueue(3);
    C->enqueue(5);
    C->enqueue(7);
    C->enqueue(5);
    C->enqueue(3);
    bool isIt = false;
    isPalindrome(C, isIt);
    if(C)
    {
    cout << "C is a Palindrome\n";
    }
    else
    {
    cout << "C is NOT a Palindrome\n";
    }
    sort(C);
    cout << " Queue C Values after sort in ascending \n";
    display(C, cout);
    return 0;
}

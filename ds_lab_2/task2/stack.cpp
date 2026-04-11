#include <iostream>
using namespace std;

#include "Stack.h"
#include "MyStack.h"

const int MAX_SIZE = 10;

void read(Stack *S, istream & in, int n) {
    int val = 0;
    for (int i = 0; i < n; i++) {
	cout << "Enter value: ";
	in >> val;
	S->push(val);
    }
} 

int stackSize(Stack *S) {
    Stack *temp = new MyStack(*S);
    int counter = 0;
    
    int val;
    while (temp->pop(val)) {
	counter++;
    }
    return counter;
}

void display(Stack *S, ostream & out) {
    Stack *temp = new MyStack(*S);
    int stackLen= stackSize(S);
    Stack *copyStack = new MyStack(stackLen);
    temp = new MyStack(*S);
    int val;

    while (temp->pop(val)) {
	copyStack->push(val);
    }
    while (copyStack->pop(val)) {
	out << val << " ";
    }
    cout << endl;
}

void copy(Stack *src, Stack *dst) {
    Stack *temp = new MyStack(*src);
    Stack *copyStack = new MyStack(MAX_SIZE);

    int val;
    while (temp->pop(val)) {
	copyStack->push(val);
    }
    while (copyStack->pop(val)) {
	dst->push(val);
    }
}

void insert(Stack *src, Stack *dst, int pos) {
    int dstSize = stackSize(dst);
    int valsAbovePos = dstSize - pos;
    int val = 0;

    Stack * tempDstStack = new MyStack(MAX_SIZE);
    for (int i = 0; i < valsAbovePos; i++){
	dst->pop(val);
	tempDstStack->push(val);
    }

    Stack * copySrcStack = new MyStack(*src);
    Stack * reverseCopySrcStack = new MyStack(MAX_SIZE);

    while (copySrcStack->pop(val)) {
	reverseCopySrcStack->push(val);
    }
    while (reverseCopySrcStack->pop(val)) {
	dst->push(val);
    }

    while (tempDstStack->pop(val)) {
	dst->push(val);
    }
}

void shiftLeft(Stack *s, int pos) {
    Stack *copyStack = new MyStack(*s);
    int srcSize = stackSize(s);
    int valsAbovePos = srcSize - pos;
    
    int val;
    Stack *someValues = new MyStack(MAX_SIZE);
    for (int i = 0; i < valsAbovePos; i++) {
	copyStack->pop(val);
	someValues->push(val);
    }
    for (int i = 0; i < valsAbovePos - 1; i++) {
	s->pop(val);
    }
    while (someValues->pop(val)) {
	s->push(val);
    }
}

void shiftRight(Stack *s, int pos) {
    Stack *copyStack = new MyStack(*s);
    int srcSize = stackSize(s);
    int valsAbovePos = srcSize - pos;
    
    int val;
    Stack *someValues = new MyStack(MAX_SIZE);
    for (int i = 0; i < valsAbovePos; i++) {
	copyStack->pop(val);
	someValues->push(val);
    }
    for (int i = 0; i < valsAbovePos + 1; i++) {
	s->pop(val);
    }
    while (someValues->pop(val)) {
	s->push(val);
    }
}

void stats(Stack *s, int &max, float &average) {
    Stack *copyStack = new MyStack(*s);
    float sSize = stackSize(s);
    int sum = 0;

    int val;
    while (copyStack->pop(val)) {
	sum += val;
	if (val > max) {
	    max = val;
	}
    }
    average = sum / sSize;
}

int main()
{
    Stack *A = new MyStack(MAX_SIZE);

    int n = 0;
    cout << "please select a number between 1 and " << MAX_SIZE << ": ";
    cin >> n;

    read(A, cin, n);

    cout << "Stack A Values: ";
    display(A, cout);
    Stack * B = new MyStack(MAX_SIZE);
    copy(A, B);
    cout << "Stack B Values: ";
    display(B, cout);
    Stack * C = new MyStack(MAX_SIZE);
    C->push(8);
    C->push(9);
    C->push(10);
    insert(A, C, 2);
    cout << "Stack C Values: ";
    display(C, cout);

    shiftLeft(C, 2);
    cout << "Stack C Values: ";
    display(C, cout);

    shiftRight(C, 2);
    cout << "Stack C Values: ";
    display(C, cout);

    int mx = 0;
    float ag = 0.0;
    stats(C, mx, ag);
    cout << "Stack C Values: ";
    display(C, cout);
    cout << "Average is " << ag << " maximum is " << mx << endl;

    return 0;
}

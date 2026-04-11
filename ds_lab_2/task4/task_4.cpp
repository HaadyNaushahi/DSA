#include <iostream>
#include <fstream>
#include "MyStack.h"
#include <string>
using namespace std;

int MAX_SIZE = 100;

void read(Stack *S, istream & in) {
    string val;
    while (in >> val) {
	S->push(val);
    }
} 

int stackSize(Stack *S) {
    Stack *temp = new MyStack(*S);
    int counter = 0;
    
    string val;
    while (temp->pop(val)) {
	counter++;
    }
    return counter;
}

void display(Stack *S, ostream & out) {
    Stack *copyStack = new MyStack(*S);
    string val;
    while (copyStack->pop(val)) {
	out << val << " ";
    }
    cout << endl;
}

void copy(Stack *src, Stack *dst) {
    Stack *copyStack = new MyStack(*src);

    string val;
    while (copyStack->pop(val)) {
	dst->push(val);
    }
}

void insert(Stack *src, Stack *dst, int pos) {
    int dstSize = stackSize(dst);
    int valsAbovePos = dstSize - pos;
    string val;

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

Stack *removeDuplicates(Stack *s) {
    Stack *copyStack = new MyStack(*s);
    Stack *noDuplicates = new MyStack(MAX_SIZE);

    string val;
    while (copyStack->pop(val)) {
	if (val != noDuplicates->top()) {
	    noDuplicates->push(val);
	}
    }

    return noDuplicates;
}

void countFrequency(Stack *s, Stack *counts) {

}

int main() {
    ifstream in;
    in.open("text.txt");


    Stack * myStack = new MyStack(MAX_SIZE);
    read(myStack, in);

    display(myStack, cout);
    
    Stack *noDuplicates = removeDuplicates(myStack);
    display(noDuplicates, cout);


    return 0;
}

#include <iostream>
#include "MyStack.h"
#include <string>
using namespace std;

int MAX_SIZE = 10;

bool isPrime(int num) {
    for (int i = num - 1; i > 1; i--) {
	if (num % i == 0) {
	    return false;
	}
    }
    return true;
}

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

bool isPerfectSquare(int num) {
    for (int i = 1; i < num; i++) {
	int product = i * i;
	if (product > num) {
	    return false;
	}
	if (product == num) {
	    return true;
	}
    }
    return false;
}

int main() {
    Stack * myStack = new MyStack(MAX_SIZE);

    myStack->push(1);
    myStack->push(2);
    myStack->push(4);
    myStack->push(8);
    myStack->push(16);

    int val;
    while (myStack->pop(val)) {
	cout << "Value: " << val << "\t: ";
	cout << "Details: \t ";
	cout << "Palindrome: ";
	cout << ((isPalindrome(val)) ? "yes,\t " : "no,\t ");
	cout << "Prime: ";
	cout << ((isPrime(val)) ? "yes,\t " : "no,\t ");
	cout << "Perfect Square: ";
	cout << ((isPerfectSquare(val)) ? "yes,\t " : "no,\t ");
	cout << endl;
    }


    return 0;
}

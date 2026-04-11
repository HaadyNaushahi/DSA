#include "myLinkedList.h"
#include <iostream>
using namespace std;

int main() {
    myLinkedList list;

    cout << "Insert at last:\n";
    list.insertAtLast(10);
    list.insertAtLast(20);
    list.insertAtLast(30);
    list.display();

    cout << "\nInsert at first:\n";
    list.insertAtFirst(5);
    list.display();

    cout << "\nSize: " << list.getSize() << endl;

    cout << "\nSearch 20: " << list.search(20) << endl;
    cout << "Search 99: " << list.search(99) << endl;

    cout << "\nPeek position 2: " << list.peek(2) << endl;

    cout << "\nInsert 15 at pos 2:\n";
    list.put(15, 2);
    list.display();

    cout << "\nRemove from first: " << list.removeFromFirst() << endl;
    list.display();

    cout << "\nRemove from last: " << list.removeFromLast() << endl;
    list.display();

    cout << "\nGet (remove) pos 1: " << list.get(1) << endl;
    list.display();

    cout << "\nSwap pos 0 and 1:\n";
    list.swap(0, 1);
    list.display();

    cout << "\nSort ascending:\n";
    list.sort(true);
    list.display();

    cout << "\nSort descending:\n";
    list.sort(false);
    list.display();

    return 0;
}
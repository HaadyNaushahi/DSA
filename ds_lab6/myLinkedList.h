#pragma once
#include "LinkedList.h"
#include <iostream>
using namespace std;

class myLinkedList :public LinkedList{
public:
    myLinkedList();
    myLinkedList(const myLinkedList& l);
    ~myLinkedList();
    void insertAtLast(int value);
    void insertAtFirst(int value);
    void display();
    int removeFromFirst();
    int removeFromLast();
    int getSize();
    bool search(int v);
    int peek(int pos);
    int get(int pos);
    bool isEmpty();
    void put(int v, int pos);
    void swap(int xi, int yi);
    void sort(bool asc);

};

myLinkedList::myLinkedList() {
    first = nullptr;
    last = nullptr;
}

myLinkedList::myLinkedList(const myLinkedList & l){
        first = last = nullptr;
        Node* temp = l.first;

        while (temp != nullptr){
            insertAtLast(temp->data);
            temp = temp->next;
        }
}

myLinkedList::~myLinkedList(){
    while (!isEmpty()){
        removeFromFirst();
    }
}

bool myLinkedList::isEmpty(){
    return first == nullptr && last == nullptr;
}

int myLinkedList::removeFromLast(){
    if (first == nullptr && last == nullptr) //empty linked list
    {
        cout << "LL is empty; returing NULL value" << endl;
        return -99999;
    }
    else if (first == last) //single node case
    {
        int returingValue = first->data;
        delete last;
        first = nullptr;
        last = nullptr;
        return returingValue;
    }
    else
    {
        Node* t = first;
        while (1)
        {
            if (t->next == last)
            {
                break;
            }
            t = t->next;
        }

        int returingValue = last->data;
        delete last;
        t->next = nullptr;
        last = t;
        return returingValue;
    }
}

int myLinkedList::removeFromFirst()
{
    if (first == nullptr && last == nullptr) //empty linked list
    {
        cout << "LL is empty; returing NULL value" << endl;
        return -99999;
    }
    else if (first == last) //single node case
    {
        int returingValue = first->data;
        delete last;
        first = nullptr;
        last = nullptr;
        return returingValue;
    }
    else
    {
        int returingValue = first->data;
        Node* t = first;
        first = first->next;
        delete t;
        t = nullptr;
        return returingValue;
    }
}

void myLinkedList::display()
{
    if (first == nullptr && last == nullptr)
    {
        cout << "->\n";
        return;
    }
    Node* t = first;
    while (1)
    {
        cout << t->data;
        cout << " -> ";
        t = t->next;
        if (t == nullptr)
        {
            //cout << "nullptr";
            break;
        }
    }
    cout << endl;
}

void myLinkedList::insertAtFirst(int value)
{
    Node* nn = new Node;
    nn->data = value;
    nn->next = nullptr;
    if (first == nullptr && last == nullptr) //first node case
    {
        first = nn;
        last = nn;
    }
    else // for all Nodes other than the first
    {
        nn->next = first;
        first = nn;
    }
}

void myLinkedList::insertAtLast(int value)
{
    Node* nn = new Node;
    nn->data = value;
    nn->next = nullptr;
    if (first == nullptr && last == nullptr) //first node case
    {
        first = nn;
        last = nn;
    }
    else // for all Nodes other than the first
    {
        last->next = nn;
        last = nn;
    }
}

int myLinkedList::getSize() {
    int count = 0;
    Node* t = first;

    while (t != nullptr){
        count++;
        t = t->next;
    }
    return count;
}

bool myLinkedList::search(int v) {
    Node* t = first;
    while (t != nullptr) {
        if (t->data == v) {
            return true;
        }
        t = t->next;
    }
    return false;
}

int myLinkedList::peek(int pos) {
    Node* t = first;
    int counter = 0;
    while (counter < pos) {
        counter++;
        t = t->next;
    }
    if (t == nullptr) return -99999;
    return t->data;
}

int myLinkedList::get(int pos) {
    Node* t = first;
    Node* prev = first;

    if (pos == 0)
        return removeFromFirst();

    int counter = 0;
    while (t != nullptr && counter < pos) {
        prev = t;
        t = t->next;
        counter++;
    }

    if (t == nullptr) return -99999;

    prev->next = t->next;
    if (t == last) last = prev;
    int val = t->data;
    delete t;
    return val;

}

void myLinkedList::put(int v, int pos) {
    
    Node* current = first;
    Node* prev = first;

    if (pos == 0) {
        insertAtFirst(v);
        return;
    }

    int counter = 0;
    while (current != nullptr && counter < pos) {
        prev = current;
        current = current->next;
        counter++;
    }
    if (counter != pos) {
        cout << "\ninvalid index\n";
        return;
    }
    Node* newNode = new Node;
    newNode->data = v;

    prev->next = newNode;
    newNode->next = current;
    if (current == nullptr) last = newNode;
}

void myLinkedList::swap(int xi, int yi) {
    if (xi == yi) return;

    Node* a = first;
    Node* b = first;
    int i = 0;

    while (a != nullptr && i < xi){
        a = a->next;
        i++;
    }

    i = 0;
    while (b != nullptr && i < yi){
        b = b->next;
        i++;
    }

    if (a != nullptr && b != nullptr){
        int temp = a->data;
        a->data = b->data;
        b->data = temp;
    }
}

void myLinkedList::sort(bool asc) {
    if (isEmpty() || first->next == nullptr)
        return;

    for (Node* i = first; i != nullptr; i = i->next)
    {
        for (Node* j = i->next; j != nullptr; j = j->next)
        {
            if ((asc && i->data > j->data) || (!asc && i->data < j->data))
            {
                int temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}
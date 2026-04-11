#include <iostream>
#include "AbstractArray.h"
#include "MyArray.h"

using namespace std;

void read(MyArray *A, istream &in, int n)
{
    int value;

    for (int i = 0; i < n; i++)
    {
        cout << "Enter value: ";
        in >> value;
        A->add(value);
    }
}

void display(MyArray *A, ostream &out)
{
    int value;

    for (int i = 0; i <= A->currentIndex; i++)
    {
        if (A->get(i, value))
            out << value << " ";
    }

    out << endl;
}

void copy(MyArray *src, MyArray *dst)
{
    int value;

    for (int i = 0; i <= src->currentIndex; i++)
    {
        if (src->get(i, value))
            dst->add(value);
    }
}

void shiftRight(MyArray *aa, int pos)
{
    if (aa->isFull())
        return;

    int value;

    aa->currentIndex++;

    for (int i = aa->currentIndex; i > pos; i--)
    {
        aa->get(i - 1, value);
        aa->insert(i, value);
    }
}

void shiftLeft(MyArray *aa, int pos)
{
    int value;

    for (int i = pos; i < aa->currentIndex; i++)
    {
        aa->get(i + 1, value);
        aa->insert(i, value);
    }

    aa->currentIndex--;
}

void insert(MyArray *src, MyArray *dst, int pos)
{
    int value;

    for (int i = 0; i <= src->currentIndex; i++)
    {
        shiftRight(dst, pos);

        src->get(i, value);
        dst->insert(pos, value);

        pos++;
    }
}

void stats(MyArray *AA, int &max, float &average)
{
    int sum = 0;
    int value;

    if (AA->isEmpty())
        return;

    AA->get(0, max);

    for (int i = 0; i <= AA->currentIndex; i++)
    {
        AA->get(i, value);

        if (value > max)
            max = value;

        sum += value;
    }

    average = (float)sum / (AA->currentIndex + 1);
}

int main()
{
    const int MAX_SIZE = 10;

    MyArray *A = new MyArray(MAX_SIZE);

    int n;
    cout << "please select a number between 1 and " << MAX_SIZE << ": ";
    cin >> n;

    read(A, cin, n);

    cout << "Array A Values: ";
    display(A, cout);

    MyArray *B = new MyArray(MAX_SIZE);
    copy(A, B);

    cout << "Array B Values: ";
    display(B, cout);

    MyArray *C = new MyArray(MAX_SIZE);

    C->add(9);
    C->add(7);
    C->add(5);

    insert(A, C, 2);

    cout << "Array C Values: ";
    display(C, cout);

    shiftLeft(C, 2);

    cout << "Array C Values: ";
    display(C, cout);

    shiftRight(C, 2);

    cout << "Array C Values: ";
    display(C, cout);

    int mx = 0;
    float ag = 0.0;

    stats(C, mx, ag);

    cout << "Array C Values: ";
    display(C, cout);

    cout << "Average is " << ag << " maximum is " << mx << endl;

    delete A;
    delete B;
    delete C;

    return 0;
}

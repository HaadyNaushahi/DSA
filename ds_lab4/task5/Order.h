#include <iostream>
#include <string>
using namespace std;

class Order {
private:
    string item;
    int price;
    int timeTaken;
public:
    Order() {
	this->item = "";
	this->price = 0;
	this->timeTaken = 0;
    }
    Order(string newItem, int newPrice, int timeTaken) {
	this->item = newItem;
	this->price = newPrice;
	this->timeTaken = timeTaken;
    }
    ~Order() {}
    friend ostream &operator<<(ostream &out, const Order & o);
};
ostream & operator<<(ostream & out, const Order & o) 
{
    out << "Item: "     << o.item
        << " | Price: " << o.price    << " PKR"
        << " | Time Taken: "<< o.timeTaken << " min";
    return out;
};


#include <iostream>
using namespace std;

class Employee {
public:
	Employee() {
		cout << "Default employee called" << endl;
	}
	virtual int calculateSalary() = 0;
};

class FullTimeEmployee :public Employee {
	int salary;
public:

	FullTimeEmployee(int salary) : Employee() {
		cout << "Parameterized employee called" << endl;
		this->salary = salary;
	}
	int calculateSalary() override {
		return salary;
	}
};
class PartTimeEmployee :public Employee {
	int hours;
	int rate;
public:

	PartTimeEmployee(int hours , int rate) : Employee() {
		cout << "Parameterized employee called" << endl;
		this->hours = hours;
		this->rate = rate;
	}
	int calculateSalary() override {
		return hours * rate;
	}
};

int main() {
	Employee* e1 = new FullTimeEmployee(1500000);
	Employee* e2 = new PartTimeEmployee(4,1000);
	cout << "Full time employee salary " << e1->calculateSalary() << endl;
	cout << "Part time employee salary " << e2->calculateSalary() << endl;

#include <iostream>
using namespace std;

class Course {
public:
	Course() {
		cout << "Default constructor called" << endl;
	}
	virtual void area() = 0;
};

class OnlineCourse : public Course{
	int weeks;
	int hoursPerWeek;
public:
	OnlineCourse(int w, int h) :weeks(w), hoursPerWeek(h), Course(){
		cout << "Parametrized constructor called" << endl;
	}
	void area() override{
		cout << "Total duration time online course: " << weeks * hoursPerWeek << endl;
	}
};

class OfflineCourse : public Course{
	int months;
	int hoursPerDay;
public:
	OfflineCourse(int m, int h) :months(m), hoursPerDay(h), Course(){
		cout << "Parametrized constructor called" << endl;
	}
	void area() override{
		cout << "Total duration time offline course: " << months * hoursPerDay << endl;
	}
};

int main() {
	Course* c1 = new OnlineCourse(5, 8);
	Course* c2 = new OfflineCourse(12, 2);
	c1->area();
	c2->area();
}

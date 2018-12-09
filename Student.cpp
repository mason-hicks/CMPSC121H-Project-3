/**
* Student.cpp
* Mason Hicks
* CMPSC121H-800
* 3 December 2018
* Creates bodies for Student Class functions
**/
#include "Student.h"
#include <string>
using namespace std;

//For when you have everything premade and wanna do more work (idk why youd do that tho)
Student::Student(string fn, char mi, string ln, string id, string uname, vector<Course> c) {
	firstName = fn;
	middleInitial = mi;
	lastName = ln;
	psuID = id;
	psuUsername = uname;
	courses = c;
}

//For when you dont have a vector of courses yet
Student::Student(string fn, char mi, string ln, string id, string uname) {
	firstName = fn;
	middleInitial = mi;
	lastName = ln;
	psuID = id;
	psuUsername = uname;
}

//For when you need this program to hold you hand at every damn step
Student::Student(string id) {
	string fn, ln, uname;
	char mi;
	vector<Course> c;

	cout << "Enter the student's first name: ";
	cin >> fn;
	cout << "Enter the student's middle initial: ";
	cin >> mi;
	cout << "Enter the student's last name: ";
	cin >> ln;
	cout << "Enter the student's PSU Username: ";
	cin >> uname;

	firstName = fn;
	middleInitial = mi;
	lastName = ln;
	psuID = id;
	psuUsername = uname;
	courses = c;
}

//The only way we can use the << is if we have access to the private member variables but it cannot
//Inherently use that so we have to take this stupid ass approach to get all the variables
//Because im too lazy to look up any other way on stack overflow
string Student::getFirstName() { return firstName; }
char Student::getMiddleInitial() { return middleInitial; }
string Student::getLastName() { return lastName; }
string Student::getPsuId() { return psuID; }
string Student::getPsuUsername() { return psuUsername; }
vector<Course> Student::getCourses() { return courses; }

//So we can print a student very easily
ostream& operator << (ostream& os, Student student) {
	os << "FNAME: " << student.getFirstName() << endl;
	os << "MINIT: " << student.getMiddleInitial() << endl;
	os << "LNAME: " << student.getLastName() << endl;
	os << "ID:    " << student.getPsuId() << endl;
	os << "USER:  " << student.getPsuUsername() << "\n\n";
	for (int i = 0; i<student.getCourses().size(); i++) {
		os << student.getCourses()[i];
	}
	return os;
}

//Its in the name, it adds a course to the list
void Student::addCourse() {
	Course c;
	for (int i = 0; i < courses.size(); i++) {
		if (c.overlap(courses[i])) {
			cout << "DID NOT ADD: " << c;
			return;
		}
	}
	courses.push_back(c);
}

//See line 77
void Student::addCourse(Course c) {
	for (int i = 0; i < courses.size(); i++) {
		if (courses[i].overlap(c)) {
			cout << "DID NOT ADD: " << c;
			return;
		}
	}
	courses.push_back(c);
}

//Removes a course based on user input
void Student::removeCourse() {
	if (courses.size() > 0) {
		int choice;
		cout << "Select a course to remove:\n";
		for (int i = 0; i < courses.size(); i++) {
			cout << i+1 << ". " << courses[i].getName() << endl;
		}
		do {
			cout << "Choice: ";
			cin >> choice;
			choice--;
			if (choice < 0 || choice > courses.size()) cout << "Invalid choice! Try again.\n";
		} while (choice < 0 || choice > courses.size());
		vector<Course> tempCourses;
		for (int i = 0; i < courses.size(); i++) {
			if (i != choice) tempCourses.push_back(courses[i]);
		}
		courses = tempCourses;
	}
	else {
		cout << "There are no courses to remove!\n";
	}
}
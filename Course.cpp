/**
* Course.cpp
* Mason Hicks
* CMPSC121H-800
* 3 December 2018
* Creates bodies for Course Class functions
**/

#include "Course.h"
#include <string> 

//For when you wanna give the variables that are precollected (i.e. when automated)
Course::Course(string n, vector<Lecture> ses) {
	name = n;
	sessions = ses;
}

//For when you wanna have the user input the variables
Course::Course() {
	string n;
	vector<Lecture> ses;

	cout << "Enter the course name: ";
	cin >> n;

	bool doAgain;
	char inAgain;
	cout << "Would you like to add a lecture? (Y/N): ";
	while (cin >> inAgain && !(toupper(inAgain) == 'Y' || toupper(inAgain) == 'N')) {
		cout << "Invalid choice! Try again\n";
		cout << "Would you like to add a lecture? (Y/N): ";
	}
	doAgain = (toupper(inAgain) == 'Y');

	while (doAgain) {
		bool validToAdd = true;
		Lecture lect;
		for (int i = 0; i<ses.size(); i++) {
			validToAdd = validToAdd && !lect.overlap(ses[i]);
		}
		if (validToAdd) ses.push_back(lect);
		cout << "Would you like to add another lecture? (Y/N): ";
		while (cin >> inAgain && !(toupper(inAgain) == 'Y' || toupper(inAgain) == 'N')) {
			cout << "Invalid choice! Try again\n";
			cout << "Would you like to add a lecture? (Y/N): ";
		}
		doAgain = inAgain == 'Y';
	}

	name = n;
	sessions = ses;

}

//Returns the private variables
string Course::getName() { return name; }
vector<Lecture> Course::getSessions() { return sessions; }

//Checks to see if this course has any overlap with another course
bool Course::overlap(Course c) {
	vector<Lecture> cSessions = c.getSessions();
	for (int i = 0; i<sessions.size(); i++) {
		for (int j = 0; j < cSessions.size(); j++) {
			if (sessions[i].overlap(cSessions[j])) {
				cout << "---NOT AVAILABLE---\n";
				cout << "CLASS TIME: " << c.getName() << endl;
				cout << cSessions[j];
				return true;
			}
		}
	}
	return false;
}

//Sets it so you can do cout << {COURSE OBJECT}
ostream& operator << (ostream& os, Course course) {
	os << course.getName() << '\n';
	for (int i = 0; i<course.getSessions().size(); i++) {
		os << course.getSessions()[i];
	}
	return os;
}

//For when a user wants to add a session
void Course::addSession() {
	Lecture l;
	sessions.push_back(l);
}

//For automation purposes
void Course::addSession(Lecture l) {
	sessions.push_back(l);
}
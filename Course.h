/**
* Course.h
* Mason Hicks
* CMPSC121H-800
* 3 December 2018
* Sets up Course class with private variables and public member functions
**/
#pragma once
#include "Lecture.h"
using namespace std;
class Course {
	private:
		string name;
		vector<Lecture> sessions;
	public:
		Course(string, vector<Lecture>);
		Course();
		string getName();
		vector<Lecture> getSessions();
		bool overlap(Course otherCourse);
		friend ostream& operator << (ostream& os, Course course);
		void addSession();
		void addSession(Lecture);
};


/**
* Student.h
* Mason Hicks
* CMPSC121H-800
* 3 December 2018
* Sets up Student class with private variables and public member functions
**/

#pragma once
#include "Course.h"
using namespace std;

class Student {
	private:
		string firstName, lastName, psuID, psuUsername;
		char middleInitial;
		vector<Course> courses;
	public:
		Student(string, char, string, string, string, vector<Course>);
		Student(string, char, string, string, string);
		Student(string);
		string getFirstName();
		char getMiddleInitial();
		string getLastName();
		string getPsuId();
		string getPsuUsername();
		vector<Course> getCourses();
		friend ostream& operator << (ostream& os, Student student);

		void addCourse();
		void addCourse(Course);
		void removeCourse();

};


/**
* Lecture.h
* Mason Hicks
* CMPSC121H-800
* 3 December 2018
* Sets up Lecture class with private variables and public member functions
**/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Lecture {
	private:
		char dayOfWeek;
		int startingTime;
		int duration;
		bool isLecture;
	public:
		Lecture(char, int, int, int, bool);
		Lecture(char, int, int, bool);
		Lecture();

		char getDayOfWeek();
		int getStartingTime();
		int getEndingTime();
		int getDuration();
		bool getIsLecture();
		bool overlap(Lecture);
		friend ostream& operator << (ostream& os, Lecture lect);
};


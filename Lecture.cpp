/**
* Lecture.cpp
* Mason Hicks
* CMPSC121H-800
* 3 December 2018
* Creates bodies for Lecture Class functions
**/

#include "Lecture.h"
#include <iomanip>
#include <string>
using namespace std;

//I will never use it this way but I wanted to make it usable by others
Lecture::Lecture(char dow, int startHour, int startMin, int dur, bool isLect) {
	dayOfWeek = dow;
	startingTime = 60 * startHour + startMin;
	duration = dur;
	isLecture = isLect;
}

//Take day of week, raw starting time, duration, and whether or not its a lecture
//For use when inputting from file
Lecture::Lecture(char dow, int startTime, int dur, bool isLect) {
	dayOfWeek = dow;
	startingTime = startTime;
	duration = dur;
	isLecture = isLect;
}

//Takes in for private variables
//For use when user is adding a new lecture
Lecture::Lecture() {
	int startHour, startMinute, dur;
	string getPM, getLec;
	bool isPM, isInvalid = true, isLec;
	char dow;

	do {
		cout << "Enter the day of week (U, M, T, W, R, F, S): ";
		cin >> dow;
		dow = toupper(dow);
		if (dow == 'U' || dow == 'M' || dow == 'T' || dow == 'W' || dow == 'R' || dow == 'F' || dow == 'S') {
			isInvalid = false;
		}
		else {
			cout << "Invalid day of week! Try again.\n";
			isInvalid = true;
		}
	} while (isInvalid);

	//Get Starting Hour
	cout << "Enter the starting hour: ";
	while (cin >> startHour && (startHour < 0 || 23 < startHour)) {
		cout << "Invalid starting hour, please try again\n";
		cout << "Enter the starting hour: ";
	}

	//Get Starting Minute
	cout << "Enter the starting minute: ";
	while (cin >> startMinute && (startMinute < 0 || 59 < startMinute)) {
		cout << "Invalid starting minute, please try again\n";
		cout << "Enter the starting minute: ";
	}

	//Check to see if starting hour is in military time. If not then ask for AM or PM
	isInvalid = true;
	if (startHour < 13) {
		cout << "Is this in the morning or afternoon? (AM/PM): ";
		while (isInvalid && cin >> getPM) {
			if (getPM.length() == 2) {
				getPM = { (char)toupper(getPM.at(0)), (char)toupper(getPM.at(1)) };
				isInvalid = !(getPM == "AM" || getPM == "PM");
			}
			else {
				isInvalid = false;
			}
			if (isInvalid) {
				cout << "Invalid choice! Try again.\n";
				cout << "Is this in the morning or afternoon? (AM/PM): ";
			}
		}
		isPM = (getPM == "PM");
	} else {
		isPM = false; //Technically yes it is in the PM but when initializing start time, we add 720 if PM but the military time already accounts for this
	}

	//Get the duration
	cout << "Enter the duration: ";
	while (cin >> dur && dur < 1) {
		cout << "Invalid duration, please try again\n";
		cout << "Enter the duration: ";
	}

	//See if this is a lecture or lab
	do {
		cout << "Is this a lecture or a lab? (LEC/LAB): ";
		cin >> getLec;
		if (getLec.length() == 3) {
			getLec = { (char) toupper(getLec.at(0)), (char) toupper(getLec.at(1)), (char) toupper(getLec.at(2)) };
			if (getLec == "LEC" || getLec == "LAB") {
				isLec = (getLec == "LEC");
				isInvalid = false;
			}
			else {
				cout << "Invalid choice! Try again.\n";
				isInvalid = true;
			}
		}
		else {
			cout << "Invalid choice! Try again.\n";
			isInvalid = true;
		}
	} while (isInvalid);

	//Initialize private variables accordingly
	dayOfWeek = dow;
	startingTime = 60 * startHour + startMinute;
	duration = dur;
	if (isPM) startingTime += 720;
	isLecture = isLec;
}

//Getters
char Lecture::getDayOfWeek() { return dayOfWeek; }
int Lecture::getStartingTime() { return startingTime; }
int Lecture::getDuration() { return duration; }
int Lecture::getEndingTime() { return startingTime + duration; }
bool Lecture::getIsLecture() { return isLecture; }

//Takes another lecture as a parameter and returns whether or not they overlap
bool Lecture::overlap(Lecture otherLect) {
	bool startInvalid = otherLect.getStartingTime() <= startingTime && startingTime <= otherLect.getEndingTime();
	bool endInvalid = otherLect.getStartingTime() <= getEndingTime() && getEndingTime() <= otherLect.getEndingTime();
	return (dayOfWeek == otherLect.getDayOfWeek() && (startInvalid || endInvalid));
}

//This took way too much work but it makes it easier down the line
ostream& operator << (ostream& os, Lecture lect) {
	//Converts raw time into hour, minute, and time of day
	int sh = lect.getStartingTime() / 60;
	string pmStr;
	bool isPM = sh / 12;
	if (isPM) {
		sh -= 12;
		pmStr = " PM";
	}
	else {
		pmStr = " AM";
	}
	int sm = lect.getStartingTime() % 60;

	//Gets the day of week
	char dow = lect.getDayOfWeek();

	//Creates string for Lecture or Lab so it is shorter when returning
	string il;
	if (lect.getIsLecture()) {
		il = " Lecture";
	}
	else {
		il = " Lab";
	}

	//
	if (sm < 10) {
		return os << "- " << dow << " " << setw(2) << right << sh << " 0" << sm << pmStr << setw(4) << lect.getDuration() << il << "\n";
	}
	else {
		return os << "- " << dow << " " << setw(2) << right << sh << " " << sm << pmStr << setw(4) << lect.getDuration() << il << "\n";
	}
}
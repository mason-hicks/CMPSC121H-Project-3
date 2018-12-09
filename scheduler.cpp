/**
 * scheduler.cpp
 * Mason Hicks
 * CMPSC121H-800
 * 3 December 2018
 * Takes file input or user input to fill a Student object
 *   Will show schedule, modify schedule, output to file, and check availability if desired
**/

#include "Student.h"
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

int menu(bool);
void setTime(char &, int &);
string convToUpper(string);

int main() {
	bool doAgain = true;
	bool safeToExit = true;
	bool studentChosen = false;
	Student *student = new Student("", ' ', "", "", "");

	//Loops while option 6 is not chosen
	while (doAgain) {
		int choice = menu(studentChosen);
		if (choice == 1) { //Choose student
			if (safeToExit) {
				string id;
				cout << "Enter the student's 9-digit PSU ID: ";
				cin >> id;
				ifstream in(id + ".txt");
				if (in.good()) { //Makes sure file exists, if it does it gets info
					string fn, ln, user, id;
					char mi;
					string token;
					Lecture *lect;
					vector<Lecture> sess;
					Course *course = new Course("This will never happen but i need to get rid of an error", sess);
					vector<Course> classes;
					int counter = 0;
					while (in >> token) {
						if (token == "FNAME:") in >> fn;
						else if (token == "MINIT:") in >> mi;
						else if (token == "LNAME:") in >> ln;
						else if (token == "ID:") in >> id;
						else if (token == "USER:") in >> user;
						else if (token == "-") {
							char day;
							int startHour, startMinute, duration;
							bool isPM, isLec;
							string inPM, inLec;
							in >> day;
							in >> startHour;
							in >> startMinute;
							in >> inPM;
							in >> duration;
							in >> inLec;
							isPM = inPM == "PM";
							if (isPM) startHour += 12;
							isLec = inLec == "Lecture";
							lect = new Lecture(day, startHour, startMinute, duration, isLec);
							course->addSession(*lect);
							delete lect;
							lect = nullptr;
						}
						else {
							if (counter != 0) {
								classes.push_back(*course);
							}
							counter++;
							delete course;
							course = nullptr;
							course = new Course(token, sess);
						}
					}
					classes.push_back(*course);
					delete student;
					student = nullptr;
					student = new Student(fn, mi, ln, id, user);
					for (int i = 0; i < classes.size(); i++) {
						student->addCourse(classes[i]);
					}
					studentChosen = true;
				}
				else { //When file does not exist, it asks to create a new student
					cout << id << ".txt does not exist. Would you like to create a new student? (Y/N): ";
					char c;
					while (cin >> c && toupper(c) != 'Y' && toupper(c) != 'N') cout << "Invalid choice! Try again.\n" << id << ".txt does not exist. Would you like to create a new student? (Y/N): ";
					if (toupper(c) == 'Y') {
						student = new Student(id);
						studentChosen = true;
						safeToExit = false;
					}
				}
			}
			else {
				cout << "You are about to overwrite the previously unsaved student. Would you like to proceed? (Y/N): ";
				char c;
				while (cin >> c && toupper(c) != 'Y' && toupper(c) != 'N') cout << "Invalid choice! Try again.\nWould you like to proceed? (Y/N): ";
				if (toupper(c) == 'Y') {
					string id;
					cout << "Enter the student's 9-digit PSU ID: ";
					cin >> id;
					ifstream in(id + ".txt");
					if (in.good()) { //Makes sure file exists, if it does it gets info
						safeToExit = true;
						string fn, ln, user, id;
						char mi;
						string token;
						Lecture *lect;
						vector<Lecture> sess;
						Course *course = new Course("This will never happen but i need to get rid of an error", sess);
						vector<Course> classes;
						int counter = 0;
						while (in >> token) {
							if (token == "FNAME:") in >> fn;
							else if (token == "MINIT:") in >> mi;
							else if (token == "LNAME:") in >> ln;
							else if (token == "ID:") in >> id;
							else if (token == "USER:") in >> user;
							else if (token == "-") {
								char day;
								int startHour, startMinute, duration;
								bool isPM, isLec;
								string inPM, inLec;
								in >> day;
								in >> startHour;
								in >> startMinute;
								in >> inPM;
								in >> duration;
								in >> inLec;
								isPM = inPM == "PM";
								if (isPM) startHour += 12;
								isLec = inLec == "Lecture";
								lect = new Lecture(day, startHour, startMinute, duration, isLec);
								course->addSession(*lect);
								delete lect;
								lect = nullptr;
							}
							else {
								int conflict = -1;
								for (int i = 0; i < classes.size(); i++) {
									if (classes[i].overlap(*course)) {
										conflict = i;
										cout << "DID NOT ADD: " << (*course);
										safeToExit = false;
									}
								}
								if (counter != 0 && conflict == -1) {
									classes.push_back(*course);
								}
								counter++;
								delete course;
								course = nullptr;
								course = new Course(token, sess);
							}
						}
						classes.push_back(*course);
						delete student;
						student = nullptr;
						student = new Student(fn, mi, ln, id, user);
						for (int i = 0; i < classes.size(); i++) {
							student->addCourse(classes[i]);
						}
						studentChosen = true;
					}
					else { //When file does not exist, it asks to create a new student
						cout << id << ".txt does not exist. Would you like to create a new student? (Y/N): ";
						char c;
						while (cin >> c && toupper(c) != 'Y' && toupper(c) != 'N') cout << "Invalid choice! Try again.\n" << id << ".txt does not exist. Would you like to create a new student? (Y/N): ";
						if (toupper(c) == 'Y') {
							student = new Student(id);
							studentChosen = true;
							safeToExit = false;
						}
					}
				}
			}
		}
		if (choice == 2) { //Adds or deletes a course
			cout << "Add a new course or delete existing? (A/D): ";
			char c;
			while (cin >> c && toupper(c) != 'A' && toupper(c) != 'D') cout << "Invalid choice! Try again.\nAdd a new course or delete existing? (A/D): ";
			if (toupper(c) == 'A') {
				student->addCourse();
			}
			else {
				student->removeCourse();
			}
			safeToExit = false;
		}
		if (choice == 3) { //Checks student availability at current time or input time
			cout << "Check current day and time? (Y/N): ";
			char c;
			bool available = true;
			while (cin >> c && toupper(c) != 'Y' && toupper(c) != 'N') cout << "Invalid choice! Try again.\nCheck current day and time? (Y/N): ";
			if (toupper(c) == 'Y') {
				char day;
				int rawtime;
				setTime(day, rawtime);
				vector<Lecture> lec;
				lec.push_back(Lecture(day, rawtime, 0, true));
				for (int i = 0; i < student->getCourses().size(); i++) {
					available = available && !(Course("", lec)).overlap(student->getCourses()[i]);
				}
				if (available) {
					cout << "Student is available at: ";
					int rawtime;
					char day;
					setTime(day, rawtime);
					int hour = rawtime / 60;
					int minute = rawtime % 60;
					bool isPM = hour / 12;
					if (isPM) hour -= 12;
					switch (day) {
						case 'U':
							cout << "Sunday ";
							break;
						case 'M':
							cout << "Monday ";
							break;
						case 'T':
							cout << "Tuesday ";
							break;
						case 'W':
							cout << "Wednesday ";
							break;
						case 'R':
							cout << "Thursday ";
							break;
						case 'F':
							cout << "Friday ";
							break;
						case 'S':
							cout << "Saturday ";
							break;
					}
					cout << hour << ":";
					if (minute / 10 == 0) cout << "0";
					cout << minute << (isPM ? "PM" : "AM") << "\n";
				}
			}
			else {
				int hour, minute, rawtime;
				string timeOfDay;
				cout << "Enter day of week (U, M, T, W, R, F, S): ";
				while (cin >> c && !(c == 'U' || c == 'M' || c == 'T' || c == 'W' || c == 'R' || c == 'F' || c == 'S')) cout << "Invalid choice! Try again.\n" << "Enter day of week (U, M, T, W, R, F, S): ";
				cout << "Enter hour: ";
				while (cin >> hour && (hour < 0 || hour > 24)) cout << "Invalid choice! Try again.\nEnter hour: ";
				cout << "Enter minute: ";
				while (cin >> minute && (minute < 0 || minute > 60)) cout << "Invalid choice! Try again.\nEnter minute: ";
				if (hour < 13) {
					cout << "Enter AM or PM: ";
					while (cin >> timeOfDay && convToUpper(timeOfDay) != "AM" && convToUpper(timeOfDay) != "PM") cout << "Invalid choice! Try again.\nEnter AM or PM: ";
					//if (convToUpper(timeOfDay) == "PM") hour -= 12;
				}
				rawtime = hour * 60 + minute;
				vector<Lecture> lec;
				lec.push_back(Lecture(c, rawtime, 0, true));
				for (int i = 0; i < student->getCourses().size(); i++) {
					available = available && !(Course("", lec)).overlap(student->getCourses()[i]);
				}
				
				if (available) {
					cout << "Student is available at: ";
					switch (c) {
					case 'U':
						cout << "Sunday ";
						break;
					case 'M':
						cout << "Monday ";
						break;
					case 'T':
						cout << "Tuesday ";
						break;
					case 'W':
						cout << "Wednesday ";
						break;
					case 'R':
						cout << "Thursday ";
						break;
					case 'F':
						cout << "Friday ";
						break;
					case 'S':
						cout << "Saturday ";
						break;
					}
					cout << hour << ":";
					if (minute / 10 == 0) cout << "0";
					cout << minute << convToUpper(timeOfDay) << "\n";
				}
			}
		}
		if (choice == 4) { //Prints student schedule to console
			cout << (*student);
		}
		if (choice == 5) { //Outputs student schedule to file
			ofstream out(student->getPsuId() + ".txt");
			out << (*student);
			out.close();
			safeToExit = true;
		}
		if(choice == 6){ //Exits immediately if file has been written, warns user if unwritten
			if (safeToExit) {
				doAgain = false;
			}
			else {
				char c;
				cout << "You have not saved. Would you like to exit anyway? (Y/N): ";
				while (cin >> c && toupper(c) != 'Y' && toupper(c) != 'N') cout << "Invalid choice! Try again.\nYou have not saved. Would you like to exit anyway? (Y/N): ";
				doAgain = toupper(c) == 'N';
			}
		}
	}
}

//Makes it easier to adjust menu, returns value of valid choice
int menu(bool studentSelected) {
	int choice;
	cout << "\nChoose an option:\n";
	cout << "1. Select student\n";
	cout << "2. Modify schedule\n";
	cout << "3. Check student availability\n";
	cout << "4. Display schedule\n";
	cout << "5. Save to file\n";
	cout << "6. Quit\n";
	cout << "Choice: ";
	cin >> choice;
	
	if (!studentSelected && 2 <= choice && choice <= 5) {
		cout << "Student has not been selected yet! Choose another option.\n";
		return menu(studentSelected);
	}

	if (choice < 1 || choice > 6) {
		cout << "Invalid choice! Choose a valid option.\n";
		return menu(studentSelected);
	}

	return choice;
	
}

//Sets parameter values to character corresponding to current day and time
void setTime(char &day, int &rawtime) {
	time_t t = time(0);
	struct tm * timeinfo;
	timeinfo = localtime(&t);
	string s = asctime(timeinfo);

	day = s.at(0);
	if (day == 'T') {
		if (s.at(1) == 'h') day == 'R';
	}

	int hour = (s.at(11) - '0') * 10 + (s.at(12) - '0');
	int minute = (s.at(14) - '0') * 10 + (s.at(15) - '0');
	rawtime = hour * 60 + minute;
}

//Converts the string to all uppercase and returns it
string convToUpper(string s) {
	string tempS;
	for (char c : s) {
		tempS += toupper(c);
	}
	return tempS;
}
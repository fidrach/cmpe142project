#include "Student.h"

#define MAX_CODING_TIME

Student::Student(int SID) {
	this->SID = SID;
}

void Student::program() {
	cout << "Imma code" << endl;
	int seconds = rand() % MAX_CODING_TIME + 1;
	Sleep(seconds * 1000);
}

void Student::seek_help() {

}

void Student::wake_TA() {

}

void Student::wait() {
	
}
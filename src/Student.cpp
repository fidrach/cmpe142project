#include "Student.h"

#define MAX_CODING_TIME

static void OS_independent_sleep (int ms) {
	#ifdef linux
	usleep(ms*1000);	// usleep takes "microseconds"
	#endif

	#ifdef _WIN32
	Sleep(ms);
	#endif
}

Student::Student(int SID) {
	this->SID = SID;
}

void Student::program() {
	cout << "Imma code" << endl;
	int seconds = rand() % MAX_CODING_TIME + 1;
	OS_independent_sleep(seconds * 1000);
}

void Student::seek_help() {

}

void Student::wake_TA() {

}

void Student::wait() {
	
}
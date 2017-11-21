#include "Student.h"

#define MAX_CODING_TIME

static void os_independent_sleep(int ms) {
	#ifdef _WIN32
	Sleep(ms);
	#endif

	#ifdef linux
	usleep(1000 * ms);
	#endif
}

Student::Student(int SID) {
	this->SID = SID;
}

void Student::program() {
	cout << "Imma code" << endl;
	int seconds = rand() % MAX_CODING_TIME + 1;
	os_independent_sleep(seconds * 1000);
}

void Student::seek_help() {

}

void Student::wake_TA() {

}

void Student::wait() {
	
}
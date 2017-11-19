#include "TA.h"

static void OS_independent_sleep (int ms) {
	#ifdef linux
	usleep(ms*1000);	// usleep takes "microseconds"
	#endif

	#ifdef _WIN32
	Sleep(ms);
	#endif
}

TA::TA() {
	seed = 25; // TODO: change to time.now during prod
	max_sleep = 3;
	srand(seed);
}

void TA::sleep() {

}

void TA::check_for_student() {

}

void TA::wake_up() {

}

void TA::help() {
	cout << "Imma sleep" << endl;
	int seconds = rand() % max_sleep + 1;
	OS_independent_sleep(seconds*1000);
}


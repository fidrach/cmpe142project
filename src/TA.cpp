#include "TA.h"

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
	Sleep(seconds*1000);
}


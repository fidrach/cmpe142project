#include <iostream>
#include <pthread.h>	// pthread_t
#include "TA.h"

#define MAX_STUDENT_COUNT 50
using namespace std;

int askForStudentCount(int);

int main() {
	pthread_t TA;
	pthread_t Students[MAX_STUDENT_COUNT];
	int invalid[MAX_STUDENT_COUNT];

	int student_count = askForStudentCount(MAX_STUDENT_COUNT);

	// Create Student and TA threads
	// for (int i = 0; i < student_count; i++) {

	// }

	return 0;
}

int askForStudentCount(int limit) {
	int desired_count = 0;
	cout << "Enter Total Number of Students: ";
	cin >> desired_count;

	cout << "You asked for " << desired_count << " students!" << endl;
}

#ifndef TA_H_
#define TA_H_

#include <iostream>
#include <stdlib.h>
#include <pthread.h>

// OS-dependent includes
#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef linux
#include <unistd.h>
#endif

using namespace std;

class TA {
public:
	TA();
	void sleep();
	void check_for_student();
	void wake_up();
	void help(); // Should help for a random time
private:
	int seed;
	int max_sleep;
};

#endif /* TA_H_ */

#ifndef TA_H_
#define TA_H_

#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <pthread.h>

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

#ifndef STUDENT_H_
#define STUDENT_H_

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

class Student {
public:
	Student(int SID);
	void seek_help();
	void wake_TA(); //using semaphore
	void program();
	void wait();
private:
	int SID;
	
};

#endif

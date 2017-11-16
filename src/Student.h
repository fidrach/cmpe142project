#ifndef STUDENT_H_
#define STUDENT_H_

#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <pthread.h>

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

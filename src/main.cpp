#include <iostream>
#include <cstdlib>		// srand(), rand()
#include <pthread.h>	// pthread_t
#include <semaphore.h>
#include <signal.h>		// pthread_kill()
#include <time.h>  		// time()
#include <string.h>
// Cross-OS includes
#ifdef _WIN32
#include <windows.h>
#endif
#ifdef linux
#include <unistd.h>
#endif

#define MAX_STUDENT_COUNT 50
using namespace std;


struct RESOURCES{
	sem_t student_ready;
	sem_t access_rw_chairs;
	sem_t ta_ready;
	sem_t cout_access;
	sem_t access_rw_student_id;
	int chairs;
	int student_id;
} shared_resources_t;

void initialize_semaphores();
void *thread_ta(void *);
void *thread_student(void * id);
void program_or_help(int max_sleep=3);
void custom_cout(string s);
static void os_independent_sleep(int ms);

int main() {
	int n_students;
	int seed = time(NULL);
	srand(seed);

	cout << "The Lazy TA" << endl;

	cout << "Enter amount of students:" << endl;

	cin >> n_students;

	initialize_semaphores();

	pthread_t ta, students[n_students];

	// Spawn TA thread
	pthread_create(&ta, NULL, thread_ta, NULL);

	// Spawn Students thread
	int id[n_students];
	for(int i=0; i<n_students; i++) {
		id[i] = i+1;
		pthread_create(&students[i], NULL, thread_student, (void *)(id + i));
	}

	// Wait till all students are done
	for(int i=0; i<n_students; i++) {
		pthread_join(students[i], NULL);
	}

	custom_cout("TA has helped all students");

	pthread_kill(ta, 0);

	return 0;
}

void initialize_semaphores() {
	sem_init(&shared_resources_t.student_ready, 0, 0);
	sem_init(&shared_resources_t.access_rw_chairs, 0, 1);
	sem_init(&shared_resources_t.ta_ready, 0, 0);
	sem_init(&shared_resources_t.cout_access, 0, 1);
	sem_init(&shared_resources_t.access_rw_student_id, 0, 0);
	shared_resources_t.chairs = 4;
}

void *thread_ta(void *) {
	while(1) {
		sem_wait(&shared_resources_t.student_ready); // TA sleeps here
		sem_wait(&shared_resources_t.access_rw_chairs);

		shared_resources_t.chairs++;

		sem_post(&shared_resources_t.ta_ready);
		sem_post(&shared_resources_t.access_rw_chairs);

		// Get the student ID
		sem_wait(&shared_resources_t.access_rw_student_id);
		int student_id = shared_resources_t.student_id;

		custom_cout("TA is helping Student #" + to_string(student_id));
		// Help student for random period of time
		program_or_help();
		custom_cout("TA is done helping Student #" + to_string(student_id));

		custom_cout("TA is checking for students");
	}
}

void *thread_student(void* id) {
	int* i = (int*)id;
	while(1) {
		custom_cout("Student #" + to_string(*i) + " is programming");
		// Program for random period of time
		program_or_help();

		custom_cout("Student #" + to_string(*i) + " seeking for help");
		sem_wait(&shared_resources_t.access_rw_chairs);

		// If chairs available
		if (shared_resources_t.chairs > 0) {

			shared_resources_t.chairs--;

			custom_cout("Student #" + to_string(*i) + " waits for TA in chair");

			sem_post(&shared_resources_t.student_ready);

			sem_post(&shared_resources_t.access_rw_chairs);

			sem_wait(&shared_resources_t.ta_ready);
			custom_cout("Student #" + to_string(*i) + " goes into TA office");

			// Provide Student ID
			shared_resources_t.student_id = *i;
			sem_post(&shared_resources_t.access_rw_student_id);

			pthread_exit(NULL);
		}
		// Go home and program some more
		else {
			custom_cout("No chairs. Student #" + to_string(*i) + " will come back later");
			sem_post(&shared_resources_t.access_rw_chairs);
		}
	}
}

void program_or_help(int max_sleep) {
	int seconds = rand() % max_sleep + 1;
	os_independent_sleep(seconds*1000);
}


void custom_cout(string s) {
	sem_wait(&shared_resources_t.cout_access);
	cout << endl << s << endl;
	sem_post(&shared_resources_t.cout_access);
}

void os_independent_sleep(int ms) {
	#ifdef _WIN32
	Sleep(ms);
	#endif

	#ifdef linux
	usleep(1000 * ms);
	#endif
}

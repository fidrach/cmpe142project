
#include <iostream>
#include <cstdlib>		// srand(), rand()
#include <pthread.h>	// pthread_t...
#include <semaphore.h>
#include <signal.h>		// pthread_kill()...
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
	sem_t customer_ready;
	sem_t access_rw_chairs;
	sem_t ta_ready;
	int chairs;
	sem_t cout_ready;
} shared_resources_t;

void initialize_semaphores();
void *thread_ta(void *);
void *thread_student(void * id);
void program_or_help(int max_sleep=3);
static void os_independent_sleep(int ms);

int main() {
	int n_students;
	int seed = 25; // TODO: change to time.now during prod
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

	cout << "TA has helped all students..." << endl;
	pthread_kill(ta, 0);
	// pthread_join(ta, NULL); // TODO: find a way to make the TA close once all students have been helped

	return 0;
}

void initialize_semaphores() {
	sem_init(&shared_resources_t.customer_ready, 0, 0);
	sem_init(&shared_resources_t.access_rw_chairs, 0, 1);
	sem_init(&shared_resources_t.ta_ready, 0, 0);
	sem_init(&shared_resources_t.cout_ready, 0, 1);
	shared_resources_t.chairs = 4;
}

void *thread_ta(void *) {
	while(1) {
	        sem_wait(&shared_resources_t.cout_ready); // mutex wrapper start
		    cout <<  endl << "TA is sleeping" << endl;
		    sem_post(&shared_resources_t.cout_ready); // mutex wrapper end
		// Sleep
		sem_wait(&shared_resources_t.customer_ready); // i think the ta is already sleeping here so no need for an extra wait
		sem_wait(&shared_resources_t.access_rw_chairs);
		shared_resources_t.chairs++;
		program_or_help();                            // put the program_or_help in the ta thread instead of the student one
		sem_wait(&shared_resources_t.cout_ready);
		cout << endl << "TA helped student #" << endl; // feel like this should be here instead of the student thread
								// not quit sure how to get the correct variable
		sem_post(&shared_resources_t.cout_ready);
		sem_post(&shared_resources_t.ta_ready);
		sem_post(&shared_resources_t.access_rw_chairs);
		sem_wait(&shared_resources_t.cout_ready);
		cout << endl << "TA is checking for students" << endl;
		sem_post(&shared_resources_t.cout_ready);
	}
}

void *thread_student(void* id) {
	int* i = (int*)id;
	while(1) {
	    sem_wait(&shared_resources_t.cout_ready);
		cout << endl <<  "Student #" << *i << " is programming" << endl;
		sem_post(&shared_resources_t.cout_ready);
		program_or_help();
		
        sem_wait(&shared_resources_t.cout_ready);
		cout <<  endl << "Student #" << *i << " seeking for help" << endl;
		sem_post(&shared_resources_t.cout_ready);
		sem_wait(&shared_resources_t.access_rw_chairs);
		if (shared_resources_t.chairs > 0) {
			shared_resources_t.chairs--;
			sem_wait(&shared_resources_t.cout_ready);
			cout << endl <<  "Student #" << *i << " waits for TA in chair" << endl;
			sem_post(&shared_resources_t.cout_ready);
			sem_post(&shared_resources_t.customer_ready);
			sem_post(&shared_resources_t.access_rw_chairs);
			sem_wait(&shared_resources_t.cout_ready);
			cout << endl << "Student #" << *i << " wakes up TA" << endl;
			sem_post(&shared_resources_t.cout_ready);
			sem_wait(&shared_resources_t.ta_ready);
			
			pthread_exit(NULL);
		}
		else {
			sem_wait(&shared_resources_t.cout_ready);
			cout <<  endl << "No chairs. Student #" << *i << " will come back later" << endl;
			sem_post(&shared_resources_t.cout_ready);
			sem_post(&shared_resources_t.access_rw_chairs);
		}
	}
}

void program_or_help(int max_sleep) {
	int seconds = rand() % max_sleep + 1;
	os_independent_sleep(seconds*1000);
}

void os_independent_sleep(int ms) {
	#ifdef _WIN32
	Sleep(ms);
	#endif

	#ifdef linux
	usleep(1000 * ms);
	#endif
}

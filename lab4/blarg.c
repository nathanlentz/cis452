#include <stdio.h>
#include <pthread.h> 
#include <stdio.h> 
#include <errno.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h>
#include <signal.h>
#include <string.h>

int files_requested = 0;
int files_served = 0;

void* worker_bee (void* arg);
void sigHandler(int signal);

// bad practice!!!
int main(void) {

	srand(time(NULL));	
	int status;
	char buff[50];
	char* buff_array[100];
	int k = 0;

	signal(SIGINT, sigHandler);
	// will run until ^C
	while(1){

		// creates a buffer, asks for input, puts that into the buffer
		printf("requested file name: ");
		fgets (buff, 50, stdin);
		pthread_t bee;

		files_requested++;


		if ((status = pthread_create (&bee, NULL,  worker_bee, strdup(buff))) != 0) { 
	        fprintf (stderr, "thread create error %d: %s\n", status, strerror(status)); 
	        exit (1); 
	    }
 
	}

	return 0;
}


void* worker_bee (void* file_a){

	char *val_ptr = (char*) file_a;
	int test;
	// random number between 1 - 10
	if ((rand() % (10 + 1 - 1) + 1) <= 8){
		test = 1;
		sleep(1);
	} else {
		test = (rand() % (10 + 1 - 7) + 7);
		sleep(test);
	}

	printf("\nfile served: %s slept for: %d", val_ptr, test);

	fflush(stdout);
	files_served++;
	free(val_ptr);
	return NULL;
}

void sigHandler (int signal) {
	printf("\nTotal Files Requested: %d", files_requested);
	printf("\nTotal Files Requested: %d", files_served);
	exit(0);
}
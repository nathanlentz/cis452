#include <stdio.h>
#include <pthread.h> 
#include <stdio.h> 
#include <errno.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h>
#include <signal.h>
#include <string.h>

/************************************************************
* Lab 4 - Blocking Multi-Threaded Server
* @authors Nathan Lentz & Brandon Attala
* @date February 9th, 2017
*
* TODO: Add description
*************************************************************/

#define FILE_LEN 50
#define MAX_REQUESTS 50

/* Global Variables */
int filesRequested;
int filesServed; 

/* Prototypes */
void sigHandler(int signal);
void* worker(void* arg);


/* Main Function */

int main()
{
	// Seed random number generator
	srand(time(NULL));

	// TODO: Make this an array of char arrays
	char buffer[FILE_LEN];
	char* files[MAX_REQUESTS];
	int status;
	
	// Register signal handler 
	signal(SIGINT, sigHandler);

	printf("Connecting to server...");
	fflush(stdout);
	sleep(1);
	printf("Connected\n\n");

	// Dispatch thread 
	int i = 0;
	while(1){
		// Input string from user
		printf("Enter name of file: ");
		fgets(buffer, FILE_LEN, stdin);
		files[i] = strndup(buffer, FILE_LEN);

		// Spawn child thread and pass filename entered via user
		pthread_t workThread;
 		if ((status = pthread_create (&workThread, NULL,  worker, files[i]) != 0)) { 
	        fprintf(stderr, "thread create error %d: %s\n", status, strerror(status)); 
	        exit (1); 
    	}
		// Repeat!
		i++;
	}

}


/*************************************************************
* Signal Handler to handle SIGINT (^C) 
* Reports statistics from the threads
**************************************************************/

void sigHandler(int signal)
{
	// Do stuff
	if(signal == SIGINT){
		// report statistics
		printf("Total Files Requested: %d\n", filesRequested);
		printf("Total Files Served: %d\n", filesServed);
		exit(0);
	}
	exit(0);
}


/*************************************************************
* Work Thread Function
**************************************************************/
void* worker(void* arg)
{
	filesRequested++;
	// Dereference the filename for access	
 	char *fileRequest = (char*) arg;

	int sleepTime;

	// Sleep for certain amount of time
	// 80% - Sleep(1)	
 	if(rand() % 10 <= 5){
 		sleepTime = 1;
 		sleep(sleepTime);;
 	}

	// 20% - Sleep(7 - 10)
 	else {
 		sleepTime = rand() % 4 + 7;
 		sleep(sleepTime);
 	}

	// Wake up, print diagonstic message that includes the name of the file

	filesServed++;
	printf("Found file : %s\t Serve time: %i\n", fileRequest, sleepTime);

	return 0;
}
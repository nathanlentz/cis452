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

#define FILELEN 50

/* Global Variables */
int filesRequested;
int filesServed; 

/* Prototypes */
void sigHandler(int signal);
void* worker(void* arg);


/* Main Function */

int main()
{
	char buff[FILELEN];
	int status;
	// Seed random number generator
	srand(time(NULL));

	// Register signal handler 
	signal(SIGINT, sigHandler);

	printf("Connecting to server...");
	fflush(stdout);
	sleep(1);
	printf("Connected\n\n");

	// Dispatch thread 
	while(1){
		// Input string from user
		printf("Enter name of file: ");
		fgets(buff, FILELEN, stdin);

		// Spawn child thread and pass filename entered via user
		pthread_t workThread;
 		if ((status = pthread_create (&workThread, NULL,  worker, &buff) != 0)) { 
	        fprintf(stderr, "thread create error %d: %s\n", status, strerror(status)); 
	        exit (1); 
    	}
		// Repeat!
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
	// Dereference the filename for access	
 	char *fileRequest = (char*) arg;
	//printf("Worker sees: %s\n", file_request);
 	int randomNum = rand() % 100 + 1;
 	printf("Random number: %d", randomNum);
	// Sleep for certain amount of time

	// 80% - Sleep(1)
	// 20% - Sleep(7 - 10)
	// Wake up, print diagonstic message that includes the name of the file

	return NULL;
}
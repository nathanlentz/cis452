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
double avgTime;
pthread_mutex_t count_mutex;

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
	//char* files[MAX_REQUESTS];
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
		int bufferSize = strlen(buffer);
		if(bufferSize < 1){
			printf("\nFile length must be at least 1 char long: ");
			continue;
		}

		// remove \n from fgets
		buffer[bufferSize-1]='\0';
		fflush(stdout);

		// Strndup returns a pointer to a new string
		// So files is an array of pointers
		// if(i <= MAX_REQUESTS){
		// 	files[i] = strndup(buffer, FILE_LEN);	
		// }
		// else {
		// 	printf("At request limit!\n");
		// 	exit(0);
		// }
		

		// Spawn child thread and pass filename entered via user
		pthread_t workThread;
 		if ((status = pthread_create (&workThread, NULL,  worker, strndup(buffer,FILE_LEN)) != 0)) { 
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

		avgTime = avgTime/filesServed;
		// report statistics
		printf("\n\nReceived instructions to kill...");
		printf("\nTotal Files Requested: %d\n", filesRequested);
		printf("Total Files Served: %d\n\n", filesServed);
		printf("Avg File Access Time: %lf\n\n", avgTime);
		exit(0);
	}
	exit(0);
}


/*************************************************************
* Work Thread Function
**************************************************************/
void* worker(void* arg)
{
	// TODO: Implement mutex for file access time

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
	printf("\n\nFound file: %s\t Serve Time: %d\n", fileRequest, sleepTime);

	pthread_mutex_lock(&count_mutex);
		avgTime += sleepTime;
	pthread_mutex_unlock(&count_mutex);

	fflush(stdout);
	free(fileRequest);

	return NULL;
}
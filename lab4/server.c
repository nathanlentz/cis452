#include <stdio.h>


/************************************************************
* Lab 4 - Blocking Multi-Threaded Server
* @authors Nathan Lentz & Brandon Attala
* @date February 9th, 2017
*
* TODO: Add description
*************************************************************/

/* Global Variables */

/* Prototypes */
void sigHandler(int signal);
void worker(void* arg);


/* Main Function */

int main()
{
	// Register signal handler 
	signal(SIGINT, sigHandler);


	// Dispatch thread 
	while(1){
		// Input string from user

		// Spawn child thread and pass filename entered via user

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
	}
}


/*************************************************************
* Work Thread Function
**************************************************************/
void worker(void* arg)
{
	// Dereference the filename for access

	// Sleep for certain amount of time
	// 80% - Sleep(1)
	// 20% - Sleep(7 - 10)
	// Wake up, print diagonstic message that includes the name of the file,

	return NULL;
}
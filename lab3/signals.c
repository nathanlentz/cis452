/********************************************************
* Lab 3 Programming Assignment - Communicating Processes
* @authors: Nathan Lentz & Brandon Attala
* @date: February 2nd, 2-17
* 
* Practice with Signal Handlers and demonstrates 
* communication between a parent process and its child
********************************************************/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


/* Prototypes */

void signalHandler(int signal);
void closeHandler(int signal);

/* Global Variables */

pid_t pid;


/* Main Method */

int main()
{
	// Initialize random number generator
	srand(time(NULL));

	int status;

	// Fork parent process
	pid = fork();
	// if((pid = fork()) < 0){
	if(pid < 0){
		perror("Failed to fork\n");
		exit(1);
	}	

	// Child Instructions
	else if(pid == 0){
		printf("Spawned child PID#: %d\n", getpid());

		// Get our parent ID so we can send signals to it
		pid_t ppid = getppid();
		int randomNumber;
		int randomSignal;

		while(1){

			// Wait random amount of time (1-5 seconds)
			randomNumber = (rand() % 5) + 1;
			sleep(randomNumber);

			// Randomly send signal to parent
			randomSignal = rand() % 2;
			if(randomSignal == 0){
				kill(ppid,SIGUSR1);
				
			}
			else{
				kill(ppid,SIGUSR2);
			}
		}
	}
	// Parent Instructions
	else {
		// Register signal handler with user signals and ^C
		sleep(1);
		signal(SIGUSR1, signalHandler);
		signal(SIGUSR2, signalHandler);
		signal(SIGINT, closeHandler);

		printf("Waiting . . .");
		fflush(stdout);
		
		wait(&status);

	}
	return 0;
}

/*******************************************************
* Signal Handler generates outpu that is dependant on 
* the signal which was generated by user defined signals
* SIGUSR1 / SIGUSR2
********************************************************/

void signalHandler(int signal)
{
	
	if(signal == SIGUSR1){
		printf("\t\t Received SIGUSR1\n");
		printf("Waiting . . .");
		fflush(stdout);
	}

	else if(signal == SIGUSR2){
		printf("\t\t Received SIGUSR2\n");
		printf("Waiting . . .");
		fflush(stdout);
	}

	// Something went wrong
	else {
		printf("\t\t Uh oh! I wasn't expecting this signal, exiting.\n");
		exit(1);
	}
}

/*********************************************************
* Close Handler ensures to kill processes before exiting
* the program. We ensure that a SIGINT signal is registered
* with this handler by the parent. If the parent receives
* this signal, we check to ensure pid is positive, and then 
* issue a kill
* http://www.tutorialspoint.com/unix_system_calls/kill.htm
***********************************************************/

void closeHandler(int signal){
	if(pid > 0){
		printf("\t\tStupid kids, I'm ending you.\n");
		// Kill child process with SIGKILL
		//If pid is positive, then signal sig is sent to pid.
		kill(pid, SIGKILL);
		exit(0);
}
	}

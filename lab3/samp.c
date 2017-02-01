/*************************************************************
*	Lab 3 Programming Assignment
*	Sean Crowley
*	Vignesh Suresh
*
*	Description : This program communicates between a parent
*				  and a child with the use of signals
*************************************************************/

#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h>
#include <string.h>

void signalHandler(int signal);

int main(){
	//Stores the PID and the Parent PID
	pid_t pid, ppid;

	//An array filled with the signal types that will be sent
	int signalTypes[3];
	signalTypes[0] = SIGUSR1;
	signalTypes[1] = SIGUSR2;
	signalTypes[2] = SIGINT;

	//Creates a child and checks if fork is successful
	if ((pid = fork()) < 0) { 
		perror ("fork failed"); 
		exit (1); 

	//Child Process
	}else if (pid == 0) { 
		//Prints the childs PID
		printf("Child PID : %ld\n", (long) getpid()); 

		//Gets the parents PID
		ppid = getppid();

		//Sends random signals at a random time (0-5 secs)
		while(1){
			//Sleeps at random time
			sleep(rand() % 6);

			//Chooses a random signal to send (SIGUSR1 or SIGUSR2)
			int signal = signalTypes[rand() % 2];
		
			//Prints appropriate message based on signal
			if(signal == signalTypes[0])
				printf("\nChild : sending SIGUSR1\n");
			else
				printf("\nChild : sending SIGUSR2\n");

			//Sends the signal to the parent
			kill(ppid, signal);
		}

	//Parent process
	}else{
		//Prints the parents PID
		printf("Parent PID : %ld\n", (long) getpid());

		//Installs signal handlers
		signal(signalTypes[0], signalHandler);
		signal(signalTypes[1], signalHandler);
		signal(signalTypes[2], signalHandler);

		//Sleeps until a signal occurs
		while(1){
			pause();
		}
	}
	return 0;
}

//Manages the signals
void signalHandler(int signal){
	//Checks the signal type and deals with it appropriately 
	if (signal == SIGUSR1)
		printf("Parent : received SIGUSR1\n");
	if (signal == SIGUSR2)
		printf("Parent : received SIGUSR2\n");
	if (signal == SIGINT){
		printf("\nParent : received SIGINT");
		printf("\nClosing down the program!\n");
		exit (0);
	}
}
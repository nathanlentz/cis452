/*********************************************
* Lab 2 Programming Assignment - Simple Shell
* @authors: Nathan Lentz & Brandon Attala
* @date: Jan 23rd, 2017
* 
* Simple shell 
**********************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/* Constants */
#define LINESIZE 256

/* Prototypes */
void display_console();
char** read_command();


int main(int argc, char* argv[]) 
{  
	pid_t pid;
	int status;
	char** command;

	// Enter loop for shell
	while(1){

		//command = read_command();

	    if(command != NULL && !strcmp(command[0],"quit")){
      		break;
    	}
	}
cd 
	return 0;
}

// Display console message to user
void display_console()
{
	printf("nlba > ");
}

// Parse command in arguments sent to child process
char** read_command()
{

}	
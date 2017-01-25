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

		// Call read command and parse user input 
		//command = read_command();

		// Exit if user types quit
	    if(!strcmp(command[0],"quit") && command != NULL){
      		break;
    	}

    	pid = fork();

    	if(pid < 0){
    		perror("Fork Failed");
    		exit(1);
    	}
    	else if(pid == 0){ 
    		// We are the child, do stuff

    	}
    	else if(pid > 0){
    		// We are the parent, do stuff
    	}
    		

    	
	}
	// Return memory used for command as program exits
	free(command);
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
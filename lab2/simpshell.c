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
	pid_t pid, child
	int status;
	char** command;

	// Enter loop for shell
	while(1){

		// Call read command and parse user input 
		command = read_command();

		// Exit if user types quit
	    if(!strcmp(command[0],"quit") && command != NULL){
      		break;
    	}

    	pid = fork();

    	if(pid < 0){
    		perror("Fork Failed");
    		exit(1);
    	}
    	// The Child
    	else if(pid == 0){ 
    		// We are the child, do stuff 
            // TODO: Implement execvp()


    	}
    	// The Parent. Wait for child to execute and get data for usage
    	// waitpid -> https://linux.die.net/man/2/waitpid
    	else if(pid > 0){
    		// We are the parent, do stuff
    		
    		// Wait for 
    		waitpid(-1, &status, 0);

    		// TODO: Get data for usage
            

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
	char buf[LINESIZE];	
    char* word;

    // An array of pointers 
	char** command;

    while(1){
        display_console();

        // Get user input
        fgets(buf, LINESIZE, stdin)

        // Was a command entered?
        if(strlen(buf)==1){
            continue;
        }

        // TODO: Get rid of '\0' at end 

        // TODO: Check if command was longer than line length - 2

        break;
    }

    // We now have a command. Allocate memory
    command = malloc(sizeof(char*));
    word = strtok(buf, " ");

    // Iterate thorugh arguments, reallocate space for pointer array
    // allocate space for pointer to string in the pointer array, copy
    // the string to the pointer array
    int i = 0;
    while(){
        // Do stuff above
        i++
    }

    free(word);
}	
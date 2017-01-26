/*********************************************
* Lab 2 Programming Assignment - Simple Shell
* @authors: Nathan Lentz & Brandon Attala
* @date: Jan 23rd, 2017
* 
* Simple shell 
**********************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

/* Constants */
#define LINELEN 256

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
		command = read_command();

		// Exit if user types quit
	    if(!strcmp(command[0],"quit") && command != NULL){
            printf("Goodbye!\n");
      		break;
    	}

    	pid = fork();

    	if(pid < 0){
    		perror("Fork Failed");
    		exit(1);
    	}
    	// The Child
    	else if(pid == 0){ 
    		// We are the child, run execvp
            if(execvp(command[0], &command[0]) < 0){
                perror("Failed to execute");
                exit(1);
            }
    	}
    	// The Parent. Wait for child to execute and get data for usage
    	// waitpid -> https://linux.die.net/man/2/waitpid
    	else if(pid > 0){	
    		// Wait for child
    		waitpid(-1, &status, 0);
            
            struct rusage usage;
            if(getrusage(RUSAGE_CHILDREN, &usage) < 0){
                perror("Unable to get usage");
                exit(1);
            }
            else{
                //stackoverflow.com/questions/1469495/unix-programming-struct-timeval-how-to-print-it-c-programming
                // tv_usec is the number of microseconds
                printf("User CPU Time: %ld.%06ld\n", usage.ru_utime.tv_sec, usage.ru_stime.tv_usec);
                printf("Involuntary Context Switches: %lu\n", usage.ru_nivcsw);
            }
    	}
	}
	// Return memory used for command as program exits
	free(command);
	return 0;
}

// Parse command in arguments sent to child process
char** read_command()
{
	char buff[LINELEN];	
    char* token;

    // An array of pointers 
	char** command;

    while(1){
        display_console();

        // Get user input
        fgets(buff, LINELEN, stdin);
        int buffSize = strlen(buff);

        // Was a command entered?
        if(buffSize == 1){
            continue;
        }

        // Remove \n from fgets 
        buff[buffSize-1]='\0'; 

        // TODO: Check if command was longer than expected
        break;
    }

    // We now have a command. Allocate memory
    command = malloc(sizeof(char*));
    token = strtok(buff," ");

    /* Create a vector of pointers to arguments for use in execvp */

    // Iterate thorugh arguments, reallocate space for pointer array
    // allocate space for pointer to string in the pointer array, copy
    // the string to the pointer array
    int i = 0;

    while(1){
        command = realloc(command,sizeof(char*) * (i+1));
        command[i] = malloc((strlen(token)+1) * sizeof(char));
        strcpy(command[i], token);
        i++;
        // If nex is NULL, we've reached the end
        if((token = strtok(NULL," ")) == NULL) {
            break;
        }
      }

    // execvp needs null terminate to argument list or a bad adress will be given
    command[i] = NULL;

    free(token);
    return command;
}	

// Display console message to user
void display_console()
{
    printf("nlba type 'quit' to exit > ");
}

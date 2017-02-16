#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE 1024

int main(void)
{
	// ****************************************************
	// Variable declaration
	// ****************************************************

	key_t key;
	int shmid;
	int accepting_input = 1;
	char *shm, *s, c;
	char *user_input = malloc(sizeof(char)*BUFSIZ);

	// ****************************************************
	// Creating the shared memory segment
	// ****************************************************

	// The key is set equal to user ID & the shared memory segment is created
	key = getuid();	
	shmid = shmget(key, SIZE, IPC_CREAT | 0666);					

	// An error occurs if the segment isn't created
	if (shmid < 0) {
		perror("shmget failed: The shared memory segment wasn't created");
		exit(EXIT_FAILURE);
	}
	
	// The shared memory segment is attached to the first available data space
	shm = shmat(shmid, NULL, 0);

	// An error occurs if the segment isn't attached
	if (shm == (char *) -1) {
		perror("shmat failed: segment wasn't attached to data space");
		exit(EXIT_FAILURE);
	}

	// ****************************************************
	// User enters input in an infinite loop
	// ****************************************************

	while (accepting_input) {

		// Prompts the user for input & records it
		printf("Enter a string or 'exit' : ");
		fgets(user_input, BUFSIZ, stdin);

		// If the input is 'exit' the loop is terminated such that
		// the shared memory segment can be detached and the IPC can be closed
		if (strncmp(user_input, "exit", 4) == 0) { 
			accepting_input = 0;
		}

		// The input is recorded into the shared memory segment
		// A dollar sign '$' is added to the end of the input string,
		// so that reader.c knows when the input ends
		// ($ is not alpha numeric, so it can’t harm the program functionality)
		memcpy(shm, user_input, strlen(user_input));
		s = shm; 
		s += strlen(user_input);						 
		*s = '$';

	
		// reader.c signals that it has finished reading the input string
		// by inserting an '@' symbol to the memory address shm is pointing to
		// (the beginning of the shared memory string).
		// So now writer.c is waiting for that signal so that it can restart the loop.
		// ('@' is not alpha numeric, so it can’t harm the program functionality)
		while (*shm != '@')
		{									 
			sleep(1); 
		}  
	}

	// ****************************************************
	// Shared memory communication has to close
	// ****************************************************

	// An error occurs if the segment isn't detached
	if (shmdt(shm) == -1) { 
		perror("shmdt failed: segment wasn't dettached from data space");	
                exit(EXIT_FAILURE);
	}

	
	// An error occurs if the IPC isn't closed
	if (shmctl(shmid, IPC_RMID, 0) == -1) { 
		perror("shmctl failed: ipc didn't close");				
		exit(EXIT_FAILURE);
	}
}

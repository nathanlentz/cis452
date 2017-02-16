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
	// Variables declaration
	// ****************************************************

	key_t key;
	int shmid;
	int cnt;
	int infinite_loop = 1;
	char *shm, *s;
	char line[BUFSIZ];

	// ****************************************************
	// Setup of shared memory
	// ****************************************************

	// get the same key as the one created by writer.c & locate the shared memory segment
	key = getuid();	
	shmid = shmget(key, SIZE, 0666);

	// An error occurs if the segment is not located
	if (shmid < 0) {
		perror("shmget failed: The shared memory segment wasn't created");
		exit(EXIT_FAILURE);
	}

	
	// The memory segment is attached to the data space
	shm = shmat(shmid, NULL, 0);

	// An error occurs if the segment is not attached
	if (shm == (char *) -1) {
		perror("shmat failed: The segment wasn't attached to data space");
		exit(EXIT_FAILURE);
	}


	// ****************************************************
	// User input is received and written in a loop
	// ****************************************************

	while (infinite_loop) {

		// Waiting for user input
		if (*shm != (int) NULL) {

			// *shm begins with an '@' while there is no new input. 
			// Thus, the program has to wait for a new input
			// Digits counter is set to zero and the line input string
			// is emptied for being able to receive new input values
			if (*shm != '@') {

				cnt = 0;
				memset(line, 0, sizeof(line));

				// The string received through shared memory is passed into the line array
				for (s = shm; *s != '$'; s++) {
					line[cnt] = *s;					
					cnt++;
				}

				
				// The input read from shared memory is printed to the console.
				printf("%s", line);

				// If the input string is "exit" the loop is interrupted
				// such that the shared memory segment can be dettached
				if (strncmp(line, "exit", 4) == 0) {
					infinite_loop = 0;
				}

				
				// The program signalizes it has finished reading the input string
				// by inserting an '@' symbol to the memory address shm is pointing to
				// (the beginning of the shared memory string)
				// Thus, writer.c can ask the user for a new input
				*shm = '@'; 
                        } 
                }
        }

	// ****************************************************
	// Shared memory has to be detached from data space
	// ****************************************************

	// An error is occurs if the segment isn't detached
	if (shmdt(shm) == -1) {
		perror("shmdt failed: The segment wasn't detached from data space");
		exit(EXIT_FAILURE);
	}
}

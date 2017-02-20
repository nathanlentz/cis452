#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <sys/ipc.h> 
#include <sys/shm.h>
#include <sys/stat.h>

#define SIZE 16

/*************************************************************
* CIS 452 - Lab 6 Programming Assignment
* @authors Nathan Lentz & Brandon Attala
* @date February 23 2016
* Shared Memory Synchronization 
* Demonstrate the use of semaphores to control access to 
* shared memory 
*************************************************************/

int main(int argc, char* argv[])
{ 
   int status; 
   long int i, loop, temp, *shmPtr; 
   int shmId, semId;
   pid_t pid;

   // Set our loop value from command line argument
   loop = atoi(argv[1]);

   if ((shmId = shmget (IPC_PRIVATE, SIZE, IPC_CREAT|S_IRUSR|S_IWUSR)) < 0) {
      perror ("i can't get no..\n"); 
      exit (1); 
   } 
   if ((shmPtr = shmat (shmId, 0, 0)) == (void*) -1) { 
      perror ("can't attach\n"); 
      exit (1); 
   }

   shmPtr[0] = 0; 
   shmPtr[1] = 1;

   // TODO: Create semaphore
   //semget()

   // TODO: Initialize semaphore
   //semctl()


   if (!(pid = fork())) { 
      for (i=0; i<loop; i++) { 
         // TODO semaphore wait
         // semop()

         // swap the contents of shmPtr[0] and shmPtr[1]
         temp = shmPtr[0];
         shmPtr[0] = shmPtr[1];
         shmPtr[1] = temp;         
         // Signal semaphore signal
         // semop()

      } 
      if (shmdt (shmPtr) < 0) { 
         perror ("just can't let go\n"); 
         exit (1); 
      } 
      exit(0); 
   } 
   else 
      for (i=0; i<loop; i++) { 
         // swap the contents of shmPtr[1] and shmPtr[0] 
         // TODO semaphore wait
         // semop()
         temp = shmPtr[1];
         shmPtr[1] = shmPtr[0];
         shmPtr[0] = temp;
         // TODO semaphore signal
         // semop()
      }

   wait (&status); 
   printf ("values: %li\t%li\n", shmPtr[0], shmPtr[1]);

   // TODO remove our semaphpre
   // semctl()

   if (shmdt (shmPtr) < 0) { 
      perror ("just can't let go\n"); 
      exit (1); 
   } 
   if (shmctl (shmId, IPC_RMID, 0) < 0) { 
      perror ("can't deallocate\n"); 
      exit(1); 
   }

   return 0; 
}
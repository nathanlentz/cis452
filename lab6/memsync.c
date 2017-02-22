#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <sys/ipc.h> 
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/sem.h>

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

   // Structures for wait and signal 
   struct sembuf wait;
   struct sembuf signal;

   // Wait Struct
   wait.sem_num = 0;          /* semaphore number */ 
   wait.sem_op = -1;          /* semaphore operation */
   wait.sem_flg = SEM_UNDO;   /* operation flags */

   /* SEM_UNDO will automatically be undone when process terminates */

   // Signal Struct
   signal.sem_num = 0;
   signal.sem_op = 1;
   signal.sem_flg = SEM_UNDO;

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

   // Create semaphore 
   // http://www.tldp.org/LDP/lpg/node51.html
   semId = semget(IPC_PRIVATE, 1, IPC_CREAT | 0660);
   printf("Semaphore created!\n");

   // Initialize semaphore
   semctl(semId, 0, SETVAL, 1);


   if (!(pid = fork())) { 
      for (i=0; i<loop; i++) { 
         // TODO semaphore wait
         semop(semId, &wait, 1);

         // swap the contents of shmPtr[0] and shmPtr[1]
         temp = shmPtr[0];
         shmPtr[0] = shmPtr[1];
         shmPtr[1] = temp;         
         // Signal semaphore signal
         semop(semId, &signal, 1);

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
         semop(semId, &wait, 1);

         temp = shmPtr[1];
         shmPtr[1] = shmPtr[0];
         shmPtr[0] = temp;
         // TODO semaphore signal
         semop(semId, &signal, 1);
      }

   waitpid(pid, &status, 0); 

   printf ("values: %li\t%li\n", shmPtr[0], shmPtr[1]);

   // Remove semaphore
   semctl(semId, 0, IPC_RMID);

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
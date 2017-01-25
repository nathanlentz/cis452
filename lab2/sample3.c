#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int main() 
{ 

    // use these variables

    pid_t pid;
    int status;

    if ((pid = fork()) < 0) { 
        perror("fork failure"); 
        exit(1); 
    } 
    else if (pid == 0) { 
        printf("I am child PID %ld\n", (long) getpid()); 
        /* insert an appropriate form of the exit() function here */
        exit(0);

    } 
    else { 
        /* insert an appropriate form of the wait() system call here */
        waitpid(-1, &status, 0);
        struct rusage usage;
        if(getrusage(RUSAGE_CHILDREN, &usage) < 0){
            perror("Unable to get usage");
            exit(1);
        }
        else{
            printf("User CPU Time: %ld.%06ld\n", usage.ru_utime.tv_sec, usage.ru_stime.tv_sec);
            printf("Involuntary Context Switches: %lu\n", usage.ru_nivcsw);
        }
        printf("I'm done");

    } 
    return 0; 
}
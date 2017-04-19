/**************************************************
* Lab 13 - Mini Programming Assignment 
* @authors Nathan Lentz & Brandon Attala
* @date 4.20.17
* 
* This program is a custom implementation of 'ln'
* which can be used to create both hard and soft 
* links to files in a linux file system
***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char * argv[]){
  char * filePath;
  char * linkPath;
	int s = 0;
    
	if (argc < 3) {
    	printf("Not enough arguments. Please include file name and link name.\n");
    exit(EXIT_FAILURE);
	}
    
	if (argc == 4) {
     if (strchr(argv[3], 's') != NULL)
            	s = 1;
     else{
      	printf("Flag has no meaning here: %s\n", argv[3]);
      	exit(EXIT_FAILURE);
     }
	}
    
	// Path of existing file
	filePath = argv[1];
  // Name of link to be made
	linkPath = argv[2];
    
  // If there is no -s flag, create a hard link
	if (s == 0){
     link(filePath, linkPath);
     if (errno != 0){
      	perror("Error: ");
      	exit(EXIT_FAILURE);
     }
	}

  // If there was a -s flag, create a soft link
	else{
     symlink(filePath, linkPath); 
     if (errno != 0){
      	perror("Error: ");
      	exit(EXIT_FAILURE);
     }
	}

	return 0;
}

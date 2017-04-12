#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h> 
#include <dirent.h> 
#include <errno.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

/****************************************************
* Lab 12 Programming Assignment - ls implementation
* @authors Nathan Lentz & Brandon Attala
* @date 4/13/2017
* 
* This program is an implementation of the 'ls' command
* which uses stat to gather info on a file and prints
* info similarly to 'ls' and sorts alphabetically
* Can support '-l' and '-i' flags
*****************************************************/

#define MAX_FILENAME_SIZE	256

/* Properties */
char * dirName;
DIR * dirPtr;
struct dirent * entryPtr;
struct stat statBuf;

char* dateFormatting[7];
char* dateChar;
// Flags used for outputting
int lFlag = 0;
int iFlag = 0;
int dFlag = 0;
int totalFiles;


/* Prototypes */


/* Main Entry to Program */
int main(int argc, char* argv[])
{
	int i;
	// Check if arguments are passed and last isn't a dir
	if(argc > 1 && stat(argv[argc-1], &statBuf) < 0){
		dirName = ".";

		// Get flags from arguments
		int i;
		for(i = 0; i <= argc-1; i++){
			char* tmp = argv[i];
			// Use strchr to locate character in string
			if(strchr(tmp, 'l') != NULL){
				lFlag = 1;
			}
			if(strchr(tmp, 'i') != NULL){
				iFlag = 1;
			}
			if(strchr(tmp, 'd') != NULL){
				dFlag = 1;
			}
		}
	}

	// If no arguments are passed, just ls cd
	else if (argc == 1){
		dirName = ".";
	}

	// If > 1 arguments passes w/ a directory path
	else {
		// Get directory name 
		dirName = argv[argc-1];

		// Change cd to current
		chdir(dirName);
		dirName = ".";

		// Get flags
	
		for(i = 0; i <= argc-1; i++){
			char* tmp = argv[i];
			// Use strchr to locate character in string
			if(strchr(tmp, 'l') != NULL){
				lFlag = 1;
			}
			if(strchr(tmp, 'i') != NULL){
				iFlag = 1;
			}
			if(strchr(tmp, 'd') != NULL){
				dFlag = 1;
			}
		
		}
	}

	dirPtr = opendir(dirName);

	// Grab total number of files from directory
	while((entryPtr = readdir(dirPtr))){
		totalFiles++;
	}

	char* files[totalFiles];
	int currentDirIndex = 0;

	// Point stream to first entry in directory
	dirPtr = opendir(dirName);

	// Loop through files in directory 
	while((entryPtr = readdir(dirPtr))){
		// Load file name into array 
		files[currentDirIndex] = entryPtr->d_name;
		currentDirIndex++;
	}

	//TODO Sort all files via name
	//qsort(files, currentDirIndex, sizeof(char*), &)

	// If '-l' sum blocks used by files
	if(lFlag == 1){
		int blockSum = 0;
		int size;
	
		for(i = 0; i < totalFiles; i++){
			// Get file info
			stat(files[i], &statBuf);
			if(files[i][0] == '.'){
				continue;
			}
			size = statBuf.st_size;
			blockSum += size/4096;
			if(size%4096 != 0){
				blockSum++;
			}
		}
		printf("total %d\n", blockSum*4);
	}

	
	for(i = 0; i < totalFiles; i++){
		stat(files[i], &statBuf);

		if(strcmp(files[i], "..") == 0){
			// don't print current directory 
			continue;
		}

		// If file is not a directory and directories are only being printed
		if(dFlag == 1 && S_ISDIR(statBuf.st_mode) == 0){
			continue;
		}

		// If file is a directory and directories are not printing
		else if(dFlag == 0 && files[i][0] == '.'){
			continue;
		}

		// Print info for -l 
		if(lFlag == 1){
	        printf("%c", (S_ISDIR(statBuf.st_mode))? 'd': '-'); //if dir
	        //printf("%s ", format_perms(statBuf.st_mode)); //formatted permissions
	        printf("%zu ", statBuf.st_nlink); //num of links
	        printf("%s ", getpwuid(statBuf.st_uid)->pw_name); //user name
	        printf("%s ", getgrgid(statBuf.st_gid)->gr_name); //group name
	        printf("%zu ", statBuf.st_size); //file size
          	//printf("%s", statBuf.st_atime);
         	// format_date(ctime(&(statBuf.st_atime))); //formatted time
         	// printf("%s ", formatted);
		}

		// Print inode for -i flag
		if(iFlag == 1){
			printf("%zu ", statBuf.st_ino);
		}

		// Print file name
		printf("%s  ", files[i]);
		//printf("\x1b[0m");

		if (lFlag == 1){
			printf("\n");
		}
	}

	if(lFlag == 0){
		printf("\n");
	}

	return 0;
}


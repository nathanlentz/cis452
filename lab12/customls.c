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
#include <time.h>

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

char * dateChars[7];
char * dateChar;
char formattedDate[64];
// Flags used for outputting
int lFlag = 0;
int iFlag = 0;
int dFlag = 0;
int totalFiles;


/* Prototypes */
void formatAndPrintDate(char * date);
const char * formatPermissions(int permission);


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
	//qsort(files, currentDirIndex, sizeof(char*), &functionnameforsort)

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

		// Print inode for -i flag
		if(iFlag == 1){
			printf("%zu ", statBuf.st_ino);
		}

		// Print info for -l 
		if(lFlag == 1){
	        printf("%c", (S_ISDIR(statBuf.st_mode))? 'd': '-'); //if dir
	        // Formatted permissions
	        // Octal formatting obtained from stack overflow: 
	        // http://stackoverflow.com/questions/10323060/printing-file-permissions-like-ls-l-using-stat2-in-c

            printf( (statBuf.st_mode & S_IRUSR) ? "r" : "-");
		    printf( (statBuf.st_mode & S_IWUSR) ? "w" : "-");
		    printf( (statBuf.st_mode & S_IXUSR) ? "x" : "-");
		    printf( (statBuf.st_mode & S_IRGRP) ? "r" : "-");
		    printf( (statBuf.st_mode & S_IWGRP) ? "w" : "-");
		    printf( (statBuf.st_mode & S_IXGRP) ? "x" : "-");
		    printf( (statBuf.st_mode & S_IROTH) ? "r" : "-");
		    printf( (statBuf.st_mode & S_IWOTH) ? "w" : "-");
		    printf( (statBuf.st_mode & S_IXOTH) ? "x" : "-");
			// Number of links	        
	        printf(" %*zu ", 2, statBuf.st_nlink);
	        // Current Username
	        printf("%s ", getpwuid(statBuf.st_uid)->pw_name);
	        // Group Name
	        printf("%s ", getgrgid(statBuf.st_gid)->gr_name);
	        // File Size
	        printf("%6zu ", statBuf.st_size);
         	
         	// Print Formatted time
         	formatAndPrintDate(ctime(&(statBuf.st_mtime))); 
		}


		// Print file name
		printf("%s  ", files[i]);

		if (lFlag == 1){
			printf("\n");
		}
	}

	if(lFlag == 0){
		printf("\n");
	}

	return 0;
}

/***************************************************
* Takes a pointer to a date in statBuf. Removes
* day of week + seconds to make date look similar
* to the -l flag
* ctime returns format: Mon Aug 13 08:23:14 2012
****************************************************/
void formatAndPrintDate(char* date)
{
	int i = 0;
	int tokens = 0;
	dateChar = strtok(date, " :");
	dateChars[i] = dateChar;
	tokens++;
	i = 0;

	while(dateChar != NULL){
		i++;
		dateChar = strtok(NULL, " :");
		dateChars[i] = dateChar;
		tokens++;
	}

	printf("%*s", 3, dateChars[1]);
	printf(" %*s", 2, dateChars[2]);
	printf(" %*s", 2, dateChars[3]);
	printf(":%*s ",2, dateChars[4]);

	return;
}


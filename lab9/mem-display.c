#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <link.h>

/***********************************************
* Lab 9 - Short program used to help display
* Locations in Program Memory various types of 
* data is stored
*
* @authors Nathan Lentz & Brandon Attala
* @date March 23rd
***********************************************/


// Uninitialized globals
int a,b,c;
// Initialized globals
int x = 0, y = 1, z = 2;


int main (int argc, char *argv[])
{
	// Some local variables
	int i = 0, j = 1, k = 2;

	printf("Location of uninitialized global a: %p\n", &a);
	printf("Location of uninitialized global b: %p\n", &b);
	printf("Location of uninitialized global c: %p\n", &c);
	printf("Location of initialized global x: %p\n", &x);
	printf("Location of initialized global y: %p\n", &y);
	printf("Location of initialized global z: %p\n", &z);
	printf("Location of initialized local i: %p\n", &i);
	printf("Location of initialized local j: %p\n", &j);
	printf("Location of initialized local k: %p\n", &k);
	printf("Environment Variable argc %p\n", &argc);
	printf("Environment Variable argv %p\n", &argv);
	
	void * l = malloc(4);
	void * m = malloc(4);
	void * n = malloc(4);
	printf("Dynamic Location l: %p\n", l);
	printf("Dynamic Location m: %p\n", m);
	printf("Dynamic Location n: %p\n", n);
	free(l);
	free(m);
	free(n);

	//dl_iterate_phdr()




	return 0;

}
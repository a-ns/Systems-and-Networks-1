#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define BIGNUM 600 //on collatz wiki, for 100 million numbers, there was
		   //hardly anything that went over 550, and i doubt we'll
		   //be running 100 million numbers with out program
void initialize(int *, int *, int, char *[]);
int histogram[BIGNUM];

int main(int argc, char *argv[]){
	int thread_count,
	    collatz_count;
	initialize(&thread_count, &collatz_count, argc, argv);		
	return 0;
}

void initialize(int * thread_count, int *collatz_count, int argc, char *argv[]){
	if (argc < 3){
		fprintf(stderr, "Improper amount of arguments. Exiting.\n");
		exit(0);
	}
	*collatz_count = atoi(argv[1]);
	*thread_count = atoi(argv[2]);
	if (*collatz_count == 0 || *thread_count == 0){
		fprintf(stderr, "Error on arguments. Exiting.\n");
		exit(0);
	}
	int i;
	for (i = 0; i < BIGNUM; ++i) histogram[i] = 0;
	
	return;	
}

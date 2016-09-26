#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define BIGNUM 600 //on collatz wiki, for 100 million numbers, there was
		   //hardly anything that went over 550, and i doubt we'll
		   //be running 100 million numbers with out program
void initialize(int *, int, char *[]);
void * collatz(void *);
int compute_stopping_time(int);
int HISTOGRAM[BIGNUM];
int COUNTER = 2;
int COLLATZ_UPPER;

int main(int argc, char *argv[]){
	int thread_count;
	   
	initialize(&thread_count, argc, argv);		
	pthread_t threads[thread_count];
	int i;
	for (i = 0; i < thread_count; i++){
		if(pthread_create(&threads[i], NULL, collatz, NULL) != 0) {
			fprintf(stderr, "Error creating thread. Exiting.\n");
			exit(0);
		}
	}
	//generate_csv();
	
	//join threads
	for (i = 0; i < thread_count; i++){
		if(pthread_join(threads[i], NULL) != 0) {
			fprintf(stderr, "Error joining thread. Exiting.\n");
			exit(0);
		}
	}
	for (i = 0; i < BIGNUM; i++){
		printf("ST [%i] : %i\n", i, HISTOGRAM[i]);
	} 
	return 0;
}

void *collatz(void *param){
	while(COUNTER < COLLATZ_UPPER){
	//	fprintf(stderr, "Thread : %u, COUNTER : %i\n",(unsigned int) pthread_self(), COUNTER);	
		int stopping_time = compute_stopping_time(COUNTER++);
		HISTOGRAM[stopping_time]++;
	}
	return NULL; 
}

int compute_stopping_time(int num){
	return 0;
}

void initialize(int * thread_count, int argc, char *argv[]){
	if (argc < 3){
		fprintf(stderr, "Improper amount of arguments. Exiting.\n");
		exit(0);
	}
	COLLATZ_UPPER = atoi(argv[1]);
	*thread_count = atoi(argv[2]);
	if (COLLATZ_UPPER == 0 || *thread_count == 0){
		fprintf(stderr, "Error on arguments. Exiting.\n");
		exit(0);
	}
	int i;
	for (i = 0; i < BIGNUM; ++i) HISTOGRAM[i] = 0;
	
	return;	
}

/* A Simple multithreaded program that computes collatz stopping times.
 * The user enters an upper bound and then the number of threads to run.
 * @info COP 4634
 * @author Alex Lindemann, Nathaniel Moore
 * @date 10/2/2016
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //for threading
#include <time.h>   // for clock
#define BIGNUM 1000 //on collatz wiki, for 100 million numbers, there was
		    //hardly anything that went over 550, and i doubt we'll
		    //be running 100 million numbers with our program
#define BILLION 1000000000L
/* Joins N number of threads specified by user.
 * @Param pthread_t *: array of pthreads, int: number of threads to join
 */
void join_threads(pthread_t *, int);

/* Spawns N number of threads specified by user.
 * @Param pthread_t *: array of pthreads, int: number of threads to make
 */
void spawn_threads(pthread_t *, int);

/* Initializes setup data.
 * @Param int *: thread count, int: argc, char **: argv
 */
void initialize(int *, int, char *[]);

/* Thread function. Calls compute stopping time
 * @Param void *: to make compiler happy
 */
void * collatz(void *);

/* Computes the stopping time for the passed in number.
 * @Param unsigned int: since we're only working with positive numbers,
 * we don't need the negative spectrum of int type. unsigned ints also allow
 * for when stopping time input becomes huge.
 */
int compute_stopping_time(unsigned int);

/* Prints the histogram to stdout in comma separated values. Each histogram
 * entry is on a new line
 */
void generate_csv();

int HISTOGRAM[BIGNUM];
int COUNTER = 2;
int COLLATZ_UPPER;



int main(int argc, char *argv[]){
	int thread_count;
	struct timespec start;
	clock_gettime(CLOCK_REALTIME, &start);	
	initialize(&thread_count, argc, argv);		
	pthread_t threads[thread_count];
	spawn_threads(threads, thread_count);
	join_threads(threads, thread_count);

	struct timespec end;
	clock_gettime(CLOCK_REALTIME, &end);
	generate_csv();
	double real_time = (end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec)/(double)BILLION;
	fprintf(stderr, "%i,%i,%lf\n",COLLATZ_UPPER, thread_count, real_time); 
	return 0;
}

void spawn_threads(pthread_t *threads, int thread_count){
	int i;
	for (i = 0; i < thread_count; i++){
		if(pthread_create(&threads[i], NULL, collatz, NULL) != 0) {
			fprintf(stderr, "Error creating thread. Exiting.\n");
			exit(0);
		}
	}
}

void generate_csv(){
	int i;
	for (i = 1; i < BIGNUM; i++)
		printf("%i,%i\n", i, HISTOGRAM[i]);
	return; 
}
void join_threads(pthread_t *threads, int thread_count){
	int i;
	for (i = 0; i < thread_count; i++){
		if(pthread_join(threads[i], NULL) != 0) {
			fprintf(stderr, "Error joining thread. Exiting.\n");
			exit(0);
		}
	}
}
void *collatz(void *param){
	while(COUNTER < COLLATZ_UPPER){
		int counter = COUNTER;
		COUNTER++;
		int stopping_time = compute_stopping_time((unsigned int) counter);
		HISTOGRAM[stopping_time]++;
	}
	pthread_exit(NULL);
	return NULL; 
}

int compute_stopping_time(unsigned int num){
	int ans = 0;
	if (num == 1) return 1;
	if (num % 2 == 0)
		ans = 1 + compute_stopping_time (num/2);
	else
		ans = 1 + compute_stopping_time ((3*num)+1);
	return ans;	
}

void initialize(int * thread_count, int argc, char *argv[]){
	if (argc < 3){
		fprintf(stderr, "Improper amount of arguments. Exiting.\n");
		exit(0);
	}
	COLLATZ_UPPER =atoi(argv[1]);
	*thread_count = atoi(argv[2]);
	if (COLLATZ_UPPER == 0 || *thread_count == 0){
		fprintf(stderr, "Error on arguments. Exiting.\n");
		exit(0);
	}
	int i;
	for (i = 0; i < BIGNUM; ++i){
		HISTOGRAM[i] = 0;
	}
	return;	
}

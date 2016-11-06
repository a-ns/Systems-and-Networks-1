#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ROW 20480
#define COL 4096
#define BILLION 1000000000L

char MATRIX[ROW][COL];

void doExperiments();
void write_one_row (int, int);
void write_one_col (int, int);
void print_row (int);
void print_col (int);
void printMatrixRow();
void printMatrixCol();
void writeMatrixRow();
void writeMatrixCol();
typedef void (*MatrixFuncPtr)();
int main (int argc, char*argv[]){

	doExperiments();
	
	return 0;
}

void doExperiments () {
	struct timespec start[4];
	struct timespec end[4];
	MatrixFuncPtr fptr[4] = {&writeMatrixRow, &writeMatrixCol, &printMatrixRow, &printMatrixCol};

	int i;
	int k;
	for (i = 0; i < 4; i++){
		clock_gettime(CLOCK_REALTIME, &start[i]);
		for (k = 0; k < 10; k++) {
			fptr[i]();	
		}
		clock_gettime(CLOCK_REALTIME, &end[i]);
		fprintf(stderr, "%lf\n", end[i].tv_sec - start[i].tv_sec + (double)(end[i].tv_nsec - start[i].tv_nsec)/(double)BILLION);
	
	}
}

/* This will "print" the matrix row by row, calling print_row with the desired row to "print"
 *
 */
void printMatrixRow () {
	int i;
	for (i = 0; i < ROW; i++)
		print_row (i);
}

/* This will perform IO and actually print the desired row to screen. 
 * It will first call read_one_row and create a copy of the global MATRIX's row,
 * print out the copy, and then free the copy.
 *
 *@param row - the desired row to be printed
 */
void print_row (int row){
	int i;
	int doSomething;
	for (i = 0; i < COL; i++){
	//	printf("%i\n",(int) readr[i]);
		doSomething = MATRIX[row][i] += 1;
	}
	doSomething++;
	return;
}


/*	This will "print" the matrix col by col, calling print_col with the desired col to "print"
 */
void printMatrixCol () {
	int i;
	for (i = 0; i < COL; i++)
		print_col (i);
}

/* This will perform IO and actually print the desired col to screen.
 * It will first call read_one_col and create a copy of the global MATRIX's col,
 * print out the copy, and then free the copy.
 *
 *
 *@param col - the desired col to be printed
 */
void print_col (int col){
	int i;
	int doSomething;
	for (i = 0; i < ROW; i++){
	//	printf("%i\n", (int) readc[i]);
		doSomething = MATRIX[i][col] += 1;
	}
	doSomething++;
	return;
}


/* This will write the matrix row by row, calling write_one_row
 *
 */
void writeMatrixRow (){
	int i;
	for (i = 0; i < ROW; i++)
		write_one_row (i, 0);
}


/* This will write values starting from num to the row specified in the global MATRIX.
 * num will increment each iteration to avoid compiler optimizations.
 *
 * @param int row to write to, num - number to start writing to the desired row
 */
void write_one_row (int row, int num){
	int i;
	for (i = 0; i < COL; i++) {
		MATRIX[row][i] = num++; // num++ to avoid compiler optimization (as neccessary from the project description). I hope simply doing this works.
	}
	return;
}


/* This will write the matrix col by col, calling write_one_col
 *
 */
void writeMatrixCol () {
	int i;
	for (i = 0; i < COL; i++)
		write_one_col (i, 0);
}

/*This will write values startin from num to the col specified in the global MATRIX.
 * num will increment each iteration to avoid compiler optimizations.
 *
 *@param int col to write to, num - number to start writing to the deisred col
 */
void write_one_col (int col, int num){
	int i;
	for (i = 0; i < ROW; i++){
		MATRIX[i][col] = num++; // num++ to avoid compiler optimization (as neccessary from the project description). I hope simply doing this works.
	}
	return;
}

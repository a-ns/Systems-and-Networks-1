#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROW 20480
#define COL 4096

char MATRIX[ROW][COL];

void write_one_row (int, int);
void write_one_col (int, int);
char * read_one_row (int);
char * read_one_col (int);
void print_row (int);
void print_col (int);

int main (int argc, char*argv[]){

	printf("%i\n",(int) sizeof(MATRIX));
	write_one_row(0, 5);
	write_one_col(0, 4);
	print_row(0); //DO NOT ACTUALLY USE IN SUBMISSION BECUASE IO, use read_one instead
	print_col(0); //DO NOT ACTUALLY USE IN SUBMISSION BECAUSE IO, use read_one instead 
	
	return 0;
}
/* This will perform IO and actually print the desired row to screen. 
 * It will first call read_one_row and create a copy of the global MATRIX's row,
 * print out the copy, and then free the copy.
 *
 *@param row - the desired row to be printed
 */
void print_row (int row){
	char * readr = read_one_row(row);
	int i;
	for (i = 0; i < COL; i++){
		printf("%i\n",(int) readr[i]);
	}
	free(readr); //free what we malloc
	return;
}

/* This will perform IO and actually print the desired col to screen.
 * It will first call read_one_col and create a copy of the global MATRIX's col,
 * print out the copy, and then free the copy.
 *
 *
 *@param col - the desired col to be printed
 */
void print_col (int col){
	char * readc = read_one_col(col);
	int i;
	for (i = 0; i < ROW; i++){
		printf("%i\n", (int) readc[i]);
	}
	free(readc); //free what we malloc
	return;
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


/* This creates a copy of the desired row from the global MATRIX and returns a pointer to it.
 *
 *@param int row - the desired row to read
 *@return char * to the recreated row
 */
char * read_one_row (int row){
	char  *read = malloc(COL); //chars are 1 byte big, so doing sizeof(char) * COL is redundant and unneccessary.
	memcpy(read, MATRIX[row], COL); //nice build in function that will copy COL bytes from MATRIX to read, rather than iterating through it ourselves
	return read;
}


/*This creates a copy of the desired col from the global MATRIX and returns a pointer to it.
 *
 *
 *@param int col - the deisred col to read
 *@return char * to the recreated col
 */
char * read_one_col (int col){
	char *read = malloc(ROW);
	int i;
	for (i = 0; i < ROW; i++){ //must iterate through it ourselves because memcpy function doesn't work like that since 2D arrays are just one big 1D array
		read[i] = MATRIX[i][col]; 
	}
	return read;
}

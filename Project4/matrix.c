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
	print_row(0);
	print_col(0);
	
	return 0;
}

void print_row (int row){
	char * readr = read_one_row(row);
	int i;
	for (i = 0; i < COL; i++){
		printf("%i\n",(int) readr[i]);
	}
	free(readr);
	return;
}
void print_col (int col){
	char * readc = read_one_col(col);
	int i;
	for (i = 0; i < ROW; i++){
		printf("%i\n", (int) readc[i]);
	}
	free(readc);
	return;

}
void write_one_row (int row, int num){
	int i;
	for (i = 0; i < COL; i++) {
		MATRIX[row][i] = num++;
	}
	return;
}

void write_one_col (int col, int num){
	int i;
	for (i = 0; i < ROW; i++){
		MATRIX[i][col] = num++;
	}
	return;
}

char * read_one_row (int row){
	char  *read = malloc(COL);
	memcpy(read, MATRIX[row], COL);
	return read;
}

char * read_one_col (int col){
	char *read = malloc(ROW);
	int i;
	for (i = 0; i < ROW; i++){
		read[i] = MATRIX[i][col];
	}
	return read;
}

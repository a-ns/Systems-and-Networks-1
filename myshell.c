/**
* This is a simple shell program.
*
* @author Alex Lindemann, Nathaniel Moore
* @date 8/24/2016
* @info Course COP4634
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"


void printParams (Param_t *);
int is_debug(int , char *[]);

int main (int argc, char *argv[]) {
  int debug = is_debug(argc, argv);
  while(1) {
    char buffer[BIGNUM];
    fprintf (stdout, "%% : ");
    fgets (buffer, BIGNUM, stdin);
    buffer[strlen(buffer) - 1] = '\0';
    if (debug) printf ("The buffer is \"%s\"\n\n", buffer);
    if ( strcmp (buffer, "exit") == 0)
      return 0;

    Param_t params = parse_input (buffer);
    if (debug) printParams(&params);
  }
  return 0;
}

/**
* Program will enter debug mode if user enabled -Debug flag
* Return-Type: int (1 == TRUE, 0 == FALSE)
*/
int is_debug(int argc, char*argv[]){
  return (argc > 1 && strcmp (argv[1], "-Debug") == 0);
}

/**
* Professor supplied printer for a struct PARAMS.
* Function requires a struct PARAMS pointer, so
*    use printParams(&params_struct) when calling if working with structs.
*
*/
void printParams (Param_t *param) {
  int i;
  printf ("InputRedirect: [%s]\n",
    (param->inputRedirect != NULL) ? param->inputRedirect: "NULL");
  printf ("OutputRedirect: [%s]\n",
    (param->outputRedirect != NULL) ? param->outputRedirect:"NULL");
  printf ("ArgumentCount: [%d]\n", param->argumentCount);
  for (i = 0; i < param->argumentCount; i++)
    printf("ArgumentVector[%2d]: [%s]\n", i, param->argumentVector[i]);
  return;
}

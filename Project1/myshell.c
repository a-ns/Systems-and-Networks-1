/**
* This is a simple shell program.
*
* @author Alex Lindemann, Nathaniel Moore
* @date 8/24/2016
* @info Course COP4634
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "parse.h"

/**
* Professor supplied printer for a struct PARAMS.
* @Param Param_t *
*/
void printParams (Param_t *);

/**
* Program will enter debug mode if user enabled -Debug flag
* @Param int, char *[] (argc and argv read in from command line)
* Return-Type: int (standard C, zero is false, nonzero is true)
*/
int is_debug(int , char *[]);

/**
* This executes the commands read in by the parser
* @Param Param_t struct
*/
void run_command( Param_t);

int main (int argc, char *argv[]) {
  int debug = is_debug(argc, argv);
  while(1) {
    char buffer[BIGNUM];
    fprintf (stdout, "%% : ");
    fgets (buffer, BIGNUM, stdin);

    buffer[strlen(buffer) - 1] = '\0';
    if (debug)
      printf ("The buffer is \"%s\"\n\n", buffer);

    if ( strcmp (buffer, "exit") == 0)
      return 0;

    Param_t params = parse_input (buffer);

    if (debug)
      printParams(&params);

    run_command(params);
  }
  return 0;
}

int is_debug(int argc, char*argv[]){
  return (argc > 1 && strcmp (argv[1], "-Debug") == 0);
}

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

void run_command (Param_t params) {
  if (params.argumentCount < 1)
    return;
  int i,
      status = 0,
      n = 1,
      total;
  pid_t children[n], wpid;
  if (strstr(params.argumentVector[0], "testme") != NULL || strstr(params.argumentVector[0], "prime") != NULL) {
    n = atoi (params.argumentVector[1]);
    total = atoi (params.argumentVector[2]);
    if (n == 0 || total == 0) {
      printf("Incorrect input. Expected integer.\n");
      return;
    }
  }
  for (i = 0; i < n; ++i){
      children[i] = fork();
      if (children[i] == -1) {
        exit(-1);
      }
      else if (children[i] == 0) { //child
        if (strstr(params.argumentVector[0], "testme") != NULL || strstr(params.argumentVector[0], "prime") != NULL) {
            params.argumentVector[1] = malloc(sizeof(char)*BIGNUM);
            params.argumentVector[2] = malloc(sizeof(char)*BIGNUM);
            params.argumentVector[3] = malloc(sizeof(char)*BIGNUM);
            //these calls to malloc do not need a corresponding free statement, exec will overwrite and memory will be "freed" or process will exit, freeing memory
            sprintf(params.argumentVector[1], "%i", n);
            sprintf(params.argumentVector[2], "%i", i);
            sprintf(params.argumentVector[3], "%i", total);
            params.argumentVector[4] = NULL;
        }
        if (params.outputRedirect != NULL)
          freopen (params.outputRedirect, "a", stdout);
        if (params.inputRedirect != NULL)
          freopen (params.inputRedirect, "r", stdin);
        execvp(params.argumentVector[0], params.argumentVector);
        printf ("myshell: command not found: %s\n", params.argumentVector[0]);
        exit(0);
      }
  }
  while((wpid = wait(&status)) > 0); //wait for children to finish before accepting new command
  return;
}

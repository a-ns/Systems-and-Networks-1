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


void printParams (Param_t *);
int is_debug(int , char *[]);
void run_command( Param_t);
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
    if (debug){
      printParams(&params);
    }
    run_command(params);

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

void run_command (Param_t params) {
  if (params.argumentCount < 1)
    return;
  int i;
  int status = 0;
  int n = 5; // this is read in as a paramter from shell
  pid_t children[n], wpid;
  /*for (i = 0; i < n; ++i){
    children[i] = fork();
    if (children[i] == -1){
      exit(-1);
    }
    else if (children[i] == 0) {
      //child
      //call the exec function here i guess

      if (params.outputRedirect != NULL)
        freopen (params.outputRedirect, "a", stdout);
      if (params.inputRedirect != NULL)
        freopen (params.inputRedirect, "a", stdin);
      if (execvp(params.argumentVector[0], &(params.argumentVector[1])) == -1)
        printf("exec fail\n");
        exit(0);
    }
  }

    //parent, waits for all other process to finish
    printf ("Parent process : %i\n", getpid());
    while((wpid = wait(&status)) > 0);
    */
  wpid = fork();
  if (wpid == 0) { //child
    execvp (params.argumentVector[0], params.argumentVector);
    printf ("Program \"%s\" not found.\n", params.argumentVector[0]);
    exit(0);
  }
  else {
    //parent
    while((wpid = wait(&status)) > 0);
  }
  return;
}

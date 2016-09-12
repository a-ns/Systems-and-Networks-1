/**
* This is the parser for the shell program.
*
* @author Alex Lindemann, Nathaniel Moore
* @date 8/24/2016
* @info Course COP4634
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

struct PARAM parse_input (char *buffer) {
  Param_t params;
  params.argumentCount = 0; //not guaranteed to be 0 without. For clean output when printing on failure.
  params.inputRedirect = params.outputRedirect = NULL; // not guaranteed to be initialized to NULL. For clean output when printing on failure.
  char *arguments[MAXARGS];
  int i;
  for(i = 0; i < MAXARGS; i++){
    params.argumentVector[i] = NULL;
    arguments[i] = NULL;
 }
  char *current_token = strtok (buffer, " ");
  i = 0;
  while (current_token != NULL) {
    if (i > MAXARGS) {
      fprintf (stdout, "Maximum number of arguments exceeded!.\n");
      params.argumentCount = -1;
      return params;
    }
    arguments[i]  = current_token;
    current_token = strtok (NULL, " ");
    ++i;
  }
  verify_input(i, arguments, &params);
  return params;
}

void verify_input (int i, char *arguments[], Param_t *params) {
  int j;
  int input_found  = 0,
      output_found = 0;
  for (j = 0; j < i; j++) {
    if (params->argumentCount == -1)
      return;
    if (check_special_chars(j, &output_found, &input_found, arguments, params));
    else if ((arguments[j][0] == '>' || arguments[j][0] == '<') && arguments[j][1] == '\0'){ /* Input and output weren't formatted correctly */
          printf ("Error : Improper formatting of file sources.\n");
          params->argumentCount = -1;
          return;
    }
    else if (input_found == 1 && output_found == 1) {
      printf ("Error : Input after file sources not allowed.\n");
      params->argumentCount = -1;
      return;
    }
    params->argumentVector[j] = arguments[j];
    params->argumentCount++;
  }
  //check input/output Redirects for bad characters
  verify_redirects(params);
  return;
}

void verify_redirects (Param_t * params) {
  if (params->inputRedirect != NULL) {
    params->argumentCount -= 1;
    if (strstr (params->inputRedirect, "<") != NULL || strstr (params->inputRedirect, ">") != NULL){
      printf ("Error : Improper formatting of file sources.\n");
      params->argumentCount = -1;
      return;
    }
  }
  if (params->outputRedirect != NULL) {
    params->argumentCount -= 1;
    if (strstr (params->outputRedirect, ">") != NULL || strstr (params->outputRedirect, "<")){
      printf ("Error : Improper formatting of file sources.\n");
      params->argumentCount = -1;
      return;
    }
  }
}

int check_special_chars (int j, int *output_found, int *input_found, char *arguments[], Param_t *params) {
  if ((arguments[j][0] == '>' || arguments[j][0] == '<') && arguments[j][1] != '\0') { /* input and output are formatted correctly */
    if (arguments[j][0] == '>'){
      if (*output_found != 1) {
        params->outputRedirect   = &(arguments[j][1]);
        *output_found = 1;
      }
      else {
        printf ("Error : multiple definitions for file source not allowed.\n");
        params->argumentCount = -1;
        return 0;
      }
    }
    else {
      if (*input_found != 1) {
        params->inputRedirect = &(arguments[j][1]);
        *input_found = 1;
      }
      else {
        printf ("Error : multiple definitions for file source not allowed.\n");
        params->argumentCount = -1;
        return 0;
      }
    }
    arguments[j]++; /* move the pointer past the < > characters */
  }
  return 1;
}

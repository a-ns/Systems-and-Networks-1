/**
* Header for parse.c
*
* @author Alex Lindemann, Nathaniel Moore
* @date 8/24/2016
* @info Course COP4634
*/
#ifndef _parse_h
#define _parse_h


#define MAXARGS 32 /* Professor supplised #define to use */
#define BIGNUM 500 /* For big arrays */
/**
* Professor supplied structure to adhere to.
*/
struct PARAM {
  char *inputRedirect;           /* file name or NULL */
  char *outputRedirect;          /* file name or NULL */
  int  argumentCount;            /* number of tokens in argument vector */
  char *argumentVector[MAXARGS]; /* array of strings */
};
typedef struct PARAM Param_t; /* Professor supplied typedef to use */

/**
* parses the input passed in by buffer
* return-type: struct PARAM
* ------ Errors: If there is an error during parsing, argumentCount will be set to -1 and function will return to caller.
*/
struct PARAM parse_input (char *);


/**
* Verifies the input for any mistakes. Places tokens into the Param_t struct when things work.
* Return-Type: None
*/
void verify_input (int, char *[], struct PARAM *);

void verify_redirects (Param_t *);

int check_special_chars (int , int *, int *, char *[], Param_t *); 

#endif

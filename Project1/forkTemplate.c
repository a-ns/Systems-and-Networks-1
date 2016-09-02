#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main () {
  int i;
  int n = 5; // this is read in as a paramter from shell
  pid_t children[n];
  for (i = 0; i < n; i++){
    children[i] = fork();
    if (children[i] == 0) //so we don't spawn 2^n - 1 processes, breaks out of the loop in child processes
      break;
  }
  if (children[i] == 0) {
    //child
    //call the exec function here i guess
    printf ("i : %i\n", i);
    printf("Child process : %i\n", getpid());
  }
  else {
    //parent, waits for all other process to finish
    printf ("Parent process : %i\n", getpid());
    wait(NULL);
  }
  return 0;
}

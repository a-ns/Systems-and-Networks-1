#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main () {
  int i;
  int status = 0;
  char *output = "output.txt"; // outputRedirect from shell
  int n = 5; // this is read in as a paramter from shell
  pid_t children[n], wpid;
  for (i = 0; i < n; ++i){
    children[i] = fork();
    if (children[i] == -1){
      exit(-1);
    }
    else if (children[i] == 0) {
      //child
      //call the exec function here i guess
      printf ("i : %i\n", i);
      printf("Child process : %i\n", getpid());
      freopen (output, "a", stdout);
      if (execl("/usr/bin/ls", "ls", "-l", NULL) == -1)
        printf("exec fail\n");
        exit(0);
    }
  }
    //parent, waits for all other process to finish
    printf ("Parent process : %i\n", getpid());
    while((wpid = wait(&status)) > 0);
  return 0;
}

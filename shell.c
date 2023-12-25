#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
int main()
{
  int status;
  char command[100];
  int len;
  pid_t child_pid;
  while(1){
    fflush(stdout);
    if(fgets(command,100,stdin)==NULL)
      {
	printf("\n");
	break;
      }
    len = strlen(command);
    if (len > 0 && command[len - 1] == '\n') {
      command[len - 1] = '\0';
    }
    child_pid = fork();
    if(child_pid==-1){
      exit(EXIT_FAILURE);
    }
    if(child_pid == 0){
      if(execlp(command,command,NULL)==-1){
	exit(EXIT_FAILURE);
      }
    }
    else{
      wait(&status);
      if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
	  fprintf(stderr, "./shell: %s: command not found\n", command);
	}
    }
  }
  return 0;
}

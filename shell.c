#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>
#include <signal.h>
int main()
{
  int status;
  char command[100];
  pid_t child_pid;
  pid_t my_pid;
  char *args[100];
  char *envp[] = {NULL};
  char *arg;
  int i = 0;
  while(1){
    fflush(stdout);
    if(fgets(command,100,stdin)==NULL)
      {
	break;
      }

    arg = strtok(command, " \n\t");
    while(arg){
      args[i] = arg;
      arg = strtok(NULL," \n\t");
      i++;
    }
    args[i]=NULL;
    if(args[0]==NULL) continue;

    my_pid = getpid();
    if(strcmp(args[0], "exit")==0)
      {
	if(kill(my_pid, SIGKILL) == -1)
	  {
	    exit(EXIT_FAILURE);
	  }
      }
    child_pid = fork();
    if(child_pid==-1){
      perror("error");
      exit(EXIT_FAILURE);
    }
    if(child_pid == 0){
      if(execve(args[0],args,envp)==-1){
	fprintf(stderr, "./shell: %s: command not found\n", args[0]);
	exit(EXIT_FAILURE);
      }
    }
    else{
      wait(&status);
    }
  }
  return 0;
}

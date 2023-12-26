#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>
#include <signal.h>
extern char **environ;
int main()
{
  int status;
  char command[100];
  pid_t child_pid;
  char *args[100];
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

    if(strcmp(args[0], "exit")==0)
      {
	exit(0);
      }
    i=0;
    child_pid = fork();
    if(child_pid==-1){
      perror("error");
      exit(EXIT_FAILURE);
    }

    if(child_pid == 0){
      if(execvp(args[0],args)==-1){
	fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
	exit(EXIT_FAILURE);
      }
    }
    else{
      do {
	waitpid(child_pid, &status, WUNTRACED);
      } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
  }
  return 0;
}

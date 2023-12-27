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
  char *command_path;
  char *path_token;
  char full_path[256];
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
    child_pid = fork();
    if(child_pid==-1){
      perror("error");
      exit(EXIT_FAILURE);
    }
    if(child_pid==0){
    command_path = getenv("PATH");
    path_token = strtok(command_path, ":");
    while (path_token != NULL) {
      snprintf(full_path, sizeof(full_path), "%s/%s", path_token, args[0]);
      if (access(full_path, X_OK) == 0) {
	if (execve(full_path, args, environ) == -1) {
	  fprintf(stderr, "./shell: %s: command not found\n", args[0]);
	exit(127);
	}
      }

      path_token = strtok(NULL, ":");
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

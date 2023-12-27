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
  char *cmd_path;
  char *path_var = getenv("PATH");
  char *path_copy;
  char *correct_path;
  int i = 0;
  char *dir;
  while(1){
    i=0;
    correct_path = NULL;
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
    if(strcmp(args[0],"env")==0){
      execve(args[0],args,environ);
    }
    if(strcmp(args[0], "exit")==0){
	exit(0);
      }
    if (path_var == NULL) {
      fprintf(stderr, "PATH not found\n");
      return EXIT_FAILURE;
    }
    path_copy = strdup(path_var);
    dir = strtok(path_copy, ":");
    while(dir!=NULL){
      cmd_path = malloc(sizeof(args[0]) + sizeof(dir) + 2);
      cmd_path = strdup(dir);
      strcat(cmd_path,"/");
      strcat(cmd_path,args[0]);
      if (access(cmd_path, X_OK) == 0) {
	correct_path = strdup(cmd_path);
	break;
      }
      free(cmd_path);
      dir = strtok(NULL,":");
    }
    free(path_copy);
    if(correct_path == NULL){
      fprintf(stderr, "./shell: %s: command not found\n", args[0]);
    }
    else{
      child_pid = fork();
      if (child_pid == 0){
	if(execve(correct_path,args,environ) == -1){
	  exit(127);
	}
      }
      else{
	do{
	  waitpid(child_pid, &status, WUNTRACED);
	}while(!WIFEXITED(status) && !WIFSIGNALED(status));
	free(correct_path);
      }
    }
  }
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
extern char **environ;

int main() {
  int status = 0;
  char *command = NULL;
  pid_t child_pid;
  char **args;
  char *arg;
  char *cmd_path;
  char *dir;
  size_t len = 0;
  char *path_var;
  char *path_copy;
  char *correct_path;
  int i;

  while (1) {
    correct_path = NULL;
    i = 0;
    path_var = getenv("PATH");
    fflush(stdout);

    if (getline(&command, &len, stdin) == -1) {
      free(command);
      exit(EXIT_FAILURE);
    }
    args = malloc(strlen(command) * sizeof(char *));
    if(args==NULL){
      exit(EXIT_FAILURE);
    }
    arg = strtok(command, " \n\t");
    while (arg) {
      args[i] = arg;
      arg = strtok(NULL, " \n\t");
      i++;
    }

    args[i] = NULL;

    if (args[0] == NULL) continue;

    if (strcmp(args[0], "env") == 0) {
      execve(args[0], args, environ);
      continue;
    }

    if (strcmp(args[0], "exit") == 0) {
      free(command);
      free(args);
      exit(status);
    }

    if(access(args[0],X_OK)==0){
      child_pid = fork();

      if (child_pid == 0) {
	if (execve(args[0], args, environ) == -1) {
	  for (i = 0; args[i]; i++)
	    free(args[i]);
	  free(args);
	  exit(EXIT_FAILURE);
	}
      } else {
	do {
	  waitpid(child_pid, &status, WUNTRACED);
	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	if (WIFEXITED(status)) {
	  status = WEXITSTATUS(status);
	} else {
	  status = EXIT_FAILURE;
	}
	free(args);
      }
      status = 0; 
      continue;
    }

      
    if (path_var == NULL) {
      for (i = 0; args[i]; i++)
	free(args[i]);
      free(args);
      exit(EXIT_FAILURE);
    }

    path_copy = malloc(sizeof(path_var) * sizeof(char *));
    strcpy(path_copy, path_var);
    dir = strtok(path_copy, ":");

    while (dir != NULL) {
      cmd_path = malloc(strlen(dir) + strlen(args[0]) + 2);
      if (cmd_path == NULL) {
	for (i = 0; args[i]; i++)
	  free(args[i]);
	free(args);
	exit(EXIT_FAILURE);
      }
      strcpy(cmd_path, dir);
      strcat(cmd_path, "/");
      strcat(cmd_path, args[0]);

      if (access(cmd_path, X_OK) == 0) {
	correct_path = strdup(cmd_path);
	if (correct_path == NULL) {
	  for (i = 0; args[i]; i++)
	    free(args[i]);
	  free(args);
	  exit(EXIT_FAILURE);
	}
	free(cmd_path);
	break;
      }
      free(cmd_path);
      dir = strtok(NULL, ":");
    }
    
    if (correct_path == NULL) {
      fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
    }
    else {
      child_pid = fork();
      if (child_pid == 0) {
	if (execve(correct_path, args, environ) == -1) {
	  for (i = 0; args[i]; i++)
	    free(args[i]);
	  free(args);
	  exit(EXIT_FAILURE);
	}
	status = 0;
      }
      else {
	  waitpid(child_pid, &status, 0);
      }
      if (WIFEXITED(status)) {
	status = WEXITSTATUS(status);
      }
      else {
	status = EXIT_FAILURE;
      }
    }
    
    free(correct_path);
    free(path_copy);
    free(args);
    exit(status);
  }
  free(command);
  exit(0);
  return 0;
}

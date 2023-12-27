#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

int main() {
  int status;
  char command[100];
  pid_t child_pid;
  char *args[100];
  char *arg;
  char *cmd_path;
  char *dir;
  char *path_var = getenv("PATH");
  char *path_copy;
  char *correct_path;
  int i;

  while (1) {
    correct_path = NULL;
    i = 0;

    fflush(stdout);

    if (fgets(command, 100, stdin) == NULL) {
      break;
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
      perror("execve");
      exit(EXIT_FAILURE);
    }

    if (strcmp(args[0], "exit") == 0) {
      exit(0);
    }

    if (path_var == NULL) {
      fprintf(stderr, "PATH not found\n");
      return EXIT_FAILURE;
    }

    path_copy = strdup(path_var);
    dir = strtok(path_copy, ":");

    while (dir != NULL) {
      cmd_path = malloc(strlen(dir) + strlen(args[0]) + 2);
      if (cmd_path == NULL) {
	perror("malloc");
	exit(EXIT_FAILURE);
      }
      strcpy(cmd_path, dir);
      strcat(cmd_path, "/");
      strcat(cmd_path, args[0]);

      if (access(cmd_path, X_OK) == 0) {
	correct_path = strdup(cmd_path);
	if (correct_path == NULL) {
	  perror("strdup");
	  exit(EXIT_FAILURE);
	}
	break;
      }

      free(cmd_path);
      dir = strtok(NULL, ":");
    }

    free(path_copy);

    if (correct_path == NULL) {
      fprintf(stderr, "./shell: %s: command not found\n", args[0]);
    } else {
      child_pid = fork();

      if (child_pid == 0) {
	if (execve(correct_path, args, environ) == -1) {
	  perror("execve");
	  exit(EXIT_FAILURE);
	}
      } else {
	do {
	  waitpid(child_pid, &status, WUNTRACED);
	} while (!WIFEXITED(status) && !WIFSIGNALED(status));

	free(correct_path);
      }
    }
  }

  return 0;
}

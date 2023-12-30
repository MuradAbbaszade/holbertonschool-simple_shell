#include <stdio.h>
#include "main.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *get_correct_path(char *path_var, char **args)
{
  char *path_copy;
  char *dir;
  char *cmd_path;
  char *correct_path;
    path_copy = malloc(sizeof(path_var) * sizeof(char *));
    strcpy(path_copy, path_var);
    dir = strtok(path_copy, ":");

    while (dir != NULL) {
      cmd_path = malloc(strlen(dir) + strlen(args[0]) + 2);
      if (cmd_path == NULL) {
	free(args);
	free(path_copy);
	free(cmd_path);
	exit(EXIT_FAILURE);
      }
      strcpy(cmd_path, dir);
      strcat(cmd_path, "/");
      strcat(cmd_path, args[0]);

      if (access(cmd_path, X_OK) == 0) {
	correct_path = strdup(cmd_path);
	if (correct_path == NULL) {
	  free(args);
	  free(path_copy);
	  free(cmd_path);
	  exit(EXIT_FAILURE);
	}
	free(cmd_path);
	break;
      }
      free(cmd_path);
      dir = strtok(NULL, ":");
    }
    free(path_copy);
    return (correct_path);
}

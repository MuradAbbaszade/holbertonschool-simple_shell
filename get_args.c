#include <stdio.h>
#include "main.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char **get_args(char *command)
{
  char *arg;
  char **args;
  int i = 0;
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
    return (args);
}

#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
extern char **environ
int run_command(char **args);
char **get_args(char *command);
char *get_correct_path(char *path_var, char **args);
#endif

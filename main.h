#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;
void run_exit(char *command, char **args, int status);
int run_with_full_path(char *correct_path, char **args);
int run_command(char **args);
char **get_args(char *command);
char *get_correct_path(char *path_var, char **args);
#endif

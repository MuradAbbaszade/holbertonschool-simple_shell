#ifndef MAIN_H
#define MAIN_H

int run_command(char **args);
char **get_args(char *command);
char *get_correct_path(char *path_var, char **args);
#endif

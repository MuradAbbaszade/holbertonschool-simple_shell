#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "main.h"

/**
 * get_correct_path - Find the correct full path for a given command in the PATH variable.
 * @path_var: The PATH variable string.
 * @args: An array of strings representing the command and its arguments.
 * Return: Full path of the command
 */
char *get_correct_path(char *path_var, char **args)
{
    char *path_copy;
    char *dir;
    char *cmd_path;
    char *correct_path = NULL;
    path_copy = malloc(strlen(path_var) + 1);
    strcpy(path_copy, path_var);
    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        cmd_path = malloc(strlen(dir) + strlen(args[0]) + 2);
        if (cmd_path == NULL)
        {
            free(args);
            free(path_copy);
            free(cmd_path);
            exit(EXIT_FAILURE);
        }
        strcpy(cmd_path, dir);
        strcat(cmd_path, "/");
        strcat(cmd_path, args[0]);
        if (access(cmd_path, X_OK) == 0)
        {
            correct_path = strdup(cmd_path);
            if (correct_path == NULL)
            {
                free(cmd_path);
                free(args);
                free(path_copy);
                exit(EXIT_FAILURE);
            }
            break;
        }
        free(cmd_path);
        dir = strtok(NULL, ":");
    }
    if (correct_path != NULL)
        free(cmd_path);
    free(path_copy);
    return (correct_path);
}

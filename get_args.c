#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "main.h"

/**
 * get_args - Tokenize a command into arguments.
 * @command: The command to tokenize
 * Return: An array of strings representing the arguments.
 */

char **get_args(char *command)
{
        char *arg;
        char **args;
        int i = 0;
        args = malloc(strlen(command) * sizeof(char *));
        if (args == NULL)
        {
            exit(EXIT_FAILURE);
        }
        arg = strtok(command, " \n\t");
        while (arg)
        {
            args[i] = arg;
            arg = strtok(NULL, " \n\t");
            i++;
        }
        args[i] = NULL;
        return (args);
}

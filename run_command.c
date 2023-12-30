#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
extern char **environ;
/**
 * run_command - Execute a command.
 * @args: An array of strings representing the command and its arguments.
 *
 * Return: The exit status of the executed command.
 */
int run_command(char **args)
{
        int i;
        int status;
        pid_t child_pid = fork();
        if (child_pid == 0)
        {
            if (execve(args[0], args, environ) == -1)
            {
                for (i = 0; args[i]; i++)
                    free(args[i]);
                free(args);
                exit(EXIT_FAILURE);
            }
            status = EXIT_SUCCESS;
        }
        else
        {
            waitpid(child_pid, &status, WUNTRACED);
            if (WIFEXITED(status))
            {
                status = WEXITSTATUS(status);
            }
        }
        return (status);
}

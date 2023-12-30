#include "main.h"

/**
 * main - Entry point for the simple shell program.
 *
 * Return: The exit status of the shell.
 */
int main(void)
{
int status = 0;
char *command = NULL;
char **args;
size_t len = 0;
char *path_var;
char *correct_path;
int i;
  
while (1)
{
i = 0;
correct_path = NULL;
path_var = getenv("PATH");
fflush(stdout);
if (getline(&command, &len, stdin) == -1)
{
free(command);
exit(status);
}
if (command == NULL)
break;
args = get_args(command);
if (args[0] == NULL)
continue;
if (strcmp(args[0], "exit") == 0)
{
run_exit(command, args, status);
}
if (access(args[0], X_OK) == 0)
{
status = run_command(args);
free(args);
continue;
}
if (path_var == NULL)
{
for (i = 0; args[i]; i++)
free(args[i]);
free(args);
exit(EXIT_FAILURE);
}
correct_path = get_correct_path(path_var, args);
status = run_with_full_path(correct_path, args);
free(args);
}
free(command);
exit(status);
return (status);
}

/**
 * run_exit - Clean up resources and exit the program.
 * @command: The command string.
 * @args: An array of strings representing the command and its arguments.
 * @status: The exit status code.
 */
void run_exit(char *command, char **args, int status)
{
free(command);
free(args);
exit(status);
}

/**
 * run_with_full_path - Execute a command with its full path.
 * @correct_path: The full path to the executable command.
 * @args: An array of strings representing the command and its arguments.
 * Return: The exit status of the executed command.
 */
int run_with_full_path(char *correct_path, char **args)
{
int status = 0;

if (correct_path == NULL)
{
status = 127;
fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
}
else
{
args[0] = correct_path;
status = run_command(args);
free(correct_path);
}
return (status);
}

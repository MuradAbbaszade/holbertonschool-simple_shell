# Simple Shell Project

## Overview
This is a simple shell project written in C. The shell allows users to execute commands in a Unix-like environment.

## Features
- Accepts input from the command line.
- Utilizes strtok to parse commands and arguments.
- Looks for executable files in the PATH environment variable.
- Provides informative error messages for better handling.
- Executes commands through fork, execve, and waitpid.
- Ability to run shell scripts containing a series of commands.

## Building the Shell
To compile the shell, use the following command:

```bash
gcc *.c -o hsh
```
Running the Shell
Execute the following command to run the shell:

```bash
./hsh
```
Usage
Once the shell is running, you can enter various commands supported by the shell.

Example
```bash
$ ./hsh
ls -l
total 76
-rw-r--r-- 1 root root   140 Dec 30 04:10 AUTHORS
-rw-r--r-- 1 root root   541 Dec 30 11:08 get_args.c
-rw-r--r-- 1 root root  1070 Dec 30 11:13 get_correct_path.c
-rwxr-xr-x 1 root root 17952 Dec 30 11:51 hsh
-rw-r--r-- 1 root root   389 Dec 30 11:47 main.h
-rw-r--r-- 1 root root  1099 Dec 30 10:23 man_1_simple_shell
-rw-r--r-- 1 root root   650 Dec 30 11:49 README.md
-rw-r--r-- 1 root root   639 Dec 30 11:15 run_command.c
-rwxr-xr-x 1 root root 17744 Dec 30 02:27 shell
-rw-r--r-- 1 root root  1746 Dec 30 11:47 shell.c
-rwxr-xr-x 1 root root   119 Dec 17 04:00 push
```

| File                  | Description                                   |
|-----------------------|-----------------------------------------------|
| AUTHORS               | List of contributors to the project           |
| get_args.c            | Parses user input to extract command and arguments |
| get_correct_path.c    | Searches for the correct path of executable files in the PATH variable |
| hsh                   | Executable file for the shell program         |
| main.h                | Header file with function declarations       |
| man_1_simple_shell    | Manual page for the simple shell program      |
| README.md             | Documentation file (you're reading it now)  |
| run_command.c         | Executes commands using fork, execve, and waitpid |
| shell                 | Executable file for the shell program         |
| shell.c               | Source code file for the shell program        |
| push                  | git add . , git commit -m "a" , git push  |

## Authors
-Murad Abbaszade: [GitHub Profile](https://github.com/MuradAbbaszade)

-Tural Bayramli: [GitHub Profile](https://github.com/STTGL)

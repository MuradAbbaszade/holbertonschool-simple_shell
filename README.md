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
hsh$ ls -l
```

## Authors
-Murad Abbaszade: [GitHub Profile](https://github.com/MuradAbbaszade)

-Tural Bayramli: [GitHub Profile](https://github.com/STTGL)

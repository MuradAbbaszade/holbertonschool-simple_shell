#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
void trim_whitespaces(char *str) {
  char *end;
  while (*str == ' ' || *str == '\t') {
        str++;
    }
    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\n')) {
        end--;
    }
    *(end + 1) = '\0';
}
int main()
{
  int status;
  char command[100];
  int len;
  pid_t child_pid;
  while(1){
    fflush(stdout);
    if(fgets(command,100,stdin)==NULL)
      {
	break;
      }
    trim_whitespaces(command);
    len = strlen(command);
    if (len > 0 && command[len - 1] == '\n') {
      command[len - 1] = '\0';
    }
    child_pid = fork();
    if(child_pid==-1){
      perror("error");
      exit(EXIT_FAILURE);
    }
    if(child_pid == 0){
      if(execlp(command,command,NULL)==-1){
	fprintf(stderr, "./shell: %s: command not found\n", command);
	exit(EXIT_FAILURE);
      }
    }
    else{
      wait(&status);
    }
  }
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>
void removeWhitespaces(char *str) {
    if (str == NULL) {
      return;
    }
    int i = 0, j = 0;
    while (str[i]) {

        if (!isspace((unsigned char)str[i])) {
            str[j] = str[i];
            j++;
        }
        i++;
    }
    str[j] = '\0';
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
    removeWhitespaces(command);
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

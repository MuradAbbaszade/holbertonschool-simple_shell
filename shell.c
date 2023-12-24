#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
int main()
{
  int status;
  char command[100];
  int len;
  pid_t child_pid;
  char* args;
  while(1){
    printf("murad$ ");
  if(fgets(command,100,stdin)==NULL)
    {
      exit(EXIT_FAILURE);
    }
  len = strlen(command);
  command[len-1]='\0';
  child_pid = fork();
  if(child_pid==-1){
    exit(EXIT_FAILURE);
  }
  if(child_pid == 0){
    if(execlp(command,command,NULL)==-1){
      printf("./shell: No such file or directory\n");
    }
  }
  else{
    wait(&status);
  }
  }
  return 0;
}

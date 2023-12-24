#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(){
  int i = 0;
  int status;
  pid_t child_pid;
  for (i=0;i<5;i++){
    child_pid = fork();
    if(child_pid == 0){
      char *argv[] = {"/bin/ls", "-l", "/tmp/", NULL};
      if (execve(argv[0], argv, NULL) == -1)
	{
	  perror("Error:");
	}
    }
    else{
      wait(&status);
      printf("%i\n",status);
    }
  }
  return 0;
}

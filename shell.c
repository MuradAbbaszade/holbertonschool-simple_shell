#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main()
{
  char command[100];
  int i = 0;
  int j = 0;
  if (fgets(command, 100, stdin) != NULL) {
    i=strlen(command)-1;
    command[i]='\0';
    char *a = strtok(command," ");
    while(a!=NULL){
      printf("%s",a);
      a = strtok(NULL," ");
    }
    printf("bash: %s: command not found\n",command);
  }
  else{
    exit(98);
  }
  return (1);
}

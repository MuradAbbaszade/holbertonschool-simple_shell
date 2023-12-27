#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main() {
  char *command = "ls";
  char *cmd_path = NULL;
  char *correct_path = NULL;
  char *path_copy;
  char *dir;
  FILE *fp;
  char *path_var = getenv("PATH");
  if (path_var == NULL) {
    fprintf(stderr, "PATH değişkeni bulunamadı.\n");
    return EXIT_FAILURE;
  }
  path_copy = strdup(path_var);
  dir = strtok(path_copy, ":");
  while(dir!=NULL){
    cmd_path = malloc(sizeof(command) + sizeof(dir) + 2);
    cmd_path = strdup(dir);
    strcat(cmd_path,"/");
    strcat(cmd_path,command);
    if (access(cmd_path, X_OK) == 0) {
      correct_path = strdup(cmd_path);
      break;
    }
    dir = strtok(NULL,":");
  }
  if(correct_path == NULL){
    printf("%s",correct_path);
    exit(EXIT_FAILURE);
  }
  else{
    printf("%s",correct_path);
    exit(EXIT_SUCCESS);
  }
}

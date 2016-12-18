#include <stdio.h>
#include <unistd.h>

int main() {

  pid_t pid;
  
  pid = fork();
  printf("Line 1\n");
  pid = fork();
  printf("Line 2\n");
  if (fork() == 0)
    printf("Line 3\n");
  else
    printf("Line 4\n");
  return(0);
} // main()

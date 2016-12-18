#include <stdio.h>
#include <unistd.h>

int main() {

  int x = 1;
  pid_t pid;
  
  pid = fork();

  if (pid ==0) {
    x++;
    printf("hello from child\n");
    printf("value of x in child (incremented): %d\n", x);
    int y = getpid();
    printf("process id of child: %d\n", y);
  }
  else {
    x--;
    sleep(1);
    printf("hello from parent\n");
    printf("value of x in parent (decremented): %d\n", x);
    printf("process id of parent: %d\n", pid);
  }
  return(0);
} // main()

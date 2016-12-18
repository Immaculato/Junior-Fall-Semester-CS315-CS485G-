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
    printf("%d\n", y);
  }
  else {
    x--;
    sleep(1);
    printf("hello from parent\n");
    printf("value of x in parent (decremented): %d\n", x);
    printf("%d\n", pid);
  }
  return(0);
} // main()

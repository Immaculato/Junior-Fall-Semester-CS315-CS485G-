#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  if (fork() == 0) { /* I am the child */
    printf("The child (pid=%d) will now terminate\n", getpid());
    exit(0);
  }
  else { /* I am the parent */
    printf("The parent (pid=%d) entering an infinite loop\n", getpid());
    while (1); /* this is an infinite loop */
  }
  return(0);
} // main()

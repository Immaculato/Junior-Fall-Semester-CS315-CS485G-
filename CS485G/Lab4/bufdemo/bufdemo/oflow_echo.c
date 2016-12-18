#include <stdlib.h>
#include <stdio.h>

void echo();

/* Main program */
int main() {
  while (1)
      echo();
  return(0); // never called
} // main

/* My gets -- just like gets - Get a string from stdin */
char *mygets(char *dest) {
  int c = getchar();
  char *p = dest;
  while (c != EOF && c != '\n') {
    *p++ = c;
    c = getchar();
  }
  *p = '\0';
  return dest;
} // mygets

/* Echo Line */
void echo() {
  char buf[4];    /* Way too small */
  
  mygets(buf);
  puts(buf);
} // echo
  
void not_called() {
  printf("This routine is never called\n");
  printf("If you see this message, something bad has happend\n");
  exit(0);
} // not_called

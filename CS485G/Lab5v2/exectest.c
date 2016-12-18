#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#define BUFLEN 256

int main() {

	pid_t pid;
	int retval, child_status;
	char cmd[BUFLEN];
	char param[BUFLEN];

	printf("To exit, type the letter q as the program to run\n");
	printf("and then type anything you like as the parameter.\n");
    printf("Enter a program to run: ");
    fgets(cmd, BUFLEN, stdin);
    cmd[strlen(cmd)-1] = '\0'; /* this removes the \n */
    
    printf("Enter a single parameter to the program: ");
    fgets(param, BUFLEN, stdin); 
    param[strlen(param)-1] = '\0'; /* this removes the \n */

    while (cmd[0] != 'q') {

     /* create a process to run the requested program */
     pid = fork();
     if (pid ==0) {
       
       printf("The child is running. The child is about to run %s %s\n",
	      cmd, param);


	execl(cmd, param, param, NULL);
       /* ----------------- YOUR CODE GOES HERE -------------------------*/
       /* add code to call one of the forms of exec to run the program   */
       /* cmd with the paramter param.                                   */
       /*                                                                */
       /* Hint: this can be written in as little as one line of code.    */
       /* ----------------- YOUR CODE GOES HERE -------------------------*/

        /* These line should not be executed */
       printf("If you see this, then the child failed to exec the program\n");
       exit(0);
     }
     else {
       
       printf("The parent started a child to run %s %s.\n", cmd, param);
       retval = wait(&child_status); /* block until child terminates */
       
     }

     /* read the next command to execute */
     printf("Enter a program to run: ");
     fgets(cmd, BUFLEN, stdin);
     cmd[strlen(cmd)-1] = '\0'; /* this removes the \n */
     
     printf("Enter a single parameter to the program: ");
     fgets(param, BUFLEN, stdin); 
     param[strlen(param)-1] = '\0'; /* this removes the \n */
  }  /* end while */
  return(0);
} // main()

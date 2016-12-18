#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Set Abuf to be empty.  Read string into Bbuf. Print out Abuf and Bbuf */
void echo()
{
	char Abuf[4];
	char Bbuf[4];

	Abuf[0] = '\0';
	gets(Bbuf);
	printf(" Abuf = '%s'\n Bbuf = '%s'\n", Abuf, Bbuf);
} // echo()

int main(int argc, char *argv[])
{
	printf("Enter a string: ");
	echo();
	return(0);
} // main()

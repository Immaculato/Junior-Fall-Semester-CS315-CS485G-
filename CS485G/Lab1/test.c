/* The web site http://www.ibm.com/developerworks/library/l-gnuprof.html has
 * a nice description of how to use the gprof utility.  Please consult
 * that site for additional information.  The following code is derived
 * from code on that page, but shows an addition level of procedure calls.
 *
 * A nice overview of the features and command line options available in
 * gprof can be found here http://www.cs.utah.edu/dept/old/texinfo/as/gprof.html
 *
 * Your goal in this exercise is to use the gcc, gprof, and valgrind programs
 * to analyze the performance of the program below.   You should follow
 * the steps below and should save your session in a file called mysession.txt.
 * You should then upload your "mysession.txt" file to the
 * CS Portal: https://www.cs.uky.edu/csportal.
 *
 * YOU MUST PERFORM THIS EXERCISE ON YOUR VM.
 *
 * A. Record your session:
 *   1. Use the "script" command (script mysession.txt)
 *
 * B. Read through the test program to see what it is doing
 *   1. Use one of less, vim, emacs, gedit, or some other program
 *      to display the program.
 *  
 * C. Compile with varying levels of optimizations and time the runtime
 *   1. Compile with no optimizations using the -O0 option (gcc -Wall -O0 -o test test.c)
 *   2. Run and time the program (time ./test 1000)
 *   3. Compile with max optimizations using the -O3 option (gcc -Wall -O3 -o test test.c)
 *   4. Run and time the program (time ./test 1000)
 *   5. Say which is faster (echo "The FILL_IN_THE_BLANK was faster.  It took FILL_IN_THE_BLANK time.")
 *
 * D. Profile both versions of the program using "gprof"
 *    (Do the following steps twice: first with a test program
 *     with no optimizations (-O0), and then with a test program
 *     with max optimizations (-O3).
 *   Steps to use gprof:
 *   1. compile with profiling and debugging options (-p and -g)
 *       and with the appropriate optimization.  For
 *       example, with no optimization it would be "gcc -Wall -p -g -O0 -o test test.c"
 *   2. run the program (./test 1000)
 *   3. print a "flat profile" (gprof -p ./test)
 *   4. print a "call stack profile" (gprof -q ./test)
 *
 * (Remember to repeat the above steps using max optimizations)
 *
 * E. Now profile both versions of the program using "valgrind"
 *    (Do the following steps twice: first with a test program
 *     with no optimizations (-O0), and then with a test program
 *     with max optimizations (-O3).
 *   Steps to use valgrind/kcachegrind:
 *   1. run valgrind to create a callgrind profile file
 *      (valgrind --tool=callgrind ./test 1000)
 *   2. run kcachegrind to view the profile (kcachegrind)
 *      Note this will not produce output in your mysession.txt file
 * 
 * F. Stop recording your session:
 *   1. type "exit"
 *
 * G. Now open a web browser on your VM and upload mysession.txt to https://www.cs.uky.edu/csportal
 */
#include <stdio.h>
#include <stdlib.h>

int a(void) {
  int i = 0, g = 0;
  while(i++ < 100000) {
	  g += i;
  }
  return g;
} // a()

int c(void) {
  int i = 0, g = 0;
  while(i++ < 400000) {
	 g += i;
  }
  return g;
} // c()

int b(void) {
  int i = 0, g = 0;
  while(i++ < 400000) {
	 g += i;
  }
  c();
  return g;
} // b()

/* ---- main() ---- */
int main(int argc, char** argv)
{
	int iterations;
	if(argc != 2) {
		printf("Usage %s <Number of Iterations>\n", argv[0]);
		exit(-1);
	} else {
		iterations = atoi(argv[1]);
	}
	printf("No of iterations = %d\n", iterations);
	while(iterations--) {
		a();
		b();
	}
	return(0);
} // main

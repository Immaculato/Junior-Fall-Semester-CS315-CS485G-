/*
 * Test program for benchmarking.
 * slightly modified from an example used in Systems Programming (cs485 NFM)
 *
 */
#include <stdio.h>
#include <stdlib.h>

/* ---- A() ---- */
int A(void)
{
	int i = 0, p = 0;
	while (i++ < 100000)
		p *= i % 100;
	return p;
}

/* ---- C() ---- */
int C(void)
{
	int i = 0, p = 0;
	while (i++ < 500000)
		p *= i % 100;
	return p;
}

/* ---- b() ---- */
int B(void)
{
	int i = 0, p = 0;
	while (i++ < 500000)
		p *= i % 100;
	C();
	return p;
}

/* ---- main() ---- */
int main(int argc, char** argv)
{
	int iterations;

	if (argc != 2)
	{
		printf("Usage %s <num-iterations>\n", argv[0]);
		exit(-1);
	}
	iterations = atoi(argv[1]);

	printf("# iterations = %d\n", iterations);

	while (iterations--)
	{
		A();
		B();
	}

	return 0;
}

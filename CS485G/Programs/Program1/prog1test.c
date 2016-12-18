#include <stdio.h>
#include <string.h>
typedef unsigned char *pointer;
	void show_bytes(pointer start, int len){
	int i;
	for (i = 0; i < len; i += 1) {
		printf("%p\t0x%.2x\n",start+i, start[i]);
	}
	printf("\n");
} // show_bytes
int main() {
	int a = 15213;
	printf("int a = %d (0x%08x);\n", a, a);
	show_bytes((pointer) &a, sizeof(int));
	return 0;
} 

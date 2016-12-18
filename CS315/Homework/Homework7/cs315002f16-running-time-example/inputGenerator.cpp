#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

int main(int argc, char **argv) {
	srand(time(NULL));
	int sizeboard = atoi(argv[1]);
	cout << sizeboard+5 << endl;
	for (int i=1; i<sizeboard; i++) {
		int possibleGreaters = rand() % (sizeboard-i);
		cout << possibleGreaters;
		for (int j=0; j<possibleGreaters; j++) {
			cout << " " << rand() % (sizeboard-i) + (i+1);
		}
		cout << endl;
	}
}		

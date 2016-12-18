#include <iostream>
#include <sstream>
using namespace std;

int main() {
	int firstdie;
	int seconddie;
	int temp;
	cin >> firstdie;
	cin >> seconddie;
	if (seconddie < firstdie) {
		temp = firstdie;
		firstdie = seconddie;
		seconddie = temp;
	}
	for (int i=firstdie+1; i<=seconddie+1; i++) cout << i << endl;
}

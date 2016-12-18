#include <iostream>

using namespace std;

int main() {
	int squares[101];
	squares[0]=0;
	for (int i=1; i<101; i++) {
		squares[i] = i*i;
		squares[i]+=squares[i-1];
	}
	int size;
	cin >> size;
	while (size != 0) {
		cout << squares[size] << endl;
		cin >> size;
	}
}


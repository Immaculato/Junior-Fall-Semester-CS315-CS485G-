#include <stack>
#include <iostream>

using namespace std;

void hanoi(int n, int A, int B, int C) {
	if (n<=0) return;
	hanoi(n-1, A, C, B);
	cout << "move disk "<<n<<" from "<< A<< " to " << C << endl;
	hanoi(n-1, B, A, C);
}

//eliminate tail recursion by making a goto statement, and including the recursive
//changes into a series of statements.
void hanoi2(int n, int A, int B, int C) {
	int t;
	a: if (n <= 0) return;
	hanoi2(n-1, A, C, B);
	cout << "move disk "<<n<<" from "<< A<< " to " << C << endl;
	n--; t=A; A=B; B=t;
	goto a;
}

//gotos are scary, so this one used a while loop instead.
void hanoi3(int n, int A, int B, int C) {
	int t;
	while (n>0) {
		hanoi3(n-1, A, C, B);
		cout << "move disk "<<n<<" from "<< A<< " to " << C << endl;
		n--; 
		t=A; 
		A=B; 
		B=t;
	}
}

int main() {
	int userinput;
	cin >> userinput;
	cin.ignore();
	int A=1;
	int B = 2;
	int C = 3;
	hanoi(userinput, A, B, C);
	cout << "goto version" << endl;
	hanoi2(userinput, A, B, C);
	cout << "while version" << endl;
	hanoi3(userinput, A, B, C);
}
		
		


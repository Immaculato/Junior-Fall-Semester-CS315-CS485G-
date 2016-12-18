#include <string>
#include <iostream>

using namespace std;

/** Works Cited: Keisuke Kanao's solution to uva 11960 (divisor game)
 *   ***I DO NOT TAKE CREDIT FOR THE CITED SOLUTION***    
 *  The aforementioned work was used extensively in creating a solution
 *   that fulfilled the time requirement for the divisor game.
 *
 */

/*
void printLargestDivisor(int N) {
	int largestDivisor = 1;
	int numDivisors = 2;
	int largestNumDivisors = 2;
	for (int i=2; i<N+1; i+=2) {
		numDivisors=2;
		for (int j=2; j*j<i; j+=1) {
			if (i%j == 0) {
				 numDivisors+=2; 
				 if (i==j) numDivisors-=1;
			}
		}
		if (numDivisors >= largestNumDivisors) {
			largestDivisor = i;
			largestNumDivisors=numDivisors;
		}
	}
	cout << largestDivisor << endl;
}
*/
// my original solution above: functional, but too slow

int main() {

	int numberDivisors[1000001];
	int largestDivisors[1000001];
	for (int i=1; i <= 1000000; i+=1) {
		for (int j=i; j <= 1000000; j+=i) {
			numberDivisors[j]+=1;
		}
	}
	int largestNumDivisor = 0;
	int largestNumDivisorIndex = 0;
	for (int i=1; i<=1000000; i+=1) {
		if (largestNumDivisor <= numberDivisors[i]) {
			largestNumDivisor = numberDivisors[i];
			largestNumDivisorIndex = i;
		}
		largestDivisors[i] = largestNumDivisorIndex;
	}
	int userinput;
	cin >> userinput;
	if (!((userinput>0)&&(userinput<50001))) {
		return 1;
	}
	cin.ignore();
	for (int i=0; i<userinput; i++) {
		int N;
		cin >> N;
		cout << largestDivisors[N] << endl;
	}
}

		
		


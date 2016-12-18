#include <iostream>
#include <cmath> 
using namespace std;

int main() {
	long long int N;
	while (cin >> N) {
		long long int sum = 0;
		long long int i=N-2;
		i = pow(2, i) + 1;
		for (int j=0; j<3; j++) {
			sum+=i;
			i+=2;
		}
		cout << sum;
	}
}


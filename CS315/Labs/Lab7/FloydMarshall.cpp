#include <iostream>
#include <climits>
#include <sstream>
using namespace std;

const int MAX = 21470000;

int main() {
	int sizeMatrix;	
	cin >> sizeMatrix;
	int weights[sizeMatrix][sizeMatrix];
	for (int i=0; i<sizeMatrix; i++) {
		for (int j=0; j<sizeMatrix; j++) {
			string weight;
			cin >> weight;
			if (weight == "X") {	
				weights[i][j] = MAX;
			} else {
				stringstream stream(weight);
				int numweight;
				stream >> numweight;
				weights[i][j] = numweight;
			}
		}
	}
	
	for (int k=0; k<sizeMatrix; k++) {
		for (int i=0; i<sizeMatrix; i++) {
			for (int j=0; j<sizeMatrix; j++) {
				if (weights[i][j] > weights[i][k] + weights[k][j]) {
					weights[i][j] = weights[i][k] + weights[k][j];
				}
			}
		}
	}

	cout << "weights:" << endl;
	for (int i=0; i<sizeMatrix; i++) {
		for (int j=0; j<sizeMatrix; j++) {
			if (weights[i][j] == MAX) cout << "INF ";
			else cout << weights[i][j] << " ";
		}
		cout << endl;
	}
}			

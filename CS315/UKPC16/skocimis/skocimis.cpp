#include <iostream>
#include <sstream>
using namespace std;

int main() {
	int first, second, third, moves;
	string line;
	getline(cin, line);
	stringstream stream(line);
	stream >> first;
	stream >> second;
	stream >> third;
	if (third-second > second-first) cout << third-second-1;
	if (third-second < second-first) cout << second-first-1;
	if (third-second == second-first) cout << third-second-1;	
}

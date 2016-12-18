#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
	string inputline;
	vector<string> strings;
	while (cin >> inputline) {
		for (int i=0; i<inputline.length(); i++) {
			inputline[i]-=7;
		}
		strings.push_back(inputline);
	}
	for (int i=0; i<strings.size(); i++) {
		cout << strings[i] << endl;
	}
}

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

const vector<int> ALPHABET = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','_','.'};

void printReverseRot(string reverse, int offset) {
	for (int i=reverse.length()-1; i>=0; i--) {
		int value = reverse[i]+offset;
		if (value == 95+offset) value = 26+offset;
		else if (value == 46+offset) value = 27+offset;
		else value= value%65;
		char character = ALPHABET[value%28];
		cout << character;
	}
}

int main() {
	vector<int> rotationvalues;
	vector<string> rotationstrings;
	while (true) {
		string line;
		getline(cin, line);
		stringstream stream(line);
		int value;
		stream >> value;
		if (value == 0) break;
		rotationvalues.push_back(value);
		stream >> line;
		rotationstrings.push_back(line);
	}
	for (int i=0; i<rotationvalues.size(); i++) {
		printReverseRot(rotationstrings[i], rotationvalues[i]);
		if (i < rotationvalues.size()-1) cout << endl;
	}
}

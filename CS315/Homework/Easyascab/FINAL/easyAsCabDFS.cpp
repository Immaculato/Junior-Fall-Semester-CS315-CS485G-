#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

bool loop = false;

struct letter {
	set<char> followers;
	int numPredecessors = 0;
	int depth = 0;
	bool visited = false;
};

map<char, letter> alphabet;


void findDepth(char root, int depth) {
	if (loop) return;
	set<char> charFollowers = alphabet[root].followers;
	for (set<char>::iterator it = charFollowers.begin(); it!=charFollowers.end(); it++) {
		if (alphabet[*it].depth < depth) alphabet[*it].depth = depth;
		if (alphabet[*it].visited) loop = true;
		alphabet[*it].visited = true;
		findDepth(*it, depth+1);
		alphabet[*it].visited = false;
	}
}

string buildFinalAlphabet(char highestChar) {
	int index = 0;
	const int arraySize = highestChar - 96;
	string finalString = "";
	for (int i=0; i<arraySize; i++) finalString+="*";
	set<int> depths;
	int oldsize=0;
	for (char i='a'; i<=highestChar; i++) {
		int depth = alphabet[i].depth;
		depths.emplace(depth);
		int currsize = depths.size();
		if (currsize == oldsize) return "*";
		finalString[alphabet[i].depth] = i;
		oldsize = currsize;
	}
	return finalString;
}
		


int main() {
	char highestChar;
	int reads;
	cin >> highestChar >> reads;
	for (char i='a'; i<=highestChar; i++) {
		letter newletter;
		alphabet.emplace(i, newletter);
	}
	string firstString, secondString;
	cin >> secondString;
	for (int i=0; i<reads-1; i++) {  //reads-1 because we already read 1 to initialize
		firstString = secondString;
		cin >> secondString;
		int smallestStringSize;
		if (firstString.length() >= secondString.length()) {
			smallestStringSize = secondString.length();
		} else {
			smallestStringSize = firstString.length();
		}
		
		int j=0;
		bool hintFound = false;
		while (!hintFound && j<smallestStringSize) {
			if (firstString[j] != secondString[j]) {
				alphabet[firstString[j]].followers.emplace(secondString[j]);
				alphabet[secondString[j]].numPredecessors+=1;
				hintFound = true;
			}
			j++;	
		}
	}

	/*
	for (char i='a'; i<=highestChar; i++) {
		cout << "Stuff for character " << i << ":";
		letter currletter = alphabet[i];
		for (set<char>::iterator it = alphabet[i].followers.begin(); it != alphabet[i].followers.end(); it++) {
			cout << " " << *it;
		}
		cout << "numPredecessors: "<<alphabet[i].numPredecessors;
		cout << endl;
	}
	*/
	int numRoots = 0;
	char root;
	char i='a';
	while (numRoots < 2 && i <= highestChar) {
		if (alphabet[i].numPredecessors == 0) {
			root = i;
			numRoots+=1;
		}
		i++;
	}
	
	if (numRoots == 0) {
		cout << "IMPOSSIBLE";
		return 0;
	} else if (numRoots > 1) {
		cout << "AMBIGUOUS";
		return 0;
	}
	
	//initialization for root depth
	alphabet[root].depth = 0;
	findDepth(root, 1);

	/*
	for (char i='a'; i<=highestChar; i++) {
		cout << "Stuff for character " << i << ":";	
		cout << "depth: "<<alphabet[i].depth;
		cout << endl;
	}
	*/

	
	if (loop) {
		cout << "IMPOSSIBLE";
		return 0;
	}
	string answer = buildFinalAlphabet(highestChar);
	if (answer == "*") cout << "AMBIGUOUS";
	else cout << answer;
	//start looping through hints from root
}

		

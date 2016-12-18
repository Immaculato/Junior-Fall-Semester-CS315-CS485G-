#include <iostream>
#include <string>
#include <vector>
#include <set>
#include<chrono>
#include <ctime>

using namespace std;

bool loop = false;

struct letter {
	vector<int> followers;
	int numPredecessors = 0;
	int depth=-1;
	bool visited = false;
};

letter* alphabet;


void findDepth(int root, int depth) {
	if (loop) return;
	int sizeFollowers = alphabet[root].followers.size();
	for (int i=0; i<sizeFollowers; i++) {
		int followerIndex = alphabet[root].followers[i];
		if (alphabet[followerIndex].depth < depth) alphabet[followerIndex].depth = depth;
		if (alphabet[followerIndex].visited) loop = true;
		alphabet[followerIndex].visited = true;
		findDepth(followerIndex, depth+1);
		alphabet[followerIndex].visited = false;
	}
}

string buildFinalAlphabet(int highestChar) {
	int index = 0;
	std::string finalString(highestChar, ' ');
	vector<int> depths;
	for (int i=0; i<highestChar; i++) {
		int depth = alphabet[i].depth;
		int sizeVector = depths.size();
		for (int j=0; j<sizeVector; j++) {
			if (depth == depths[j]) return "*";
		}
		depths.push_back(depth);
		finalString[alphabet[i].depth] = i+97;
	}
	return finalString;
}		


int main() {
	std::chrono::time_point<std::chrono::system_clock> start, end;

	char highestChar;
	int reads;
	cin >> highestChar >> reads;
	//this allocates a spot for each letter - i.e., 'd'=100 and 100-96=4 letters to represent
	alphabet = new letter[highestChar-96];
	string firstString, secondString;
	cin >> secondString;
	for (int i=0; i<reads-1; i++) {  //reads-1 because we already read 1 to initialize
		firstString = secondString;
		cin >> secondString;
		//find the size of the smallest string: we don't want to segfault
		int smallestStringSize;
		if (firstString.length() >= secondString.length()) {
			smallestStringSize = secondString.length();
		} else {
			smallestStringSize = firstString.length();
		}
		
		bool hintFound = false;

		
		//now, run through the parallel strings letter by letter until we find a difference (we should assume that there is one).
		int j=0;
		while (!hintFound && j!=smallestStringSize) {
			char firstChar = firstString[j];
			char secondChar = secondString[j];
			if (firstChar != secondChar) {
				alphabet[firstChar-97].followers.push_back(secondChar-97);
				alphabet[secondChar-97].numPredecessors++;
				hintFound = true;
			}
			j++;
		}
	}
	
	/*
	for (int i=0; i<highestChar-96; i++) {
		cout << (char)i+96 << " followers: ";
		for (int j=0; j<alphabet[i].followers.size(); j++) {
			cout << alphabet[i].followers[j] << endl;
		}
		cout << endl;
	}
	*/

	int numRoots = 0;
	int root;
	int i=0;
	//find the roots - note that if there are 0 roots its impossible, and if >1, ambiguous.
	while (i < highestChar-96 && numRoots<2) {
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
	start = std::chrono::system_clock::now();
	findDepth(root, 1);
	end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	std::cout  << elapsed_seconds.count()<< endl;
	if (loop) {
		cout << "IMPOSSIBLE";
		return 0;
	}
	start = std::chrono::system_clock::now();
	string answer = buildFinalAlphabet(highestChar-96);
	end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        end_time = std::chrono::system_clock::to_time_t(end);
	std::cout  << elapsed_seconds.count()<< endl;
	if (answer == "*") cout << "AMBIGUOUS";
	else cout << answer;
	//start looping through hints from root

}

		

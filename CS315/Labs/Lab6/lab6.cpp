//Name: Tristan Basil
//UVA Problem 469 - Wetlands of Florida


#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <ctype.h>

using namespace std;

int totwater = 0;
int sizegrid;
int sizegridx;
int sizegridy;

//simple struct to keep track of filled/visited status for backtracking
struct water {
	bool filled = false;
	bool visited = false;
};

//recursively backtracks to find total adjacent water
void findwater(water map[], int xpos, int ypos) {
	for (int i=ypos-1; i<=ypos+1; i++) {
		for (int j=xpos-1; j<=xpos+1; j++) {
			if (map[i*sizegridx+j].filled && !map[i*sizegridx+j].visited) {
				map[i*sizegridx+j].visited = true;
				totwater+=1;
				findwater(map, j, i);
			}
		}
	}	
}

//sets all modifiable grid locations to unvisited
void unvisitboard(water map[]) {
	for (int i=1; i<sizegridy-1; i++) {
		for (int j=1; j<sizegridx-1; j++) {
			map[i*sizegridx+j].visited=false;
		}
	}
}

void printboard(water map[]) {
	for (int i=0; i<sizegridx*sizegridy; i++) {
			if (map[i].filled) cout << "W ";
			else cout << "L ";
		}
}

int main() {
	int cases;
	cin >> cases;
	vector<string> answers;
	
	for (int i=0; i<cases; i++) {
	
	//if (i>0) cin.ignore();
	
	string line, firstline;
	cin >> firstline;
	int ypos;
	//note grid has 2 extra columns and rows at each end - this frames the data to prevent segfaults
	sizegridx = firstline.length() + 2;
	
	//fill appropriate locations according to input
	vector<string> lines;
	//lines.push_back(firstline);
	bool endofcases = false;
	cin.ignore();
	int k=-1;
	while (!endofcases) {
		k++;
		if (k==0) line = firstline;
		else getline(cin, line);
		endofcases = !(line[0] == 'W' | line[0] == 'L');
		if (!endofcases) lines.push_back(line);
	}
	sizegridy = lines.size()+2; //needs 2 extra
	int actualsize = sizegridx * sizegridy;
	water map[actualsize];
	
	for (int i=1; i<sizegridy-1; i++) {
		for (int j=1; j<sizegridx-1; j++) {
			if (lines[i-1][j-1] == 'W') map[i*sizegridx+j].filled = true;
		}
	}

	//printboard(map);
	
	
	vector<int> xpositions;
	vector<int> ypositions;
	bool done = false;
	int coords = 0;
	while(!done) {
		if (coords > 0) getline(cin, line);
		stringstream stream(line);
		if (line.empty()) {
			done = true;
		} else {
			coords++;
			int xpos, ypos;
			stream >> ypos;
			stream >> xpos;
			ypositions.push_back(ypos);
			xpositions.push_back(xpos);
		}
		/*
		cin >> ypos;
		if (!isalpha(ypos)) {
			cin >> xpos;
			xpositions.push_back(xpos);
			ypositions.push_back(ypos);
		} else {
			done = true;
		}
		*/
	}
	for (int i=0; i<coords; i++) {
		findwater(map, xpositions[i], ypositions[i]);
		answers.push_back(to_string(totwater));
		answers.push_back("\n");
		unvisitboard(map);
		totwater=0;
	}
	answers.push_back("\n");
	
	
	}
	answers.pop_back();
	for (int i=0; i<answers.size(); i++) {
		cout << answers[i];
	}
}
	

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>

using namespace std;

const int TOP_LEFT = 1;
const int TOP_RIGHT = 2;
const int BOTTOM_LEFT = 3;
const int BOTTOM_RIGHT = 4; 
const set<int> TOP_LEFT_INDEX = {1, 2, 5, 6};
const set<int> TOP_RIGHT_INDEX = {3, 4, 7, 8};
const set<int> BOTTOM_LEFT_INDEX = {9, 10, 13, 14};
const set<int> BOTTOM_RIGHT_INDEX = {11, 12, 15, 16};

static bool solved = false;

void printBoard(vector<char> sudokuBoard) {
	for (int i=1; i<17; i++) {
		cout << sudokuBoard[i] << " ";
		if (i%4==0) {
			cout << endl;
		}
	}
}

int determineCorner(int index) {
	if (TOP_LEFT_INDEX.find(index) != TOP_LEFT_INDEX.end()) return TOP_LEFT;
	if (TOP_RIGHT_INDEX.find(index) != TOP_RIGHT_INDEX.end()) return TOP_RIGHT;
	if (BOTTOM_LEFT_INDEX.find(index) != BOTTOM_LEFT_INDEX.end()) return BOTTOM_LEFT;
	if (BOTTOM_RIGHT_INDEX.find(index) != BOTTOM_RIGHT_INDEX.end()) return BOTTOM_RIGHT;
	return 0;
}

set<char> findCandidates(int index, vector<char> sudokuBoard) {
	set<char> matches;
	int row = ((index-1)/4);
	row++;
	int column = (index%4);
	if (column == 0) column=4;
	int quadrant = determineCorner(index);
	int rowStartI = 1+((row-1)*4);
	for (int i=rowStartI; i<rowStartI+4; i++) {
		if (sudokuBoard[i] != 'x') matches.insert(sudokuBoard[i]);
	}
	for (int i=column; i<column+13; i+=4) {
		if (sudokuBoard[i] != 'x') matches.insert(sudokuBoard[i]);
	}
	set<int>::iterator itr;
	switch (quadrant) {
		case 1: for(itr= TOP_LEFT_INDEX.begin(); itr != TOP_LEFT_INDEX.end(); itr++) {
			if (sudokuBoard[*itr] != 'x') matches.insert(sudokuBoard[*itr]);
			}
			break;
		case 2: for(itr= TOP_RIGHT_INDEX.begin(); itr != TOP_RIGHT_INDEX.end(); itr++) {
                        if (sudokuBoard[*itr] != 'x') matches.insert(sudokuBoard[*itr]);
                        }
			break;
		case 3: for(itr= BOTTOM_LEFT_INDEX.begin(); itr != BOTTOM_LEFT_INDEX.end(); itr++) {
                        if (sudokuBoard[*itr] != 'x') matches.insert(sudokuBoard[*itr]);
                        }
			break;
		case 4: for(itr= BOTTOM_RIGHT_INDEX.begin(); itr != BOTTOM_RIGHT_INDEX.end(); itr++) {
                        if (sudokuBoard[*itr] != 'x') matches.insert(sudokuBoard[*itr]);
                        }
			break;
	}

	//determine what possibilities are missing from those taken; these are the availible values.
	set<char> candidates;
	for (char i='1'; i<'5'; i++) {
		if (matches.find(i) == matches.end()) {
			candidates.insert(i);
		}
	}
	return candidates;
}

//starts at index=1 (current_cell=1).
void solveSudoku(vector<char> sudokuBoard, int index) {
	if (solved) return;
	if (index == 17) {
		printBoard(sudokuBoard);
		solved=true;
		return;
	}
	//if there is already a number provided, skip over it.
	if (sudokuBoard[index] != 'x') { 
		solveSudoku(sudokuBoard, index+1);
		return;
	}
	//if there is a blank (X), find the possible candidates.
	set<char> candidates = findCandidates(index, sudokuBoard);
	//if there are no candidates (c_index<c_num), back track by returning out.
	if (candidates.empty()) {
		return;
	}
	//if there is a candidate, update this candidate into a tentative solution,
	//and c_index+=1 (shown in the function call with index+1).
	set<char>::iterator itr;
	for (itr = candidates.begin(); itr != candidates.end(); itr++) {
		sudokuBoard[index] = *itr;
		//if the index is 16, we found a solution. print it, write it down,
		//then backtrack to find more (if possible).	
		if (index == 16) {
			printBoard(sudokuBoard);
			solved = true;
		} else {
		//if we aren't at the end, add 1 to the index and keep going.
			solveSudoku(sudokuBoard, index+1);
		}
	}
}
	
int main()  { 
	vector<char> sudokuBoard;
	sudokuBoard.push_back('0');
	for (int i=0; i<4; i++) {
		string inputline;
       		getline(cin, inputline);
		stringstream stream(inputline);
		for (int j=0; j<4; j++) {
			char testchar;
			stream >> testchar;
			sudokuBoard.push_back(testchar);
		}
	}	
	solveSudoku(sudokuBoard, 1);
	//cout << "Iterations: " << iterations << endl;
}

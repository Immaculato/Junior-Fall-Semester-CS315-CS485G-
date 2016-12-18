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
const set<int> LARGE_TOP_LEFT_INDEX = {1, 2, 3, 10, 11, 12, 19, 20, 21};
const set<int> LARGE_TOP_MIDDLE_INDEX = {4, 5, 6, 13, 14, 15, 22, 23, 24};
const set<int> LARGE_TOP_RIGHT_INDEX = {7, 8, 9, 16, 17, 18, 25, 26, 27};
const set<int> LARGE_MIDDLE_LEFT_INDEX = {28, 29, 30, 37, 38, 39, 46, 47, 48};
const set<int> LARGE_MIDDLE_MIDDLE_INDEX = {31, 32, 33, 40, 41, 42, 49, 50, 51};
const set<int> LARGE_MIDDLE_RIGHT_INDEX = {34, 35, 36, 43, 44, 45, 52, 53, 54};
const set<int> LARGE_BOTTOM_LEFT_INDEX = {55, 56, 57, 64, 65, 66, 73, 74, 75};
const set<int> LARGE_BOTTOM_MIDDLE_INDEX = {58, 59, 60, 67, 68, 69, 76, 77, 78};
const set<int> LARGE_BOTTOM_RIGHT_INDEX = {61, 62, 63, 70, 71, 72, 79, 80, 81};

static bool largeSudokuSolved = false;
static int solutions = 0;
static int iterations = 0;

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
        iterations++;
        if (index == 17) {
                printBoard(sudokuBoard);
                solutions++;
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
                        solutions++;
                } else {
                //if we aren't at the end, add 1 to the index and keep going.
                        solveSudoku(sudokuBoard, index+1);
                }
        }
}

void printLargeBoard(vector<char> sudokuBoard) {
	for (int i=1; i<82; i++) {
		cout << sudokuBoard[i] << " ";
		if (i%9==0) {
			cout << endl;
		}
	}
}

int determineLargeSection(int index) {
        if (LARGE_TOP_LEFT_INDEX.find(index) != LARGE_TOP_LEFT_INDEX.end()) return 1;
        if (LARGE_TOP_MIDDLE_INDEX.find(index) != LARGE_TOP_MIDDLE_INDEX.end()) return 2;
        if (LARGE_TOP_RIGHT_INDEX.find(index) != LARGE_TOP_RIGHT_INDEX.end()) return 3;
        if (LARGE_MIDDLE_LEFT_INDEX.find(index) != LARGE_MIDDLE_LEFT_INDEX.end()) return 4;
	if (LARGE_MIDDLE_MIDDLE_INDEX.find(index) != LARGE_MIDDLE_MIDDLE_INDEX.end()) return 5;
	if (LARGE_MIDDLE_RIGHT_INDEX.find(index) != LARGE_MIDDLE_RIGHT_INDEX.end()) return 6;
	if (LARGE_BOTTOM_LEFT_INDEX.find(index) != LARGE_BOTTOM_LEFT_INDEX.end()) return 7;
	if (LARGE_BOTTOM_MIDDLE_INDEX.find(index) != LARGE_BOTTOM_MIDDLE_INDEX.end()) return 8;
	if (LARGE_BOTTOM_RIGHT_INDEX.find(index) != LARGE_BOTTOM_RIGHT_INDEX.end()) return 9;
        return 0;
}

set<char> findLargeCandidates(int index, vector<char> sudokuBoard) {
        set<char> matches;
        int row = ((index-1)/9);
        row++;
        int column = (index%9);
        if (column == 0) column=9;
        int section = determineLargeSection(index);
        int rowStartI = 1+((row-1)*9);
        for (int i=rowStartI; i<rowStartI+9; i++) {
                if (sudokuBoard[i] != 'x') matches.insert(sudokuBoard[i]);
        }
        for (int i=column; i<column+73; i+=9) {
                if (sudokuBoard[i] != 'x') matches.insert(sudokuBoard[i]);
        }
        set<int>::iterator itr;
        switch (section) {
                case 1: for(itr= LARGE_TOP_LEFT_INDEX.begin(); itr != LARGE_TOP_LEFT_INDEX.end(); itr++) {
                        if (sudokuBoard[*itr] != 'x') matches.insert(sudokuBoard[*itr]);
                        }
                        break;
                case 2: for(itr= LARGE_TOP_MIDDLE_INDEX.begin(); itr != LARGE_TOP_MIDDLE_INDEX.end(); itr++) {
                        if (sudokuBoard[*itr] != 'x') matches.insert(sudokuBoard[*itr]);
                        }
                        break;
                case 3: for(itr= LARGE_TOP_RIGHT_INDEX.begin(); itr != LARGE_TOP_RIGHT_INDEX.end(); itr++) {
                        if (sudokuBoard[*itr] != 'x') matches.insert(sudokuBoard[*itr]);
                        }
                        break;
                case 4: for(itr= LARGE_MIDDLE_LEFT_INDEX.begin(); itr != LARGE_MIDDLE_LEFT_INDEX.end(); itr++) {
                        if (sudokuBoard[*itr] != 'x') matches.insert(sudokuBoard[*itr]);
                        }
                        break;
		case 5: for(itr= LARGE_MIDDLE_MIDDLE_INDEX.begin(); itr != LARGE_MIDDLE_MIDDLE_INDEX.end(); itr++) {
                        if (sudokuBoard[*itr] != 'x') matches.insert(sudokuBoard[*itr]);
                        }
                        break;
		case 6: for(itr= LARGE_MIDDLE_RIGHT_INDEX.begin(); itr != LARGE_MIDDLE_RIGHT_INDEX.end(); itr++) {
                        if (sudokuBoard[*itr] != 'x') matches.insert(sudokuBoard[*itr]);
                        }
                        break;
		case 7: for(itr= LARGE_BOTTOM_LEFT_INDEX.begin(); itr != LARGE_BOTTOM_LEFT_INDEX.end(); itr++) {
                        if (sudokuBoard[*itr] != 'x') matches.insert(sudokuBoard[*itr]);
                        }
                        break;
		case 8: for(itr= LARGE_BOTTOM_MIDDLE_INDEX.begin(); itr != LARGE_BOTTOM_MIDDLE_INDEX.end(); itr++) {
                        if (sudokuBoard[*itr] != 'x') matches.insert(sudokuBoard[*itr]);
                        }
                        break;
		case 9: for(itr= LARGE_BOTTOM_RIGHT_INDEX.begin(); itr != LARGE_BOTTOM_RIGHT_INDEX.end(); itr++) {
                        if (sudokuBoard[*itr] != 'x') matches.insert(sudokuBoard[*itr]);
                        }
                        break;
        }

        //determine what possibilities are missing from those taken; these are the availible values.
        set<char> candidates;
        for (char i='1'; i<='9'; i++) {
                if (matches.find(i) == matches.end()) {
                        candidates.insert(i);
                }
        }
        return candidates;
}

//this is almost exactly the same process as with the smaller board,
//just with bigger numbers. the total amount of solutions is not provided
//because the number can get VERY large.
void solveLargeSudoku(vector<char> sudokuBoard, int index) {
	if (largeSudokuSolved) return;
        if (index == 82) {
                printLargeBoard(sudokuBoard);
                largeSudokuSolved = true;
                return;
        }
        if (sudokuBoard[index] != 'x') {
                solveLargeSudoku(sudokuBoard, index+1);
                return;
        }
        set<char> candidates = findLargeCandidates(index, sudokuBoard);
        if (candidates.empty()) {
                return;
        }
        set<char>::iterator itr;
        for (itr = candidates.begin(); itr != candidates.end(); itr++) {
                sudokuBoard[index] = *itr;
                if (index == 81) {
                        printLargeBoard(sudokuBoard);
                        largeSudokuSolved = true;
                } else {
                        solveLargeSudoku(sudokuBoard, index+1);
                }
        }
}

int main()  {
	cout << "Press 1 to run in 2x2 mode with extra credit,\n"
	     << "or 2 to run in 3x3 mode." << endl;
	int userChoice;
	cin >> userChoice;
	cin.ignore();
	if (userChoice==2) {
		vector<char> sudokuBoard;
	        sudokuBoard.push_back('0');
       	 	for (int i=0; i<9; i++) {
                	string inputline;
              	 	getline(cin, inputline);
                	stringstream stream(inputline);
                	for (int j=0; j<9; j++) {
                        	char testchar;
                        	stream >> testchar;
	                        sudokuBoard.push_back(testchar);
        	        }
       		 }
        	 solveLargeSudoku(sudokuBoard, 1);
	} else if (userChoice == 1) {
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
        	solutions = 0;
        	solveSudoku(sudokuBoard, 1);
        	cout << "Total solutions: " << solutions << endl;
	}
}

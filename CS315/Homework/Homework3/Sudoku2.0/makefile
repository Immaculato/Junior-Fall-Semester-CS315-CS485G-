Sudoku : Sudoku.o
	g++ -o $@ Sudoku.o
Sudoku.o : Sudoku.cpp
	g++ -std=c++11 -c $?
SudokuLarge : SudokuLarge.o
	g++ -o $@ SudokuLarge.o
SudokuLarge.o : SudokuLarge.cpp
	g++ -std=c++11 -c $?
clean:
	rm -i *.o

README for SUDOKU ------
By Tristan Basil
CS315-002
Extra credit included*****

VERSION 1.1:
-Extended 9x9 sudoku version to include backtrack step count and option to specify number of solutions to print

**************************

Included files:
-README
-Sudoku.cpp
-SudokuLarge.cpp
-makefile

Description:
    This zip contains 2 programs: 'Sudoku', which addresses the main homework 3 problem,
and 'SudokuLarge', which addresses the extra credit parts of the homework 3 program and
allows user to see backtracked step count and to specify the number of solutions to find.

Compilation:
 1. Use the command `make Sudoku` to create the executable "Sudoku", which uses 2x2
    Sudoku boards as input. Integers 1-4 act as preset values and 'x's serve as blanks.
 2. Use the command `make SudokuLarge` to create the executable "SudokuLarge", which
    uses 2x2 or 3x3 Sudoku boards as input. Integers 1-4 in the first case, or 1-9 in
    the latter act as preset values and 'x's serve as blanks in both modes.

Output:
 1. Running the 2x2 executable "Sudoku" will print 1 possible solution to the
    provided 2x2 puzzle.
 2. Running the extra credit 2x2/3x3 executable "SudokuLarge" allows the user to choose
    whether they want to run in 2x2 mode by initially inputting a "1", or to run in
    3x3 mode by initially putting in a "2". In the first mode, solving a 2x2 sudoku
    puzzle will print all possible solutions to the provided puzzle, alongside the
    number of them. In the second 3x3 mode, the user may first specify the number of
    solutions they wish to print, and then the puzzle. The program will print as many
    solutions as specified, or if the specified amount could not be reached, the solutions
    that were found (with a line saying so). Additionally, the number of backtrack
    steps taken in the recursive backtracking function will be printed. This serves as
    the total amount of backtracks taken to find all provided solutions.

************

Known bugs/issues:
 1. If the provided configuration is impossible to solve, the output of the program is 
    undetermined. In order to ensure a valid solution, please provide a valid puzzle.
    This applies to both the 2x2 and 3x3 executables.
 2. If the user specifies the value '0' for the number of solutions they wish to find
    in the SudokuLarge 3x3 board, it will print all possible solutions to the problem.
    Depending on the provided configuration, this could take a VERY long time.

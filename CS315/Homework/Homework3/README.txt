README for SUDOKU ------
By Tristan Basil
CS315-002
Extra credit included*****

Included files:
-README
-Sudoku.cpp
-SudokuLarge.cpp
-makefile

Description:
    This zip contains 2 programs: 'Sudoku', which addresses the main homework 3 problem,
and 'SudokuLarge', which addresses the extra credit parts of the homework 3 program.

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
    number of them. Solving a 3x3 sudoku puzzle will print just 1 possible solution to
    the provided puzzle, due to complexity.

************

Known bugs/issues:
 1. If the provided configuration is impossible to solve, the output of the program is undetermined. In order to ensure a valid solution, please provide a valid puzzle. This applies to both the 2x2 and 3x3 executables.

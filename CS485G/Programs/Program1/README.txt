Programming Assignment 1 - CS485G-001
Name: Tristan Basil
Date: 09/08/2016

Files included in .zip:
	-prog1.c  -- source code
	-Makefile -- makefile provided by Dr. Raphael Finkel for Programming Assignment 1
	-README.txt


Description:
	
	This program is designed to read a binary file, formatted in 4-byte chunks, and
display the binary in various different formats. The first 4-byte chunk in the binary file
should represent an integer n of the amount of 4-byte chunks that follow it. If a file
is successfully read, the user can then elect to do any of the following by typing the
corresponding command:
	
	-Print element n in decimal -- [pd n]
	-Print element n in hexadecimal -- [pd n]
	-Print element n in octal -- [po n]
	-Print the lowest order byte of element n -- [b0 n]
	-Print the second byte of element n -- [b1 n]
	-Print the third byte of element n -- [b2 n]
	-Print the fourth byte of element n -- [b3 n]
	-Print the sum of elements n and m, ignoring overflow -- [+ n m]
	-Print the bitwise and of elements n and m -- [& n m]
	-Print the bitwise or of elements n and m -- [| n m]
	-Print the bitwise xor of elements n and m -- [^ n m]
	-Print the result of right-shifting element n by m bits -- [> n m]
	-Print the result of left-shifting element n by m bits -- [< n m]
	-Quit -- [q]

	Note: All commands will print in hexadecimal if not stated otherwise above.

Testing:

	The testing process for this project involved generating a checklist of input to
manually input into the program. This was a comprehensive list that involved many
different combinations of valid input, edge cases, and invalid input. I am not aware
of any bugs in the current version of this program.
	

How to compile and run program:

	The command "make prog1" should be run to compile the program. This will create
the executable `prog1`, which can be run with a binary file name as an argument. This
binary file should be formatted as described in the "Description" section of this README.


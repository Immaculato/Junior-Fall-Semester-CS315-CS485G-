//course: CS216-00x
//Project: Lab Assignment 3
//Date: 01/30/2016
//Purpose: Read data from two input files which passes in from command line arguments
//         and sort the integers in a non-decreasing order
//         using Insertion Sorting and Bubble Sorting algorithms respectively
//	   Display the sequence before and after sorting
//Author: Yi Pike

#include <iostream>

using namespace std;

int main(int argc, char** argv)  {
	if (argc != 1)
   	{
		cout << "Does not require command line arguments." << endl;
        	return 1;
	}
	for (int i=1; i<101; i++) {
		if (i%5==0 && i%3==0) {
			cout << "FizzBuzz" << endl;
		} else if (i%5==0) {
			cout << "Buzz" << endl;
		} else if (i%3==0) {
			cout << "Fizz" << endl;
		} else {
			cout << i << endl;
		}
	}
}

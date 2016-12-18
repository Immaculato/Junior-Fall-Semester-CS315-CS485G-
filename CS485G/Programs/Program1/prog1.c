//course: CS485G-001
//Project: Program 1
//Date: 09/08/2016
//Purpose: Read data from an binary input file in chunks and interpret the binary in
//         various ways, including hex, octal, and unsigned integers.
//Author: Tristan Basil
//Works Cited:
//	-Various code snippets provided by Dr. Raphael Finkel, particularly for reading
//		binary chunks of data and various scan methods for read data
// 	-Stack overflow user "jxh" for ideas on how to verify whether a string is numeric

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Constant used to avoid literal " "
#define SPACE " "

//User-facing strings
#define ERROR_INVALID_FILE "Please enter a valid file name.\n"
#define ERROR_UNEXPECTED_CHAR "Unexpected character input.\n"
#define ERROR_INDEX_OUT_OF_RANGE "Index is out of range.\n"
#define ERROR_INDEX_INVALID "Index is invalid.\n"
#define ERROR_INVALID_B_COMMAND "Invalid byte command.\n"
#define ERROR_INVALID_COMMAND "Unrecognized command.\n"

//This will return false if a string such as "-1" is passed in --
//luckily, negative indexes are not accepted by this program anyways.
int isNumericString(char* string) {
	int stringEndIndex = strlen(string)-1;
	//We want this to work for strings without \n at the end too.
	if (string[strlen(string)-1] != '\n') stringEndIndex = strlen(string); 
	int i=0;
	for (i=0; i<stringEndIndex; i+=1) {
		if (!isdigit(string[i])) return 0;
	}
	return -1;
}

//Pushes over the string according to byte index.
//Usage: isolateByte(integer, 3) would push over the third byte to
//the first position, so it can be printed easily. Note that whatever
//byte it being moved should be masked beforehand.
int isolateByte(int unsigned integer, int byteIndex) {
	int i=0;
	for (i=0; i<(byteIndex*2); i+=1) integer = integer >> 4;
	return integer;	
}

int main( int argc, char *argv[] )
{
	//Program should accept 1 parameter: the name of the file.
	if ( argc != 2 )
	{
		printf( "usage: %s FILENAME\n", argv[0] );
		return 1;
	}

	//Attempt to open the file.
	FILE *file;
	file=fopen(argv[1], "r");
	//If the file could not be opened,
	if (file == NULL) {
		//End the program and tell the user a valid name is needed.
		printf(ERROR_INVALID_FILE);
		return 1;
	}
	
	int sizeOfFile = -1;
	//Knowing we have a valid file, read the first chunk for the size of the file.
	fread(&sizeOfFile, sizeof(int), 1, file);
	//Allocate space accordingly, and read the bytes.
	int fileBytes[sizeof(int)*sizeOfFile];
	fread(fileBytes, sizeof(int), sizeOfFile, file);	
	fclose(file);
	
	//Operate until the user stops manually.
	while (1) {
		char unparsedCommand[20]; 
		int firstIndex, secondIndex = -1;
		char *userCommand, *firstIndexString, *secondIndexString;

		//Get the user input.
		fgets(unparsedCommand, 20, stdin);
		userCommand = strtok(unparsedCommand, SPACE);

		//Parse the user input and perform each command accordingly.
		//Note that each command checks for valid input and index bounds specific
		//to their use

		//command: pd
		if (memcmp(userCommand, "pd", 2)==0) {
			firstIndexString = strtok(NULL, SPACE);
			if (isNumericString(firstIndexString)) {
				firstIndex = atoi(firstIndexString);
				if (firstIndex > sizeOfFile-1 || firstIndex < 0) {
					printf(ERROR_INDEX_OUT_OF_RANGE);
					return 1;
				}
			} else {
				printf(ERROR_INDEX_INVALID);
				return 1;
			}
			printf("%u\n", fileBytes[firstIndex]);
	
		//command: px
		} else if (memcmp(userCommand, "px", 2) == 0) {
			firstIndexString = strtok(NULL, SPACE);
			if (isNumericString(firstIndexString)) {
				firstIndex = atoi(firstIndexString);
				if (firstIndex > sizeOfFile-1 || firstIndex < 0) {
					printf(ERROR_INDEX_OUT_OF_RANGE);
					return 1;
				}
			} else {
				printf(ERROR_INDEX_INVALID);
				return 1;
			}
			printf("%x\n", fileBytes[firstIndex]);

		//command: po
		} else if (memcmp(userCommand, "po", 2)== 0) {
			firstIndexString = strtok(NULL, SPACE);
			if (isNumericString(firstIndexString)) {
				firstIndex = atoi(firstIndexString);
				if (firstIndex > sizeOfFile-1 || firstIndex < 0) {
					printf(ERROR_INDEX_OUT_OF_RANGE);
					return 1;
				}
			} else {
				printf(ERROR_INDEX_INVALID);
				return 1;
			}
			printf("%o\n", fileBytes[firstIndex]);
		
		//command: b* (because b commands are very similar and involve more
		//processing, all b commands are handled here)
		} else if (userCommand[0] == 'b') {	
			firstIndexString = strtok(NULL, SPACE);	
			int unsigned value;
			if (strlen(userCommand) != 2 || !isdigit(userCommand[1])) {
				printf(ERROR_INVALID_B_COMMAND);
				return 1;
			}
			if (isNumericString(firstIndexString)) {
				firstIndex = atoi(firstIndexString);
				if (firstIndex > sizeOfFile-1 || firstIndex < 0) {
					printf(ERROR_INDEX_OUT_OF_RANGE);
					return 1;
				}
			} else {
				printf(ERROR_INDEX_INVALID);
				return 1;
			}
			if(userCommand[1] == '0') {
				value = fileBytes[firstIndex] & 0x000000ff;
				//byte is already at the end position
			} else if(userCommand[1] == '1') {
				value = fileBytes[firstIndex] & 0x0000ff00;
				value = isolateByte(value, 1);
			} else if(userCommand[1] == '2') {
				value = fileBytes[firstIndex] & 0x00ff0000;
				value = isolateByte(value, 2);
			} else if(userCommand[1] == '3') {
				value = fileBytes[firstIndex] & 0xff000000;
				value = isolateByte(value, 3);
			} else { 
				printf(ERROR_INVALID_B_COMMAND);
				return 1;
			}
			printf("%x\n", value);
		
		//command: +
		} else if (userCommand[0] == '+') {
			firstIndexString = strtok(NULL, SPACE);
			secondIndexString = strtok(NULL, SPACE);
			if (isNumericString(firstIndexString) &&
			    isNumericString(secondIndexString)) {
				//get ints
				firstIndex = atoi(firstIndexString);
				secondIndex = atoi(secondIndexString);
				if ((firstIndex > sizeOfFile-1 || firstIndex < 0) ||
				   (secondIndex > sizeOfFile-1 || secondIndex < 0)) {
					printf(ERROR_INDEX_OUT_OF_RANGE);
					return 1;
				}
			} else {
				printf(ERROR_INDEX_INVALID);
				return 1;
			}

			int value = fileBytes[firstIndex]+fileBytes[secondIndex];
			printf("%x\n", value);
		
		//command: &
		} else if (userCommand[0] == '&') {
			firstIndexString = strtok(NULL, SPACE);
			secondIndexString = strtok(NULL, SPACE);
			if (isNumericString(firstIndexString) &&
			    isNumericString(secondIndexString)) {
				//get ints
				firstIndex = atoi(firstIndexString);
				secondIndex = atoi(secondIndexString);
				if ((firstIndex > sizeOfFile-1 || firstIndex < 0) ||
				   (secondIndex > sizeOfFile-1 || secondIndex < 0)) {
					printf(ERROR_INDEX_OUT_OF_RANGE);
					return 1;
				}
			} else {
				printf(ERROR_INDEX_INVALID);
				return 1;
			}

			int value = fileBytes[firstIndex]&fileBytes[secondIndex];
			printf("%x\n", value);
		
		//command: |
		} else if (userCommand[0] == '|') {
			firstIndexString = strtok(NULL, SPACE);
			secondIndexString = strtok(NULL, SPACE);
			if (isNumericString(firstIndexString) &&
			    isNumericString(secondIndexString)) {
				//get ints
				firstIndex = atoi(firstIndexString);
				secondIndex = atoi(secondIndexString);
				if ((firstIndex > sizeOfFile-1 || firstIndex < 0) ||
				   (secondIndex > sizeOfFile-1 || secondIndex < 0)) {
					printf(ERROR_INDEX_OUT_OF_RANGE);
					return 1;
				}
			} else {
				printf(ERROR_INDEX_INVALID);
				return 1;
			}

			int value = fileBytes[firstIndex]|fileBytes[secondIndex];
			printf("%x\n", value);

		//command: ^
		} else if (userCommand[0] == '^') {
			firstIndexString = strtok(NULL, SPACE);
			secondIndexString = strtok(NULL, SPACE);
			if (isNumericString(firstIndexString) &&
			    isNumericString(secondIndexString)) {
				//get ints
				firstIndex = atoi(firstIndexString);
				secondIndex = atoi(secondIndexString);
				if ((firstIndex > sizeOfFile-1 || firstIndex < 0) ||
				   (secondIndex > sizeOfFile-1 || secondIndex < 0)) {
					printf(ERROR_INDEX_OUT_OF_RANGE);
					return 1;
				}
			} else {
				printf(ERROR_INDEX_INVALID);
				return 1;
			}

			int value = fileBytes[firstIndex]^fileBytes[secondIndex];
			printf("%x\n", value);

		//command: >
		} else if (userCommand[0] == '>') {
			firstIndexString = strtok(NULL, SPACE);
			secondIndexString = strtok(NULL, SPACE);
			if (isNumericString(firstIndexString) &&
			    isNumericString(secondIndexString)) {
				//get ints
				firstIndex = atoi(firstIndexString);
				secondIndex = atoi(secondIndexString);
				if ((firstIndex > sizeOfFile-1 || firstIndex < 0)) {
					printf(ERROR_INDEX_OUT_OF_RANGE);
					return 1;
				}
			} else {
				printf(ERROR_UNEXPECTED_CHAR);
				return 1;
			}

			int value = fileBytes[firstIndex]>>secondIndex;
			printf("%x\n", value);

		//command: <
		} else if (userCommand[0] == '<') {
			firstIndexString = strtok(NULL, SPACE);
			secondIndexString = strtok(NULL, SPACE);
			if (isNumericString(firstIndexString) &&
			    isNumericString(secondIndexString)) {
				//get ints
				firstIndex = atoi(firstIndexString);
				secondIndex = atoi(secondIndexString);
				if ((firstIndex > sizeOfFile-1 || firstIndex < 0)) {
					printf(ERROR_INDEX_OUT_OF_RANGE);
					return 1;
				}
			} else {
				printf(ERROR_UNEXPECTED_CHAR);
				return 1;
			}

			int value = fileBytes[firstIndex]<<secondIndex;
			printf("%x\n", value);

		//command: q
		} else if (userCommand[0] == 'q' || userCommand[0] == 'Q') {
			return 0;
		
		//invalid command
		} else {
			printf(ERROR_INVALID_COMMAND);
			return 1;
		}
	}	
	return 0;
}


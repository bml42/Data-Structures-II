/*
 * Designed by: Benjamin M. Linam
 * functions.c
 * Project5
 *
 */

#include"functions.h"

void PrintReverse(int length) { //recursive function that utilizes activation records on stack to output the string S in reverse

	if (length >= strlen(S)) {
		return;
	} else {

		PrintReverse(length + 1);
		printf("%c", S[length]);
	}
}

int offsetLength(int stringLengths[], int fileLocation, int digitNum) {
	int counter, sum = 0;
	int diff;
	for (counter = 0; counter < fileLocation; counter++)
		sum += stringLengths[counter];
	if (digitNum == 1) { //less than 10, -3
		diff = -3;
	} else if (digitNum == 2) { //more than 10 less than 100, -2
		diff = -2;
	} else if (digitNum == 3) { //100<x1000, -1
		diff = -1;
	} else
		diff = 0;

	return ((sum + sizeof(int) + (sizeof("\n") * (fileLocation + 1))) + diff); //factors in the number of newline characters in the file
}


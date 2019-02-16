/*
 * Designed by: Benjamin M. Linam
 * Part2.c
 * Project5
 *
 */
#include"Part2.h"

void Part2() {
	/******************PART2************************/
	printf("\nPart2\n\n\n");

	file = fopen("multipleSequences.txt", "r");
	if (!file) {
		printf("Unable to open file");

	}
	fscanf(file, "%s", string3); //number of sequences
	digitNum = strlen(string3);
	numofSequences = atoi(string3);

	int stringLengths[numofSequences]; //array of strlens for each string in file
	int offsets[numofSequences]; //array containing offsets for each string in file
	char simArray[numofSequences][numofSequences]; //array that will contain similarities between strings

	for (i = 0; i < numofSequences; i++) { //initializes simArray to be all '-' to be replaced during algorithm section
		for (j = 0; j < numofSequences; j++) {
			simArray[i][j] = '-';
		}
	}

	/***********THIS LOOP FINDS LENGTHS OF STRINGS*************/
	for (counter = 0; counter < numofSequences; counter++) { //loop that executes read and array fill operation
		fscanf(file, "%s", string3);
		stringLengths[counter] = strlen(string3); //stores lengths for each string in file to stringlengths[]
		offsets[counter] = offsetLength(stringLengths, counter, digitNum); //determines offset location for each string
	}
	fclose(file);

	/***********************ALGORITHM******************/
	//first step to determine LCS length
	//there will be a loop here to conditionally fill the simArray
	for (x = 0; x < numofSequences; x++) {
		for (y = x + 1; y < numofSequences; y++) {
			/****************direct access************************/
			file = fopen("multipleSequences.txt", "r");
			if (!file) {
				printf("Unable to open file");

			}

			for (i = 0; i < LONGSTRING; i++) { //initializes whole arrays to 0
				LCSarray1[i] = 0;
				LCSarray2[i] = 0;
			}
			memset(string3, 0, strlen(string3)); //strings would not empty between fscanf's, this fixes that problem
			memset(string4, 0, strlen(string4));

			fseek(file, offsets[x], SEEK_SET); //seeks to offset location in file for desired strings
			fscanf(file, "%s", string3);
			fseek(file, offsets[y], SEEK_SET);
			fscanf(file, "%s", string4);

			fclose(file);
			//file access ended
			/***************LCS length calculation**********/
			for (i = 1; i <= stringLengths[x]; i++) {
				for (j = 1; j <= stringLengths[y]; j++) {

					if (string3[i - 1] == string4[j - 1]) {
						LCSarray2[j] = LCSarray1[j - 1] + 1;
						//diagonal
					} else {
						if (LCSarray1[j] >= LCSarray2[j - 1]) {
							LCSarray2[j] = LCSarray1[j];
							//up
						} else {
							LCSarray2[j] = LCSarray2[j - 1];
							//left
						}
					}

					if (j == stringLengths[y]) {
						for (k = 0; k < stringLengths[y]; k++)
							LCSarray1[k] = LCSarray2[k]; //copies values of array 2 to array 1 to repeat LCS operations
					}
				}
			}
			LCSlength = LCSarray2[stringLengths[y]]; //last value in last array is LCS length
			if (strlen(string3) < strlen(string4)) { //second string is longer than first string
				shortStringLength = strlen(string3);
				strcpy(shortString, string3);
				strcpy(longString, string4);
			} else if (strlen(string3) > strlen(string4)) { //first string is longer than second string
				shortStringLength = strlen(string4);
				strcpy(shortString, string4);
				strcpy(longString, string3);
			} else {
				shortStringLength = strlen(string3); //both strings are same length, goes with first string
				strcpy(shortString, string3);
				strcpy(longString, string4);
			}

			/******************lenperc calculation***************/

			lenPerc = (100
					- (100
							* ((float) strlen(shortString)
									/ (float) strlen(longString))));

			/*******************lcsperc calculation**************/

			LCSPerc = (100 * ((float) LCSlength / (float) strlen(shortString)));

			/******************FILL SIMARRAY*******************/
			if (lenPerc <= 10 && LCSPerc >= 80) { //HIGH SIM : LENPERC <=10 LCSPERC >=80
				simArray[x][y] = 'H';
			} else if (lenPerc <= 20 && LCSPerc >= 60) { //MED SIM : LENPERC <=20 LCSPERC >=60
				simArray[x][y] = 'M';
			} else if (lenPerc <= 40 && LCSPerc >= 50) { //LOW SIM : LENPERC <=40 LCSPERC >=50
				simArray[x][y] = 'L';
			} else { //NO SIM
				simArray[x][y] = 'D';
			}

		}
	}
	/*************SIMARRAY OUTPUT**************/
	printf("\t");
	for (i = 0; i < numofSequences; i++)
		printf("%d\t", i + 1);
	printf("\n");
	for (i = 0; i < numofSequences; i++) {
		printf("%d\t", i + 1);
		for (j = 0; j < numofSequences; j++) {
			printf("%c\t", simArray[i][j]);
		}
		printf("\n");
	}
}

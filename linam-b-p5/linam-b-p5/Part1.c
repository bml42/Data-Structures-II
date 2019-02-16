/*
 * Designed by: Benjamin M. Linam
 * Part1.c
 * Project5
 *
 */

#include"Part1.h"

void Part1() {
	/***********PART1**************/
	printf("\nPart1\n\n");

	count = 0;
	file = fopen("twoSequences.txt", "r");
	if (!file) {
		printf("file does not exist");

	}
	fscanf(file, "%s", string1);
	fscanf(file, "%s", string2);
	m = strlen(string1);
	n = strlen(string2);
	int c[m + 1][n + 1]; //c array for LCS

	/***********LCS***************/ //algorithm provided for use in this project
	for (i = 1; i <= m; i++) //I adjusted algorithm to run for x/y[0...n-1] instead of [1...n]
		c[i][0] = 0;
	for (j = 0; j <= n; j++)
		c[0][j] = 0;
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) {
			if (string1[i - 1] == string2[j - 1]) {
				c[i][j] = c[i - 1][j - 1] + 1;
				//diagonal
			} else {
				if (c[i - 1][j] >= c[i][j - 1]) {
					c[i][j] = c[i - 1][j];
					//up
				} else {
					c[i][j] = c[i][j - 1];
					//left
				}
			}
		}
	}
	/***********c array output****************/
	printf("\nC ARRAY\n");
	printf("\t");
	for (i = 0; i <= m; i++)
		printf("%c\t", string2[i]);
	printf("\n");
	for (i = 0; i <= m; i++) {
		if (i == 0)
			printf("  ");
		else
			printf("%c ", string1[i - 1]);
		for (j = 0; j <= n; j++) {

			printf("%d\t", c[i][j]);

		}
		printf("\n");
	}
	printf("\n");

	/******************Subsequence************************/
	i = m;	//variables containing the length of string1 and string2
	j = n;

	while (c[i][j] > 0) {
		if (string2[j - 1] == string1[i - 1]) { //diagonal
			S[count] = string1[i - 1];
			i--;
			j--;

			count++;
		} else if (string2[j - 1] != string1[i - 1]
				&& c[i][j - 1] > c[i - 1][j]) { //left

			j--;

		} else if (string2[j - 1] != string1[i - 1]
				&& c[i][j - 1] == c[i - 1][j]) { //up

			i--;
		}

	}
	/*****************Subsequence Output*****************/

	printf("String 1: %s\n", string1);
	printf("String 2: %s\n", string2);
	printf("LCS of %s and %s: ", string1, string2);
	PrintReverse(0);//uses recursive function call to output string in correct order
	printf("\n");
	fclose(file);
}

/*
 * Designed by: Benjamin M. Linam
 * Part2.h
 * Project5
 *
 */

#ifndef PART2_H_
#define PART2_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"functions.h"

#define LONGSTRING 1000
#define MAXSTRING 15


FILE *file;

void Part2(void);

int numofSequences;

int digitNum; //this will record the number of digits in the first line of text file
int i, j, x, y; //loop variables used for algorithm portion
int k; //counter used for LCS length determination
int counter; //maintains a count of how many strings have been scanned in
char string3[LONGSTRING]; //these two strings will be compared as well as finding LCS length
char string4[LONGSTRING];
char shortString[LONGSTRING];//shorter comparison string
char longString[LONGSTRING];//longer comparison string
int LCSarray1[LONGSTRING]; //these two arrays will be used for LCS operations on the above strings
int LCSarray2[LONGSTRING];
int LCSlength; //length of LCS
int shortStringLength;//shorter string length
float lenPerc;//percent difference between short string and lcs length
float LCSPerc;//percent difference between LCS length and short string

#endif /* PART2_H_ */

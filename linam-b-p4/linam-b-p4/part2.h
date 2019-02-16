/*
 * part2.h
 *
 *  Created on: Nov 16, 2017
 *      Author: Benjamin
 */

#ifndef PART2_H_
#define PART2_H_

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include"functions.h"

#define FILEMAX 4
#define FILENAMEMAX 7
#define DSNAMEMAX 10
#define DSNUMMAX 4
#define INTERVALMAX 99

struct files {

	int batchNum[FILEMAX]; //number of batches
	int itemperBatch[FILEMAX]; //items per batch
	double badbatchPercent[FILEMAX]; //percent of batches that are bad
	double baditemPercent[FILEMAX]; //percent of items that are bad in a bad batch
	int itemstoSample[FILEMAX]; //this is also used for exponent in final calculations
	float base[FILEMAX];
	float pFailure[FILEMAX];
	float pGood[FILEMAX];
	float percentDetected[FILEMAX]; //number of bads found divided by total bads
} results;

FILE *fp; //used to read from c#.txt files
FILE *fpwrite; //used during ds#.txt data writing
FILE *fpread; //used during ds#.txt data analysis

void part2(void);

#endif /* PART2_H_ */

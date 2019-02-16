/*
 * Designed by: Benjamin M. Linam
 * Part2.c
 * Project4
 *
 */

#include "part2.h"

void part2() {
	int i, j, k, a, counter, x = 0; //counting variables
	char filename[FILENAMEMAX] = "c1.txt";
	char fname[DSNAMEMAX]; //name of output ds#.txt files
	char fnum[DSNUMMAX]; //# for ds#.txt files, increments up to batchNum
	int numtomakeBad; //frequency of bad batch creation
	float badnumBatches; //number of bad batches per set of batches
	char good = 'g';
	char bad = 'b';
	int interval; //number used to determine change in 'a' for random sampling
	int badChips; //number of times a bad chip is written to a ds# file
	int badBatch; //number of bad ds files created
	int chip; //test variable used for determining if random chip is good or bad
	int badFound; //number of bad batches found by analysis loop
	char* chipArray; //array that temporarily stores char values taken in from ds#.txt files during data analysis

	for (i = 0; i < FILEMAX; i++) { //this loop will move through each c file and perform appropriate operations
		fp = fopen(filename, "r"); //reads from text file.  If read completes, code executes, else return to menu
		if (!fp) {

			printf("Unable to open file!");

		}
		fscanf(fp, "%d", &results.batchNum[x]);
		fscanf(fp, "%d", &results.itemperBatch[x]);
		fscanf(fp, "%lf", &results.badbatchPercent[x]);
		fscanf(fp, "%lf", &results.baditemPercent[x]);
		fscanf(fp, "%d", &results.itemstoSample[x]);
		fclose(fp);

		badnumBatches = results.batchNum[x]
				* (float) (results.badbatchPercent[x] / 100);
		numtomakeBad = floor(results.batchNum[x] / badnumBatches); //determines how frequently to make a bad batch

		results.base[x] = (100 - results.baditemPercent[x]) / 100;
		results.pFailure[x] = pow(results.base[x], results.itemstoSample[x]); //statistical data used in final output
		results.pGood[x] = 1 - results.pFailure[x];

		badBatch = 0; //resets num of bad batches per file to 0
		printf("\nRunning:\n");
		printf("\tNumber of batches of items:\t\t\t%d\n", results.batchNum[x]);
		printf("\tNumber of items in each batch:\t\t\t%d\n",
				results.itemperBatch[x]);
		printf("\tPercentage of batches containing bad items:\t%.0lf%%\n",
				results.badbatchPercent[x]);
		printf("\tPercentage of items that are bad in a bad set:\t%.0lf%%\n",
				results.baditemPercent[x]);
		printf("\tItems sampled from each set:\t\t\t%d\n\n",
				results.itemstoSample[x]);
		printf("Generating data sets:\n");

		/***********************DS FILE CREATION LOOP**************************/
		//creates .txt files and stores values 'b' or 'g' to represent good or bad chips in a given batch
		for (j = 0; j < results.batchNum[x]; j++) { //creates the names for each output "ds" file
			badChips = 0;
			sprintf(fnum, "%d", j);
			strcpy(fname, "ds");
			strcat(fname, fnum);
			strcat(fname, ".txt");

			fpwrite = fopen(fname, "w");

			if (j % numtomakeBad == 0) { //run loop to randomly create bad chips as bad batch is located
				badBatch++;
				for (k = 0; k < results.itemperBatch[x]; k++) { //loop runs for number of items in batch and records 'g' or 'b' one per line

					if (randomNum(INTERVALMAX) <= results.baditemPercent[x]) { //returns random number from 0->99 and compares it to bad batch percent
						badChips++;
						fprintf(fpwrite, "%c\r\n", bad); //if rand number is on interval 0 -> bad percent, writes b in file

					} else {

						fprintf(fpwrite, "%c\r\n", good); //if rand number is not on interval, 'g' is recorded
					}

				}
				printf(
						"\tCreate bad set batch # %d, totBad = %d total = %d badpct = %.0lf\n", //indicates what batch number is bad and how many bad chips it has
						j, badChips, results.itemperBatch[x],
						results.baditemPercent[x]);

			} else { //continue to run simulation and set all chips to 'g'
				for (k = 0; k < results.itemperBatch[x]; k++)
					fprintf(fpwrite, "%c\r\n", good);
			}
			fclose(fpwrite); //closes current ds file

		}
		printf("\tTotal bad sets = %d\n\n", badBatch);
		/***********************DS FILE ANALYSIS LOOP**************************/
		//analyzes created .txt files and randomly selects values to determine if batches are bad
		printf("Analyzing Data Sets:\n");
		badFound = 0;

		for (j = 0; j < results.batchNum[x]; j++) { //reads through each output "ds" file
			sprintf(fnum, "%d", j);
			strcpy(fname, "ds");
			strcat(fname, fnum);
			strcat(fname, ".txt");
			fpread = fopen(fname, "r");
			chipArray = malloc(results.itemperBatch[x] * sizeof(char)); //must save memory for array as it will vary from file to file

			for (k = 0; k < results.itemperBatch[x]; k++)
				fscanf(fpread, " %c", &chipArray[k]); //reads for number of times k = items per batch, values into chipArray for sampling

			counter = 0;
			a = 0; //these counting values will be used again, makes sure that there is nothing left stored in it
			chip = 0;
			interval = results.itemperBatch[x] / results.itemstoSample[x];
			do { //this loop will sample elements stored in chipArray, if bad chip is found, batch is marked as bad
				if (chipArray[a] == 'b') {

					chip++;
					break;

				} else {
					counter++;
					a += interval;
				}

			} while (counter != results.itemstoSample[x]); //itemstoSample has been met or bad chip found

			if (chip == 1) { //bad chip was found

				printf("\tbatch #%d is bad\n", j);
				badFound++;
			}

			free(chipArray); //frees memory saved for chipArray for reuse during next execution
			fclose(fpread);

		}
		results.percentDetected[x] = ((float) badFound / badBatch) * 100; //determines percentage of found bad batches to total bad
		printf("\nBase = %f exponent = %d\n", results.base[x],
				results.itemstoSample[x]);
		printf("P(failure to detect bad item) = %.6f\n", results.pFailure[x]);
		printf("P(batch is good) = %.6f\n", results.pGood[x]);
		printf("Percentage of bad batches detected = %.0f%%\n\n",
				results.percentDetected[x]);
		filename[1]++; //changes the file name by "c1" + 1
		x++;
	}
	/*********************SUMMARY********************/
	//outputs all results gathered throughout run of program
	printf("Summary:\n\n");
	for (x = 0; x < FILEMAX; x++) {
		printf("Run %d:\n", x + 1);
		printf("Number of batches of items:\t\t\t%d\n", results.batchNum[x]);
		printf("Number of items in each batch:\t\t\t%d\n",
				results.itemperBatch[x]);
		printf("Percentage of batches containing bad items:\t%.0lf%%\n",
				results.badbatchPercent[x]);
		printf("Percentage of items that are bad in a bad set:\t%.0lf%%\n",
				results.baditemPercent[x]);
		printf("Items sampled from each set:\t\t\t%d\n",
				results.itemstoSample[x]);
		printf("Base = %f exponent = %d\n", results.base[x],
				results.itemstoSample[x]);
		printf("P(failure to detect bad item) = %.6f\n", results.pFailure[x]);
		printf("P(batch is good) = %.6f\n", results.pGood[x]);
		printf("Percentage of bad batches detected = %.0f%%\n\n\n",
				results.percentDetected[x]);
	}

}

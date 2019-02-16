/*
 * Designed by: Benjamin M. Linam
 * Part1.c
 * Project4
 *
 */
#include "part1.h"

void part1() {

	//start of read operation
	fp = fopen("SimParameters.dat", "rb"); //reads from dat file.  If read completes, code executes, else return to menu
	if (!fp) {

		printf("Unable to open file!");

	} else {
		fread(&simNum, sizeof(int), 1, fp); //first value stored in dat file is number of simulations

		for (counter = 0; counter < simNum; counter++) { //loop reads values from file until simNum is reached

			fread(&categoryMax, sizeof(int), 1, fp); //category max is second value stored in dat file

			freqVector = malloc(categoryMax * sizeof(int)); //need to save memory for frequency vector as size will change per simulation
			for (i = 0; i < categoryMax; i++)
				fread(&freqVector[i], sizeof(int), 1, fp); //reads values to frequency vector
			fread(&eventNum, sizeof(int), 1, fp); //next value to read after freq vector will be event num

			for (i = 0, sum = 0; i < categoryMax; i++) //sums values stored in frequency array
				sum += freqVector[i];

			probArray = malloc(categoryMax * sizeof(double)); //need to save memory for each array since they will change
			eventTable = malloc(categoryMax * sizeof(int));

			/*********determines expected result*********/
			for (j = 0; j < categoryMax; j++) //initialize event table values to zero
				eventTable[j] = 0;

			for (i = 0; i < categoryMax; i++)
				probArray[i] = (double) freqVector[i] / sum; //probability array stores the percentages of occurrence for each category

			for (i = 0, Exp = 0; i < categoryMax; i++) //calculates expected total
				Exp += probArray[i] * i;

			/***********simulation evaluation**********/
			for (i = 0; i < eventNum; i++) { //evaluates random results for eventNum events

				eventResult = randomNum(categoryMax);
				for (j = 0; j < categoryMax; j++) { //searches through eventTable and if value is found, occurrence increments

					if (eventResult == j) {
						eventTable[j]++;
					}
				}

			}
			for (j = 0, sum = 0; j < categoryMax; j++) //determines simulation result
				sum += (eventTable[j] * j);

			Sim = (double) sum / (double) eventNum;
			Error = fabs(Sim - Exp) / Exp;
			//outputs all solved values to console
			printf("\nSimulation %d\n\n", counter + 1);
			printf("\tN: %d\n", eventNum);
			printf("\tSimulated Result: %.2lf\n", Sim);
			printf("\tExpected Result: %.2lf\n", Exp);
			printf("\tError percent: %.5lf\n", Error);
			free(probArray); //must free memory used by arrays as size will vary between simulations
			free(freqVector);
			free(eventTable);
			printf("\n"); //all values will be changed, program moves on to next simulation values stored sequentially in dat file
		}
		fclose(fp); //end of read
	}
}

/*
 * main.c
 * Benjamin Linam
 *
 */
//I NEED AN S ARRAY THAT HOLDS PERM VALUES||FIRST VALUE IN ARRAY IS 0->N->0, THEN RUN PERM FUNCTION - complete
//Need to sum the path lengths for each tour, increment through tour array and sum tourtable#[i][i++] until i++ == 0 - complete
//honestly need to protect elite tours from mutpercent, cannot be more than 50% or the like
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"functions.h"

int main() {

	int citynum, tournum, i, counter;
	struct timespec genStart, genEnd, genTot;
	clockid_t cid = 0;

	IN = fopen("cityWeights.txt", "r");
	i = 0;

	while (!feof(IN)) {
		fscanf(IN, "%lf", &edgevalues[i]);
		i++;
	}
	fclose(IN);

	do { //loop will continue until 20 or less cities are chosen
		printf("Enter number of cities to run: ");
		scanf("%d", &citynum);
		if (citynum > 20)
			printf("ERROR: Cannot run simulation for more than 20 cities\n");
	} while (citynum > 20);

	printf("Enter number of individual tours in a given generation: ");
	scanf("%d", &tournum);
	printf("Enter number of generations to run: ");
	scanf("%d", &gennum);
	do { //loop will continue until there is room for 2 elite tours
		printf(
				"Enter the percentage of a generation that should be comprised of mutations: ");
		scanf("%f", &mutpercent);
		solvepercentMutation(tournum);
		if (tournum - tourstoMutate < 2) {
			printf(
					"ERROR: Decrease mutation percentage.  Must leave room for elite tours.\n");
		}
	} while (tournum - tourstoMutate < 2);

	solvepercentMutation(tournum);
	init1DArrays(citynum);          //both initialize all arrays to 0
	init2DArrays(tournum, citynum);
	storeEdgeWeights(citynum);		//stores edgeweights in adjmatrix
	fillPrimeTable(citynum, tournum);	//stores tourtable1 with tours
	printf(
			"\nCALCULATING OPTIMAL COST VIA BRUTE FORCE ALGORITHM. PLEASE WAIT.\n\n");

	bruteforce(citynum); //this function will run through every possible tour (n-1)! and print the cost of the best tour


	//this is where loop should start, decrements counter until it reaches 0
	clock_gettime(cid, &genStart);
	OnetoTwo = 0;
	for (counter = 1; counter <= gennum; counter++) {
		if (OnetoTwo == 1) {
			updatetourLengths2(tournum, citynum);

			findElites2(citynum, tournum);

			OnetoTwo = 0;
		} else if (OnetoTwo == 0) {
			updatetourLengths1(tournum, citynum);

			findElites1(citynum, tournum);

			OnetoTwo = 1;
		}
	}

	clock_gettime(cid, &genEnd);
	genTot.tv_sec = genEnd.tv_sec - genStart.tv_sec;  //genetic time calculation
	genTot.tv_nsec = genEnd.tv_nsec - genStart.tv_nsec;
	if (genTot.tv_nsec < 0) {
		genTot.tv_sec--;
		genTot.tv_nsec += 1000000000;
	}

	if (gennum % 2 == 0) {
		printf("The best cost at %d generations of %d cities = %.2lf\n", gennum,
				citynum, tourLengths1[0]);
	}
	if ((gennum + 1) % 2 == 0) {
		printf("The best cost at %d generations of %d cities = %.2lf\n", gennum,
				citynum, tourLengths2[0]);
	}
	printf("Genetic algorithm took %ld.%09ld seconds to complete\n",
			genTot.tv_sec, genTot.tv_nsec);
	if (gennum % 2 == 0) {
		printf("Percent of optimal = %.2lf%%\n",(Besttour/tourLengths1[0])*100);
	}
	if ((gennum + 1) % 2 == 0) {
		printf("Percent of optimal = %.2lf%%\n",((Besttour/tourLengths2[0]))*100);
	}

	return 0;
}

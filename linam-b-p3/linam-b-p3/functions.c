/*
 * functions.c
 *
 *  Created on: Nov 2, 2017
 *      Author: Benjamin
 */
#include"functions.h"

void solvepercentMutation(int n) {
	tourstoMutate = (n * (mutpercent / 100));
}

void init1DArrays(int n) {
	int i;
	for (i = 0; i < ArrayMax; i++) { //initializes sArray and tourLengths1|2 to 0s
		sArray[i] = 0;
		tourLengths1[i] = 0;
		tourLengths2[i] = 0;
	}
	for (i = 0; i < n; i++)
		sArray[i] = i;
}

void init2DArrays(int n, int m) {

	int i, j;
	for (i = 0; i < CITYMAX; i++) { //this loop initializes the values in the adj matrix to 0

		for (j = 0; j < CITYMAX; j++)
			adjmatrix[i][j] = 0;

	}
	for (i = 0; i < n; i++) { //this loop initializes the values in the tour tables to 0

		for (j = 0; j < m + 1; j++) {

			tourtable1[i][j] = 0;
			tourtable2[i][j] = 0;

		}

	}

}
void fillPrimeTable(int n, int m) { //this will fill the prime generation table that does not count as first generation
	int i, j;
	for (i = 0; i < m; i++) {
		//printsArray(n);
		for (j = 0; j < n; j++)
			tourtable1[i][j] = sArray[j];

		perm(n);
	}
}

void displayAdjacencyMatrix(int n) {
	int i, j;
	for (i = 0; i < n; i++) //This portion of code outputs the values stored in the adjacency matrix
		printf("\t%d", i);

	printf("\n\n");

	for (i = 0; i < n; i++) {

		printf("%d\t", i);

		for (j = 0; j < n; j++)
			printf("%.2lf\t", adjmatrix[i][j]);

		printf("\n");
	}
	printf("\n");
}

void displayTourTables(int n, int m) { //citynum tournum

	int i, j;

	printf("Tour table 1\n");
	for (i = 0; i < m; i++) { //this portion of code outputs values in tourtable1

		printf("Tour %d: \t", i + 1);

		for (j = 0; j < n + 1; j++)
			printf("%d\t", tourtable1[i][j]);

		printf("\n");
	}
	printf("\n");

	printf("Tour table 2\n");
	for (i = 0; i < m; i++) { //this portion of code outputs values in tourtable2

		printf("Tour %d: \t", i + 1);

		for (j = 0; j < n + 1; j++)
			printf("%d\t", tourtable2[i][j]);

		printf("\n");
	}
	printf("\n");
}

void perm(int n) {

	int m, k, p, q, temp;
	m = n - 2;
	while (sArray[m] > sArray[m + 1])
		m = m - 1;
	k = n - 1;
	while (sArray[m] > sArray[k])
		k = k - 1;
	temp = sArray[m];	//
	sArray[m] = sArray[k];	//swap m and n
	sArray[k] = temp;	//
	p = m + 1;
	q = n - 1;
	while (p < q) {

		temp = sArray[p];	//
		sArray[p] = sArray[q];	//swap p and q
		sArray[q] = temp;	//
		p++;
		q--;
	}
}

void bruteforce(int n) {
	clockid_t cid = 0;
	Besttour = 999999;
	int m, k, p, q, i, j, temp;
	double sum;
	clock_gettime(cid, &bruteStart);
	for (i = 1; i < factorial(n - 1) - n; i++) {//use this for brute force method
		sum = 0;
		for (j = 0; j <= 1; j++) {
			if ((sArray[j] != 0) || (sArray[j + 1] != 0)) {
				sum += adjmatrix[sArray[j]][sArray[j + 1]];
			}
		}
		if (Besttour > sum) {
			Besttour = sum;
		}
		m = n - 2;
		while (sArray[m] > sArray[m + 1])
			m = m - 1;
		k = n - 1;
		while (sArray[m] > sArray[k])
			k = k - 1;
		temp = sArray[m];	//
		sArray[m] = sArray[k];	//swap m and n
		sArray[k] = temp;	//
		p = m + 1;
		q = n - 1;
		while (p < q) {

			temp = sArray[p];	//
			sArray[p] = sArray[q];	//swap p and q
			sArray[q] = temp;	//
			p++;
			q--;
		}
	}
	clock_gettime(cid, &bruteEnd);

	bruteTot.tv_sec = bruteEnd.tv_sec - bruteStart.tv_sec; //brute force time calculation
	bruteTot.tv_nsec = bruteEnd.tv_nsec - bruteStart.tv_nsec;
	if (bruteTot.tv_nsec < 0) {
		bruteTot.tv_sec--;
		bruteTot.tv_nsec += 1000000000;
	}
	printf(
			"The optimal cost determined by the brute force method for %d cities = %.2lf\n",
			n, Besttour);

	printf("Brute force algorithm took %ld.%09ld seconds to complete\n",
			bruteTot.tv_sec, bruteTot.tv_nsec);
}

void printsArray(int n) {	//n == citynum

	int i = 0;
	for (i = 0; i <= n; i++)
		printf("%i ", sArray[i]);

	printf("\n");
}

void displaytourLengtharrays(int n) {	//n == tournum

	int i = 0;
	printf("Distances in Tour Table 1:\t");
	for (i = 0; i < n; i++)
		printf("Tour %i\t", i + 1);

	printf("\n\t\t\t\t");
	for (i = 0; i < n; i++)
		printf("%.2lf\t", tourLengths1[i]);

	printf("\n");

	printf("Distances in Tour Table 2:\t");
	for (i = 0; i < n; i++)
		printf("Tour %i\t", i + 1);

	printf("\n\t\t\t\t");
	for (i = 0; i < n; i++)
		printf("%.2lf\t", tourLengths2[i]);

	printf("\n");

}

void updatetourLengths1(int n, int m) { //n = tournum m = citynum

	int i, j;
	double sum;
	for (i = 0; i < n; i++) {
		sum = 0;
		for (j = 0; j <= m; j++) {
			if ((tourtable1[i][j] != 0) || (tourtable1[i][j + 1] != 0)) {
				sum += adjmatrix[tourtable1[i][j]][tourtable1[i][j + 1]];
			}
		}
		tourLengths1[i] = sum;
	}

}

void updatetourLengths2(int n, int m) { //n = tournum m = citynum

	int i, j;
	double sum;
	for (i = 0; i < n; i++) {
		sum = 0;
		for (j = 0; j <= m; j++) {
			if ((tourtable2[i][j] != 0) || (tourtable2[i][j + 1] != 0)) {
				sum += adjmatrix[tourtable2[i][j]][tourtable2[i][j + 1]];
			}
		}
		tourLengths2[i] = sum;
	}

}

long factorial(int n) {				//returns factorial of n

	int c;
	long result = 1;

	for (c = 1; c <= n; c++)
		result = result * c;

	return result;

}
void storeEdgeWeights(int n) {
	int i, j, k = 0;
	for (i = 0; i < n; i++) { //this loop stores the edge weights in the adjacency matrix

		for (j = 0; j < n; j++) {
			if (i == j) {
				adjmatrix[i][j] = 0;
			} else {
				adjmatrix[i][j] = edgevalues[k];
				k++;
			}
		}
	}
	printf("\n");
}

void findElites1(int n, int m) { //n == citynum m == tournum
	int i, j, temp;
	int elitetour1 = 0;
	int elitetour2 = 0;
	int minvalue = tourLengths1[0];
	for (i = 0; i < m; i++) {				//finds tour number of first elite
		if (minvalue > tourLengths1[i]) {
			elitetour1 = i;
			minvalue = tourLengths1[i];

		}
	}

	if (elitetour1 == 0) { //reinits minvalue to something that is not in the location of elitetour1

		minvalue = tourLengths1[1];

	} else {
		minvalue = tourLengths1[0];
	}
	for (i = 0; i < m; i++) {				//finds tour number of second elite
		if (minvalue > tourLengths1[i]) {
			if (i != elitetour1) {
				elitetour2 = i;
				minvalue = tourLengths1[i];

			}
		}
	}

	for (i = 0; i < m; i++) {
		if (i == 0) {
			for (j = 0; j <= n; j++)
				tourtable2[i][j] = tourtable1[elitetour1][j]; //filling first elite
		} else if (i == 1) {
			for (j = 0; j <= n; j++)
				tourtable2[i][j] = tourtable1[elitetour2][j]; //filling second elite
		} else {
			for (j = 0; j <= n; j++)
				tourtable2[i][j] = tourtable1[elitetour2][j]; //filling remaining tours with second elite

			temp = tourtable2[i][(n - 1) / 2]; //this will swap the middle city with tourtable1[i][i] as i increments to n
			tourtable2[i][(n - 1) / 2] = tourtable2[i][i + 1];
			tourtable2[i][i + 1] = temp;

		}
	}
}

void findElites2(int n, int m) { //n == citynum m == tournum
	int i, j, temp;
	int elitetour1 = 0;
	int elitetour2 = 0;
	int minvalue = tourLengths2[0];
	for (i = 0; i < m; i++) {			//finds tour number of first elite
		if (minvalue > tourLengths2[i]) {
			elitetour1 = i;
			minvalue = tourLengths2[i];

		}

	}

	if (elitetour1 == 0) { //reinits minvalue to something that is not in the location of elitetour1

		minvalue = tourLengths2[1];

	} else {
		minvalue = tourLengths2[0];
	}
	for (i = 0; i < m; i++) {			//finds tour number of second elite
		if (minvalue > tourLengths2[i]) {
			if (i != elitetour1) {
				elitetour2 = i;
				minvalue = tourLengths2[i];

			}
		}

	}

	for (i = 0; i < m; i++) {
		if (i == 0) {
			for (j = 0; j <= n; j++)
				tourtable1[i][j] = tourtable2[elitetour1][j]; //filling first elite
		} else if (i == 1) {
			for (j = 0; j <= n; j++)
				tourtable1[i][j] = tourtable2[elitetour2][j]; //filling second elite
		} else {
			for (j = 0; j <= n; j++)
				tourtable1[i][j] = tourtable2[elitetour2][j]; //filling remaining tours with second elite
			temp = tourtable1[i][(n - 1) / 2]; //this will swap the middle city with tourtable1[i][i] as i increments to n
			tourtable1[i][(n - 1) / 2] = tourtable1[i][i + 1];
			tourtable1[i][i + 1] = temp;

		}
	}
}

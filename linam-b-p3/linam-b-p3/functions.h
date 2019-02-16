/*
 * functions.h
 *
 *  Created on: Nov 2, 2017
 *      Author: Benjamin
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define CITYMAX 20
#define ArrayMax 21
#define MostTours 100

int gennum, gencounter, tourstoMutate;
float mutpercent;
int OnetoTwo; //if = 0, table1 copies to table2, if = 1, table2 copies to table1
double Besttour;
struct timespec bruteStart, bruteEnd, bruteTot;

FILE* IN;
double adjmatrix[CITYMAX][CITYMAX];
int sArray[ArrayMax];
double tourLengths1[ArrayMax];
double tourLengths2[ArrayMax];
int tourtable1[MostTours][ArrayMax]; //these two tables will hold the tours for each generation, moving from 1 to 2 and so forth
int tourtable2[MostTours][ArrayMax];
double edgevalues[380];

long factorial(int n);
void printsArray(int n);
void init1DArrays(int n);
void perm(int n);
void displaytourLengtharrays(int n);
void init2DArrays(int n, int m);
void storeEdgeWeights(int n);
void fillPrimeTable(int n, int m);
void displayAdjacencyMatrix(int n);
void displayTourTables(int n, int m);
void updatetourLengths1(int n, int m);
void updatetourLengths2(int n, int m);
void findElites1(int n, int m);
void findElites2(int n, int m);
void solvepercentMutation(int n);
void bruteforce(int n);

#endif /* FUNCTIONS_H_ */

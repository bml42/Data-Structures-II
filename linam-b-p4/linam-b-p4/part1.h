/*
 * part1.h
 *
 *  Created on: Nov 16, 2017
 *      Author: Benjamin
 */

#ifndef PART1_H_
#define PART1_H_
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"functions.h"


int i, j, counter; //standard counters
double sum; //stores total frequency for each simulation
int simNum; //number of simulations to run
int categoryMax; //number of categories to choose from
int* freqVector; //frequency of occurrence for each category defined by historical data
int eventNum; //number of times top randomly generate numbers in the range of categoryMax
double* probArray; //stores the probability for each occurrence in frequency array
int* eventTable; //stores occurrences of each category during experiment evaluation
double Sim;
double Exp;
double Error;
int eventResult; //stores a single event result

FILE *fp;

void part1(void);

#endif /* PART1_H_ */

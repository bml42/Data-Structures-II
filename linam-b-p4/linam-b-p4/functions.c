/*
 * functions.c
 *
 *  Created on: Nov 16, 2017
 *      Author: Benjamin
 */
#include "functions.h"

int randomNum(int maxNum) { //produces a random number on interval with max number = maxNum

	int r;

	int range = maxNum + 1; //max number function can produce
	int buckets = RAND_MAX / range; //equally distributes values with probability
	int limit = buckets * range;

	do {

		r = rand();

	} while (r >= limit);
	return (r / buckets);

}

/*
 Designed by: Benjamin M. Linam
 main.c
 Project2

 This include the main of the program.
 */

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include"functions.h"

int main() {
	double lambda, mu, Po, L, W, Lq, Wq;
	int M, n;
	srand((unsigned) time(NULL));
	printf("Please enter number of arrivals to simulate: ");
	scanf("%d", &n);
	printf("Please enter average arrivals per time period: ");
	scanf("%lf", &lambda);
	printf("Please enter average number served per time period: ");
	scanf("%lf", &mu);
	printf("Please enter number of service channels: ");
	scanf("%d", &M); //all the above code prompts user for input data used to determine results of analytical model

	Po = getPo(lambda, mu, M);
	L = getL(lambda, mu, Po, M);
	W = getW(lambda, mu, Po, M);
	Lq = getLq(L, lambda, mu);
	Wq = getWq(W, mu); //function calls to determine the analytical values

	printf("Analytical Model Results\n");  //outputs analytical model results
	printf("Po = %.2lf\n", Po);
	printf("L = %.2lf\n", L);
	printf("W = %.2lf\n", W);
	printf("Lq = %.2lf\n", Lq);
	printf("Wq = %.2lf\n\n", Wq);
	printf("Simulation Results\n"); //the code below creates the 2 queues and displays the simulation results

	line p = createLine();  //creates first line of customers in FIFO
	queue PQ = createPriorityQueue(); //creates the priority queue
	processNextEvents(n, PQ, p, lambda, M, mu); //proccess q2q interactions
	freePriorityQueue(PQ); //frees remaining memory used for PQ
	freeQueue (p);
	//frees remaining memory used for FIFO
	return 0;
}

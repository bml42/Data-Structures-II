/*
 * Designed by: Benjamin M. Linam
 * functions.c
 * Project2
 *
 * This includes the function definitions for all functions used in Project2
 */

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include"functions.h"

double getPo(double lambda, double mu, int M) { //returns value for Po
	int i;
	double Po, denom1, denom2, denom3, sum;

	denom1 = 0;
	sum = 0;

	for (i = 0; i < M; i++) {

		sum = (1 / (double) factorial(i)) * pow((lambda / mu), i);
		denom1 = denom1 + sum;
	}
	denom2 = (1 / (double) factorial(M)) * pow((lambda / mu), M);
	denom3 = (M * mu) / ((M * mu) - lambda);
	Po = 1 / (denom1 + (denom2 * denom3));

	return Po;
}

double getL(double lambda, double mu, double Po, int M) { //returns value for L

	double num, den, L;

	num = lambda * mu * pow((lambda / mu), M);
	den = factorial(M - 1) * pow(((M * mu) - lambda), 2);
	L = ((num / den) * Po) + (lambda / mu);

	return L;

}

double getW(double lambda, double mu, double Po, int M) { //returns value for W

	double W, num, den;

	num = mu * pow((lambda / mu), M);
	den = factorial(M - 1) * pow(((M * mu) - lambda), 2);
	W = ((num / den) * Po) + (1 / mu);

	return W;
}

double getLq(double L, double lambda, double mu) { //returns value for Lq

	double Lq;

	Lq = L - (lambda / mu);

	return Lq;
}

double getWq(double W, double mu) { //returns value for Wq

	double Wq;

	Wq = W - (1 / mu);

	return Wq;
}

double getRho(double lambda, double mu, int M) { //returns value for Rho

	double Rho;

	Rho = lambda / (M * mu);

	return Rho;
}

long factorial(int x) { //function to calculate and return the factorial of variable x

	int i;
	long fact = 1;

	for (i = 1; i <= x; i++) {
		fact = fact * i;
	}

	return fact;

}

double GetNextRandomInterval(double avg) { //determines a random interval of time

	double intervalTime;
	float f = randnum();
	intervalTime = -1 * (1.0 / avg) * log(f);
	return intervalTime;

}

float randnum() { //returns a random number between 0 and 1

	double num = rand() / (double) RAND_MAX;
	if (num == 0.0) {

		num = num + 0.000000001;
	}
	return num;
}

void processNextEvents(int n, queue PQ, line p, double l, int M, double mu) { //processes each event until completion
	int i, j;
	double Po, W, Wq, Rho;
	double temp, temp2, total_servicetime;
	Po = 0;
	W = 0;
	Wq = 0;
	Customer tempCustomer = PQ->head;
	insertQueue(p, GetNextRandomInterval(l));
	for (i = 1; i < n; ++i) {
		insertQueue(p, GetNextRandomInterval(l) + getArrivalQueue(p, i - 1));
	}

	for (i = 0; i < n; ++i) {
		if (i < M) {
			temp = removeQueue(p);
			if (i == 0)
				Po = Po + temp;
			insertPriorityqueue(PQ, temp, temp,
					GetNextRandomInterval(mu) + temp);
			total_servicetime = total_servicetime + getDeparture(PQ->head)
					- getService(PQ->head);
		} else {
			tempCustomer = PQ->head;
			temp = removeQueue(p);
			for (j = 0; j < M; ++j)
				tempCustomer = tempCustomer->prevCust;
			temp2 = getDeparture(tempCustomer);
			if (temp2 < temp)
				insertPriorityqueue(PQ, temp, temp,
						GetNextRandomInterval(mu) + temp);
			else
				insertPriorityqueue(PQ, temp, temp2,
						GetNextRandomInterval(mu) + temp2);
			total_servicetime = total_servicetime + getDeparture(PQ->head)
					- getService(PQ->head);
		}
	}
	Po = (Po / getDeparture(PQ->head)) * 100;
	printf("Po = %.2lf\n", Po);
	tempCustomer = PQ->head;
	for (i = 0; i < n; ++i) {
		W = W + getDeparture(tempCustomer) - getArrival(tempCustomer);
		tempCustomer = getprevCust(tempCustomer);
	}
	W = W / n;
	printf("W = %.2lf\n", W);
	tempCustomer = PQ->head;
	for (i = 0; i < n; ++i) {
		Wq = Wq + getService(tempCustomer) - getArrival(tempCustomer);
		tempCustomer = getprevCust(tempCustomer);
	}
	Wq = Wq / n;
	printf("Wq = %.2lf\n", Wq);
	Rho = total_servicetime / getDeparture(PQ->head);
	printf("Rho = %.2lf\n", Rho);
}
line createLine() { //creation of assets to be used for FIFO queue
	int n;
	line p = malloc(sizeof *p);
	p->size = 20000;
	p->head = 0;
	p->tail = 0;
	p->arrivalTime = malloc(sizeof(double) * p->size);
	for (n = 0; n < p->size; ++n) {
		p->arrivalTime[n] = -1;
	}
	return p;
}
void insertQueue(line p, double q) { //inserts customer into FIFO
	p->arrivalTime[p->head % p->size] = q;
	p->head++;
}

double removeQueue(line p) { //removes customer from FIFO
	double temp = p->arrivalTime[p->tail % p->size];
	p->arrivalTime[p->tail % p->size] = 0;
	p->tail++;
	return temp;
}
double getArrivalQueue(line p, int location) {
	return p->arrivalTime[location];
}
void freeQueue(line p) {
	free(p);
}
queue createPriorityQueue() { //creates assets for Priority Queue
	queue p = malloc(sizeof *p);
	p->head = NULL;
	p->size = 0;

	return p;
}
void insertPriorityqueue(queue p, double a, double s, double d) { //inserts customer into priority queue
	Customer newCustomer, headCustomer;
	if (p->head == NULL) {
		newCustomer = createCustomer(a, s, d, NULL, NULL);
		newCustomer->nextCust = newCustomer;
		newCustomer->prevCust = newCustomer;
	} else {
		headCustomer = p->head;
		newCustomer = createCustomer(a, s, d, NULL, NULL);
		findprevCust(newCustomer, headCustomer);
		findnextCust(headCustomer, newCustomer);
	}
	p->head = newCustomer;
	++p->size;
}
void freePriorityQueue(queue p) {
	int n;
	Customer temp = p->head;

	if (p->head == NULL) {
		free(p);
		return;
	}

	for (n = 0; n < p->size; ++n) {
		freeCustomer(temp);
		temp = getprevCust(temp);
	}
	free(p);
}
void freeCustomer(Customer p) {
	free(p);
}
Customer createCustomer(double a, double s, double d, Customer next,
		Customer previous) { //creates customer for insertion into queue
	Customer p = malloc(sizeof *p);
	p->arrivalTime = a;
	p->startofServiceTime = s;
	p->departureTime = d;
	p->nextCust = next;
	p->prevCust = previous;

	return p;
}

void findnextCust(Customer p, Customer q) {
	p->nextCust = q;
}
void findprevCust(Customer p, Customer q) {
	p->prevCust = q;
}
double getArrival(Customer p) {
	return (p->arrivalTime);
}
double getService(Customer p) {
	return (p->startofServiceTime);
}
double getDeparture(Customer p) {
	return (p->departureTime);
}
Customer getprevCust(Customer p) {
	return (p->prevCust);
}

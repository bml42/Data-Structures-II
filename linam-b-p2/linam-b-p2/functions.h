/*
 * Designed by: Benjamin M. Linam
 * functions.h
 * Project2
 *
 * This file includes the function prototypes and structure creation
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

typedef struct Customer* Customer;  //defines these structs as types for use throughout the remainder of the program
typedef struct queue* queue;
typedef struct line* line;

struct Customer {

	double arrivalTime;
	double startofServiceTime;
	double departureTime;
	Customer nextCust;
	Customer prevCust;
};

struct line {
	double *arrivalTime;
	int head;
	int tail;
	int size;
};

struct queue {
	Customer head;
	int size;
};

long factorial(int x);
double getPo(double, double, int);
double getL(double, double, double, int);
double getW(double, double, double, int);
double getLq(double, double, double);
double getWq(double, double);
double getRho(double, double, int);
double GetNextRandomInterval(double);
double getArrival(Customer);
double getService(Customer);
double getDeparture(Customer);
double removeQueue(line);
double getArrivalQueue(line, int);
void insertPriorityQueue(queue, double, double, double);
void freePriorityQueue(queue);
void freeCustomer(Customer);
void findnextCust(Customer, Customer);
void findprevCust(Customer, Customer);
void processNextEvents(int, queue, line, double, int, double);
void insertQueue(line, double);
void freeQueue(line);
float randnum();
Customer createCustomer(double, double, double, Customer, Customer);
Customer getprevCust(Customer);
line createLine();
queue createPriorityQueue();

#endif /* FUNCTIONS_H_ */

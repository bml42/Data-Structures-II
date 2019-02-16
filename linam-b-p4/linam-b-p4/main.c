/*
 * Designed by: Benjamin M. Linam
 * main.c
 * Project4
 *
 */
#include "main.h"

int main() {
	srand(time(0));
	int exit; //escape code for do-while loop
	do {
		printf("Run Part 1? (1)\nRun Part 2? (2)\nExit Program (0)\nOption: ");
		scanf("%d", &exit);
		printf("\n");
		switch (exit) {

		case 1: //Part 1 includes reading from .dat file and running simulation and analytical model

			part1();

			break;

		case 2://Part 2 includes reading from .txt files, creating .txt files of chips and analyzing them to determine if select batches are "bad"

			part2();

			break;

		case 0://Ends program execution

			return 0;

		default://invalid input is recognized, menu will repeat

			printf("INVALID OPTION\n\n");

		}
	} while (exit != 0);
	return 0;
}


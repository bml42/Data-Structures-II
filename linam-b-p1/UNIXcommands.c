/******************************************************
Designed by: Benjamin M. Linam
UNIXcommands.c
Project1

This includes the main of the program..
Searches for input file "commands.txt and begins
program execution
******************************************************/
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include"prototypes.h"

int main() { //main function

	in = fopen("commands.txt", "r");
	if (in == NULL) {

		printf("File \"commands.txt\" could not be found\n");
		return 0;

	}

	createRootpath();
	evaluatecommands();

	return 0;
}

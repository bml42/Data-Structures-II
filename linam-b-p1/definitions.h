/******************************************************
Designed by: Benjamin M. Linam
definitions.h
Project1

This includes the defintions of all "global" variables
used by functions in the program
******************************************************/
#define LINE_LENGTH 100
#define MAX_TOKENS 5
#define TOKEN_LENGTH 50
#define NAMESIZE 30
#define DirectoryNum 100

char line[LINE_LENGTH];  			//input command line
char tokens[MAX_TOKENS][TOKEN_LENGTH];
char* directoryList[DirectoryNum]; //list of directory names used for pwd output

FILE *in;                          //file pointer which will represent read file

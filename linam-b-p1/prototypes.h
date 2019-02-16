/******************************************************
Designed by: Benjamin M. Linam
prototypes.h
Project1

This includes the prototypes of all functions used
as well as struct Node definition
******************************************************/
#ifndef PROTOTYPES_H_
#define PROTOTYPES_H_
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include"definitions.h"
//struct definition
struct Node {
	char name[NAMESIZE];
	char type;
	struct Node* parent;
	struct Node* rsibling;
	struct Node* lsibling;
	struct Node* child;
}*current, *temp1, *temp2, *source;

//prototypes
struct Node *CreateNewNode();
void tokenize();
int evaluatecommands();
void createRootpath();
void delete(struct Node*);
void whereis(char*, struct Node*);
void mkdir();
void addf();
void reverseCD();
void CD();
void pwd();
void ls();
void rm();
void mv();
void cp();

#endif /* PROTOTYPES_H_ */

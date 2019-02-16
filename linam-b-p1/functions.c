/******************************************************
Designed by: Benjamin M. Linam
functions.c
Project1

This includes the definitions of all usable functions
in the program
******************************************************/
#include "prototypes.h"

void tokenize() {     //takes in user command and separates each word into array
	int count = 0;
	char *DELIMITER = " \r\t\n";
	char *token;

	while (count < MAX_TOKENS) {

		strcpy(tokens[count], " ");
		count++;
	}
	count = 0;

	printf("$ ");

	fflush(stdout);

	fgets(line, LINE_LENGTH, in);

	token = strtok(line, DELIMITER);

	while (token != NULL) {

		strcpy(tokens[count], token);
		token = strtok(NULL, DELIMITER);
		count++;
	}
}

int evaluatecommands() {

	int i, commandTag;

	while (1) {

		for (i = 0; i < DirectoryNum; i++) {

			directoryList[i] = " ";

		}

		tokenize();

		commandTag = 0;

		i = 0;

		while (strcmp(tokens[i], " ") != 0) {

			printf("%s ", tokens[i]);

			i++;

		}
		printf("\n");

		//LIST COMMAND

		if (strcmp(tokens[0], "ls") == 0) {

			if (strcmp(tokens[1], " ") == 0) {
				ls();
			}
			if (strcmp(tokens[1], " ") != 0) {
				printf("Too many inputs...Illegal input for command \"ls\"\n");
			}
			commandTag = 1;

		}

		//MAKE DIRECTORY COMMAND

		if (strcmp(tokens[0], "mkdir") == 0) { //will have parameter (directory name)
			if (strcmp(tokens[1], " ") != 0 && strcmp(tokens[2], " ") == 0) {

				mkdir();
			}
			if (strcmp(tokens[1], " ") != 0 && strcmp(tokens[2], " ") != 0) {
				printf(
						"Too many inputs...Illegal input for command \"mkdir\"\n");
			}
			if (strcmp(tokens[1], " ") == 0) {
				printf("Did not recognize desired name for directory\n");
			}

			commandTag = 1;
		}

		//CD.. COMMAND

		if (strcmp(tokens[0], "cd..") == 0) {

			if (strcmp(tokens[1], " ") == 0) {
				reverseCD();
			}
			if (strcmp(tokens[1], " ") != 0) {
				printf(
						"Too many inputs...Illegal input for command \"cd..\"\n");
			}

			commandTag = 1;

		}

		//CD COMMAND

		if (strcmp(tokens[0], "cd") == 0) { //will have parameter (directory name)

			if (strcmp(tokens[1], " ") != 0 && strcmp(tokens[2], " ") == 0) {

				CD();
			}
			if (strcmp(tokens[1], " ") != 0 && strcmp(tokens[2], " ") != 0) {
				printf("Too many inputs...Illegal input for command \"cd\"\n");
			}
			if (strcmp(tokens[1], " ") == 0) {
				printf("Did not recognize desired name for directory\n");
			}
			commandTag = 1;

		}

		//PWD COMMAND

		if (strcmp(tokens[0], "pwd") == 0) {

			if (strcmp(tokens[1], " ") == 0) {

				pwd();
			}
			if (strcmp(tokens[1], " ") != 0) {
				printf("Too many inputs...Illegal input for command \"pwd\"\n");
			}

			commandTag = 1;

		}

		//ADD FILE COMMAND

		if (strcmp(tokens[0], "addf") == 0) { //will have parameter (file name)

			if (strcmp(tokens[1], " ") != 0 && strcmp(tokens[2], " ") == 0) {
				addf();
			}
			if (strcmp(tokens[1], " ") != 0 && strcmp(tokens[2], " ") != 0) {
				printf(
						"Too many inputs...Illegal input for command \"addf\"\n");
			}
			if (strcmp(tokens[1], " ") == 0) {
				printf("Did not recognize desired name for file\n");
			}
			commandTag = 1;
		}

		//MOVE FILE COMMAND

		if (strcmp(tokens[0], "mv") == 0) {	//will have parameters (old file)(new file)

			if (strcmp(tokens[1], " ") != 0 && strcmp(tokens[2], " ") != 0
					&& strcmp(tokens[3], " ") == 0) {       //execute

				mv();

			}

			if (strcmp(tokens[1], " ") != 0 && strcmp(tokens[2], " ") != 0
					&& strcmp(tokens[3], " ") != 0) {      //too many parameters

				printf("Too many inputs...Illegal input for command \"mv\"\n");
			}

			if (strcmp(tokens[1], " ") == 0 || strcmp(tokens[2], " ") == 0) { //not enough parameters

				printf("Did not recognize desired name for file(s)\n");

			}

			commandTag = 1;

		}

		//COPY FILE COMMAND

		if (strcmp(tokens[0], "cp") == 0) {	//will have parameters (old file)(new file)

			if (strcmp(tokens[1], " ") != 0 && strcmp(tokens[2], " ") != 0
					&& strcmp(tokens[3], " ") == 0) {       //execute
				printf(
						"cp command will be made available in \"UNIXcommands.c\" Version 2.0\n");
				//cp();

			}

			if (strcmp(tokens[1], " ") != 0 && strcmp(tokens[2], " ") != 0
					&& strcmp(tokens[3], " ") != 0) {      //too many parameters

				printf("Too many inputs...Illegal input for command \"cp\"\n");
			}

			if (strcmp(tokens[1], " ") == 0 || strcmp(tokens[2], " ") == 0) { //not enough parameters

				printf("Did not recognize desired name for file(s)\n");

			}
			commandTag = 1;

		}

		//REMOVE FILE COMMAND

		if (strcmp(tokens[0], "rm") == 0) {	//will have parameter (file name)

			if (strcmp(tokens[1], " ") != 0 && strcmp(tokens[2], " ") == 0) {
				rm();
			}
			if (strcmp(tokens[1], " ") != 0 && strcmp(tokens[2], " ") != 0) {
				printf("Too many inputs...Illegal input for command \"rm\"\n");
			}
			if (strcmp(tokens[1], " ") == 0) {
				printf("Did not recognize desired name for file\n");
			}
			commandTag = 1;

		}

		//WHERE IS FILE COMMAND

		if (strcmp(tokens[0], "whereis") == 0) { //will have parameter (file name)

			if (strcmp(tokens[1], " ") != 0 && strcmp(tokens[2], " ") == 0) {
				printf(
						"whereis command will be available in \"UNIXcommands.c\" Version 2.0\n");
				//whereis(tokens[1], source);
			}
			if (strcmp(tokens[1], " ") != 0 && strcmp(tokens[2], " ") != 0) {
				printf(
						"Too many inputs...Illegal input for command \"whereis\"\n");
			}
			if (strcmp(tokens[1], " ") == 0) {
				printf("Did not recognize desired name for file\n");
			}

			commandTag = 1;

		}

		//BYE COMMAND

		if (strcmp(tokens[0], "bye") == 0) {          //kills command prompt
			if (strcmp(tokens[1], " ") == 0) {

				fclose(in);
				return 0;
			}
			if (strcmp(tokens[1], " ") != 0) {
				printf("Too many inputs...Illegal input for command \"bye\"\n");
			}

		}
		if (commandTag == 0) {

			printf("%s is not a recognized command\n", tokens[i]);

		}

	}
	return (1);
}

struct Node *CreateNewNode() {          //creates blank directory or file
	struct Node *newNode = (struct Node*) malloc(sizeof(struct Node));
	newNode->parent = NULL;
	newNode->rsibling = NULL;
	newNode->lsibling = NULL;
	newNode->child = NULL;
	newNode->name[NAMESIZE] = ' ';
	newNode->type = ' ';
	return newNode;
}

void createRootpath() { //this will create a path from source: linam, to working directory: root
//from here temp1 will move right and left through siblings and current will always remain at the pwd
	current = CreateNewNode(); //temp2 will come into the picture when we start creating sibling nodes with mkdir()

	temp1 = CreateNewNode();

	strcpy(current->name, "linam");

	strcpy(temp1->name, "root");

	current->child = temp1;

	temp1->parent = current;

	current->type = 'D';

	temp1->type = 'D';

	source = current; //source will permanently point to linam as being source location

	current = temp1; //this is the beginning of node linkage, program will start with pwd and current/temp1 pointers at root

}

void delete(struct Node* p) {

	if (p != NULL) {

		delete(p->child);
		delete(p->rsibling);
		free(p);
	}			//having a problem with whereis ask coffey

}

void whereis(char* target, struct Node* locater) { //this function would have worked perfectly had I more time to work on it
	int i = 0;

	if (locater != NULL) {

		if (strcmp(locater->name, target) == 0) {
			printf("help");
			temp2 = locater;

			directoryList[i] = temp2->name;
			i++;
			while (temp2 != source) {
				while (temp2->lsibling != NULL) {
					temp2 = temp2->lsibling;

					if (temp2->parent != NULL) {

						temp2 = temp2->parent;
						directoryList[i] = temp2->name;
						i++;

					}
					if (temp2->lsibling == NULL && temp2->parent == NULL
							&& temp2 != source) {

						break;
					}
				}
			}
			i = 0;
			if (temp2 == source) {
				printf("at source");
				while (strcmp(directoryList[i + 1], " ") != 0) {
					i++;
				}

				while (i >= 0) {
					printf("%s/", directoryList[i]);
					i--;

				}
			}
			printf("\n");

		}
		if (temp2 != source) {
			whereis(target, locater->child);
			whereis(target, locater->rsibling);
			//printf("help");}
		}

	}
}

void mkdir() {

	int i = 0;

	temp2 = current->child;

	while (temp2 != NULL) {
		//searches for name in list
		if (strcmp(temp2->name, tokens[1]) == 0 && temp2->type == 'D') {

			printf("Directory name \"%s\" already used in Directory \"%s\"\n",
					tokens[1], current->name);

			break; //search name found

		}
		temp2 = temp2->rsibling;
	}

	if (temp2 == NULL) {

		if (current->child != NULL) {       //creates 'nth' directory in pwd

			temp2 = CreateNewNode();

			temp1->rsibling = temp2;

			temp2->lsibling = temp1;

			strcpy(temp2->name, tokens[i + 1]);

			temp2->type = 'D';

			temp1 = temp2; //creation of inchworm pointer, temp2 will always lead temp1

		}

		if (current->child == NULL) {       //creates first directory in pwd

			temp1 = CreateNewNode();

			temp1->parent = current;

			current->child = temp1;

			strcpy(temp1->name, tokens[i + 1]);

			temp1->type = 'D';

		}
		printf("%s\n", temp1->name);
	}

}

void addf() {

	int i = 0;

	if (current->child != NULL) {       //creates 'nth' directory in pwd

		temp2 = CreateNewNode();

		temp1->rsibling = temp2;

		temp2->lsibling = temp1;

		strcpy(temp2->name, tokens[i + 1]);

		temp2->type = 'F';

		temp1 = temp2; //creation of inchworm pointer, temp2 will always lead temp1

	}

	if (current->child == NULL) {       //creates first directory in pwd

		temp1 = CreateNewNode();

		temp1->parent = current;

		current->child = temp1;

		strcpy(temp1->name, tokens[i + 1]);

		temp1->type = 'F';

	}

}
void reverseCD() {              //cd..

	temp2 = current;

	while (temp2->lsibling != NULL) {

		temp2 = temp2->lsibling;

	}

	if (temp2->parent == NULL) {

		printf("There is no parent directory for \"%s\"\n", current->name);

	}
	if (temp2->parent != NULL) {

		current = temp2->parent;
		temp1 = current->child;
		while (temp1->rsibling != NULL) {
			temp1 = temp1->rsibling;
		}
		pwd();
	}

}

void CD() {

	temp2 = current->child;

	if (temp2 != NULL) {                                 //has child

		while (temp2 != NULL) {
			//searches for name in list
			if (strcmp(temp2->name, tokens[1]) == 0) {

				break; //search name found

			}
			temp2 = temp2->rsibling;

		}
	}

	if (temp2 == NULL) {

		printf("The directory name \"%s\" is invalid.\n", tokens[1]); //cannot find search name

	}

	if (temp2 != NULL) {

		if (strcmp(temp2->name, tokens[1]) == 0 && temp2->type == 'F') { //does not execute as found node is file

			printf(
					"File found with name \"%s\", but directory name \"%s\" is invalid.\n",
					tokens[1], tokens[1]);

		}

		if (strcmp(temp2->name, tokens[1]) == 0 && temp2->type == 'D') { //only executes if found node is directory
			if (temp2->child == NULL) {
				current = temp2;
				temp1 = temp2;
			}
			if (temp2->child != NULL) {

				current = temp2;
				temp1 = current->child;
				while (temp1->rsibling != NULL) {

					temp1 = temp1->rsibling;

				}

			}
			pwd();
		}
	}
}

void pwd() {

	int i = 0;

	temp2 = current;
	directoryList[i] = temp2->name;
	i++;
	while (temp2 != source) {
		while (temp2->lsibling != NULL) {
			temp2 = temp2->lsibling;
		}
		if (temp2->parent != NULL) {

			temp2 = temp2->parent;
			directoryList[i] = temp2->name;
			i++;

		}
		if (temp2->parent == NULL) {

			break;
		}
	}
	i = 0;
	while (strcmp(directoryList[i + 1], " ") != 0) {
		i++;
	}

	while (i >= 0) {
		printf("%s/", directoryList[i]);
		i--;

	}
	printf("\n");

}

void ls() {

	temp2 = current->child;

	while (temp2 != NULL) { //searches for Directories and files prints them in order

		printf("  %c ", temp2->type);
		printf("%s \n", temp2->name);
		temp2 = temp2->rsibling;

	}

}

void rm() {

	int i = 0;

	temp2 = current->child;

	while (temp2 != NULL) {

		if (strcmp(temp2->name, tokens[i + 1]) == 0) {

			break;

		}

		temp2 = temp2->rsibling;
	}

	if (temp2 != NULL) {

		if (temp2->parent == NULL) { //generic sibling node that does not have a parent

			temp2->lsibling->rsibling = temp2->rsibling;
			temp2->rsibling->lsibling = temp2->lsibling;
			temp2->rsibling = NULL;
			temp2->lsibling = NULL;
			delete(temp2);

		}
		if (temp2->parent != NULL) { //sibling node that does have parent
			if (temp2->rsibling == NULL) {		//does not have a sibling

				temp2->parent->child = NULL;
				temp2->parent = NULL;
				delete(temp2);

			} else {

				//has both parent and sibling

				temp2->parent->child = temp2->rsibling;
				temp2->rsibling->parent = temp2->parent;
				temp2->parent = NULL;
				temp2->rsibling = NULL;
				delete(temp2);

			}
		}

	}

	if (temp2 == NULL) {

		printf("File \"%s\" does not exist in directory \"%s.\"\n",
				tokens[i + 1], current->name);

	}
}

void mv() {

	temp2 = current->child;

	while (temp2 != NULL) {
//searches for new name of directory or file in list
		if (strcmp(temp2->name, tokens[2]) == 0) {

			break; //search name found

		}
		temp2 = temp2->rsibling;

	}
	if (temp2 != NULL) {

		printf("Name to replace with has already been used\n");

	}
	if (temp2 == NULL) {
		temp2 = current->child;
		while (temp2 != NULL) {
			//searches for name to change in list
			if (strcmp(temp2->name, tokens[1]) == 0) {

				break; //search name found

			}
			temp2 = temp2->rsibling;

		}
		if (temp2 == NULL) {

			printf(
					"Directory with name \"%s\" could not be found in directory \"%s\"\n",
					tokens[1], current->name);
		} else {

			strcpy(temp2->name, tokens[2]);
		}
	}
}

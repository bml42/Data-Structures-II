edit : main.o functions.o
	gcc -o Project2 main.o functions.o -lm
main.o : main.c functions.h
	gcc -c -Wall main.c
functions.o : functions.c functions.h
	gcc -c -Wall functions.c
clean: 
	rm edit main.o functions.o

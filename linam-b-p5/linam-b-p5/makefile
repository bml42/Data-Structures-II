cflags = -g -Wall
CC = gcc

objects = main.o Part1.o Part2.o functions.o

Project5: $(objects)
	$(CC) $(cflags) -o Project5 $(objects)

main.o : main.c main.h 

Part1.o : Part1.c Part1.h functions.h

Part2.o : Part2.c Part2.h functions.h

functions.o : functions.c functions.h Part1.h

.PHONY : clean
	rm $(objects) Project5

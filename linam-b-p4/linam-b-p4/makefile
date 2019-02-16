cflags = -g -Wall -lm
CC = gcc

objects = main.o part1.o part2.o functions.o

project4 : $(objects)
	$(CC) $(cflags) -o project4 $(objects)

main.o : main.c part1.h part2.h

part1.o : part1.c part1.h functions.h

part2.o : part2.c part2.h functions.h

functions.o : functions.c functions.h

.PHONY : clean
clean:
	rm test $(objects)

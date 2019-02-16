cflags = -g -Wall
CC = gcc

objects = main.o functions.o

main : $(objects)
	$(CC) $(cflags) -o main $(objects)

functions.o: functions.c  functions.h

main.o : main.c functions.h

.PHONY : clean

clean:	
	rm main $(objects)

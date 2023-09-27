# .PHONY: clean

objects = main.o list.o

CC = gcc
CFLAGS = -Wall -pedantic

.PHONY: clean

myProg: $(objects)
	gcc $(objects) -o myProg

main.o: main.c list.h
list.o: list.c list.h

clean:
	rm *.o
	rm myProg

test:
	@echo Lasciami fare!

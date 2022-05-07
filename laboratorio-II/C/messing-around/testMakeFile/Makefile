# .PHONY: clean

objects = main.o list.o

CC = gcc
CFLAGS = -Wall -pedantic

myProg: $(objects)
	gcc $(objects) -o myProg

main.o: main.c list.h
list.o: list.c list.h

clean:
	rm *.o
	rm myProg

test:
	@echo Lasciami fare!
	@./myProg 1 2 -1 2 3 -1 | diff - output1
	@echo Brav!
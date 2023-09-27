objects = exe
cfile = test.c
util = utils.h
executable = execut
executecommand = ./$(executable)


PHONY: clean, $(objects)

$(objects): $(executable) pippo.txt
	@$(executecommand)

pippo.txt:
	@touch pippo.txt

lib.o: $(util)
	gcc -o lib.o -c $^

$(executable): $(cfile)
	@gcc -Wall $^ -o $@ 


clean:
	rm -f $(executable)
	rm -f pippo.txt
	rm -f *.o

objects = exe
cfile = test.c
util = utils.h
executable = execut
executecommand = ./$(executable)


PHONY: clean, $(objects)

$(objects): $(executable)
	@$(executecommand)

lib.o: $(util)
	gcc -o lib.o -c $^

$(executable): $(cfile)
	@gcc -Wall $^ -o $@ 


clean:
	rm -f $(executable)
	rm -f *.o
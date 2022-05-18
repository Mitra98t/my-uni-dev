CC		=  gcc
AR              =  ar
additionalLibs        = boundedqueue.c
ifdef DEBUG
CFLAGS         += -Wall -g -fno-inline-functions -DDEBUG
else
CFLAGS	       += -pthread -Wall
endif
ARFLAGS         =  rvs
INCLUDES	= -I. -I ./utils/includes
LDFLAGS 	= -L.
LIBS            = -lrt

TARGETS		= farm
FILEDAT		= file1.dat file2.dat file3.dat file4.dat file5.dat file6.dat file7.dat


.PHONY: all clean cleanall exampleRun valgrind
.SUFFIXES: .c .h

%: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(additionalLibs) -o $@ $< $(LDFLAGS) $(LIBS)

all		: $(TARGETS)

clean		: 
	rm -f $(TARGETS)

cleanall	: clean
	\rm -f *.o *~ 

exampleRun	: $(TARGETS)
	./$(TARGETS) -n 4 -q 4 $(FILEDAT)

valgrind	: $(TARGETS)
	valgrind --leak-check=full ./$(TARGETS) -n 8 -q 4 -t 200 file*           




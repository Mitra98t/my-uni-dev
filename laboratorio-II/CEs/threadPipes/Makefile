CC		=  gcc -std=c11
AR              =  ar
OPTFLAGS        =
ifdef DEBUG
CFLAGS         += -Wall -g -fno-inline-functions -DDEBUG
else
CFLAGS	       += -Wall
OPTFLAGS       += -O3  -DNDEBUG
endif
ARFLAGS         =  rvs
INCLUDES	= -I. -I ./utils/includes
LDFLAGS 	= -L.
LIBS            = -lrt -lpthread

TARGETS		= main


.PHONY: all clean cleanall
.SUFFIXES: .c .h

pipeline: main.o unboundedqueue.o
	$(CC) $(CFLAGS) $(INCLUDES) $(OPTFLAGS) -o $@ $^ $(LIBS)
all		: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(OPTFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(OPTFLAGS) -c -o $@ $<


clean		: 
	rm -f $(TARGETS)

cleanall	: clean
	\rm -f *.o *~ 




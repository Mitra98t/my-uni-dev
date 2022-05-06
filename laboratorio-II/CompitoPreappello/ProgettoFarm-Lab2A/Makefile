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


.PHONY: all clean cleanall
.SUFFIXES: .c .h

%: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(additionalLibs) -o $@ $< $(LDFLAGS) $(LIBS)

all		: $(TARGETS)

clean		: 
	rm -f $(TARGETS)

cleanall	: clean
	\rm -f *.o *~ 



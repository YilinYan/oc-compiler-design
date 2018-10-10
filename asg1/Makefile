# $Id: Makefile,v 1.6 2018-09-26 16:37:28-07 - - $

CPP    = g++ -g -O0 -std=gnu++17 -Wall -Wextra -Wold-style-cast
CPPYY  = g++ -g -O0 -std=gnu++17 -Wno-register
SRCS   = auxlib.cpp auxlib.h string_set.cpp string_set.h main.cpp
OBJS   = main.o string_set.o auxlib.o

all : ${OBJS}
	${CPP} ${OBJS} -o oc

%.o : %.cpp
	${CPP} -c $<

clean :
	rm ${OBJS}

spotless : clean
	rm oc

ci :
	cid + ${SRCS}

deps :
	${CPP} -MM auxlib.cpp string_set.cpp main.cpp > Makefile.deps

include deps

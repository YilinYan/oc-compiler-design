# $Id: Makefile,v 1.6 2018-09-26 16:37:28-07 - - $

CPP    = g++ -g -O0 -std=gnu++17 -Wall -Wextra -Wold-style-cast
CPPYY  = g++ -g -O0 -std=gnu++17 -Wno-register
SRCS   = main.cpp point.h point.cpp

all : ${SRCS}
	${CPP} ${SRCS} -o main

clean :
	rm main


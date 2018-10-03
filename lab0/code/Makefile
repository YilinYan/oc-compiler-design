# $Id: Makefile,v 1.6 2018-09-26 16:37:28-07 - - $

CPP    = g++ -g -O0 -std=gnu++17 -Wall -Wextra -Wold-style-cast
CPPYY  = g++ -g -O0 -std=gnu++17 -Wno-register
OBJS   = main.o yyparse.o yylex.o
GENS   = yyparse.h yyparse.cpp yylex.cpp
SRCS   = extern.h lexer.l parser.y main.cpp Makefile

all : rpn

rpn : ${OBJS}
	${CPP} -o rpn ${OBJS}

%.o : %.cpp
#	checksource $<
#	cpplint.py.perl $<
	${CPP} -c $<

yyparse.cpp yyparse.h : parser.y
	bison --defines=yyparse.h --output=yyparse.cpp parser.y

yyparse.o : yyparse.cpp
	${CPPYY} -c yyparse.cpp

yylex.cpp : yyparse.h lexer.l
	flex --outfile=yylex.cpp lexer.l

yylex.o : yylex.cpp
	${CPPYY} -Wno-register -c yylex.cpp

spotless : clean
	- rm rpn Makefile.deps Listing.{ps,pdf}

clean :
	- rm ${OBJS} ${GENS} test.out

ci : 
	- cid + ${SRCS}

test : rpn
	( echo "3 4 * 1 3 / +" \
	; echo "10 0 /" \
	; echo foo \
	) | rpn >test.out 2>&1

lis : ${SRCS} test
	mkpspdf Listing.ps ${SRCS} yyparse.h test.out

again : spotless
	${MAKE} ci all lis

Makefile.deps : yyparse.cpp yylex.cpp
	${CPP} -MM yyparse.cpp yylex.cpp main.cpp >Makefile.deps

include Makefile.deps


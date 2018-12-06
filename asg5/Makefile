DEPSFILE  = Makefile.deps
CPP       = g++ -std=gnu++17 -g -O0
CPPWARN   = ${CPP} -Wall -Wextra -Wold-style-cast
CPPYY     = ${CPP} -Wno-sign-compare -Wno-register
MKDEPS    = g++ -std=gnu++17 -MM
GRIND     = valgrind --leak-check=full --show-reachable=yes
FLEX      = flex --outfile=${LEXCPP}
BISON     = bison --defines=${PARSEHDR} --output=${PARSECPP}

MODULES   = astree lyutils string_set auxlib symbol intermediate
HDRSRC	  = ${MODULES:=.h}
CPPSRC    = ${MODULES:=.cpp} main.cpp
FLEXSRC   = scanner.l
BISONSRC  = parser.y
PARSEHDR  = yyparse.h
LEXCPP    = yylex.cpp
PARSECPP  = yyparse.cpp
CGENS     = ${LEXCPP} ${PARSECPP}
ALLGENS   = ${PARSEHDR} ${CGENS}
ALLCSRC   = ${CPPSRC} ${CGENS}
OBJECTS   = ${ALLCSRC:.cpp=.o}
ALLSRC    = README Makefile ${HDRSRC} ${CPPSRC} ${FLEXSRC} ${BISONSRC}

all : ${OBJECTS}
	${CPPWARN} -o oc ${OBJECTS}

yylex.o : yylex.cpp
	${CPPYY} -c $<

yyparse.o : yyparse.cpp
	${CPPYY} -c $<

%.o : %.cpp
	- cpplint.py.perl $<
	${CPPWARN} -c $<

${LEXCPP} : ${FLEXSRC}
	${FLEX} ${FLEXSRC}

${PARSECPP} ${PARSEHDR} : ${BISONSRC}
	${BISON} ${BISONSRC}

ci : ${ALLSRC}
	- checksource ${ALLSRC}
	cid + ${ALLSRC}

clean :
	- rm ${OBJECTS} ${ALLGENS} ${DEPSFILE}

spotless : clean
	- rm oc

deps : ${ALLCSRC}
	@ echo "# ${DEPSFILE} created `date` by ${MAKE}" >${DEPSFILE}
	${MKDEPS} ${ALLCSRC} >>${DEPSFILE}

${DEPSFILE} :
	@ touch ${DEPSFILE}
	${MAKE} --no-print-directory deps

include ${DEPSFILE}

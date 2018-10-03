// $Id: main.cpp,v 1.2 2018-09-26 16:37:28-07 - - $

#include <stdio.h>
#include <stdlib.h>

#include "extern.h"

void yyerror (const char* error) {
   printf ("%s\n", error);
}

int main () {
   yyparse();
   return EXIT_SUCCESS;
}

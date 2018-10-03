// $Id: extern.h,v 1.1 2018-04-02 15:31:00-07 - - $

#ifndef __EXTERN_H__
#define __EXTERN_H__

int yylex();
int yyparse();

void badchar (char); 
void yyerror (const char*); 

extern char* yytext; 

#define YYSTYPE double
#include "yyparse.h"

#endif


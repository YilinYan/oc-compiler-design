// $Id: parser.y,v 1.3 2018-09-26 16:42:13-07 - - $

%{

#include <stdio.h>
#include <stdlib.h>

#include "extern.h"

%}

%token NUMBER

%%

input : input expr '\n' { printf ("\nanswer: %.15g\n", $2); }
      | '\n'            { printf ("\n"); }
      | error '\n'      { printf ("\n"); }
      |
      ;

expr  : NUMBER          { $$ = atof (yytext); }
      | expr expr '+'   { $$ = $1 + $2; }
      | expr expr '-'   { $$ = $1 - $2; }
      | expr expr '*'   { $$ = $1 * $2; }
      | expr expr '/'   { $$ = $1 / $2; }
      ;

%%


/* $Id: lexer.l,v 1.2 2018-09-26 16:37:28-07 - - $ */

%{

#include "extern.h"

%}

%option noyywrap

MANTISSA    ([[:digit:]]+\.?[[:digit:]]*|\.[[:digit:]]+)
EXPONENT    ([Ee][+-]?[[:digit:]]+)
INFINITY    ([Ii][Nn][Ff][[:isalnum:]]*)
NAN         ([Nn][Aa][Nn][[:isalnum:]]*)
NUMBER      ({MANTISSA})({EXPONENT})?|INFINITY|NAN


%%

"#".*      { ECHO; }
[ \t]+     { ECHO; }
\n         { ECHO; return '\n'; }
{NUMBER}   { ECHO; return NUMBER; }
"+"        { ECHO; return '+'; }
"-"        { ECHO; return '-'; }
"*"        { ECHO; return '*'; }
"/"        { ECHO; return '/'; }
.          { ECHO; printf ("\ninvalid character \\0%o\n", *yytext); }

%%

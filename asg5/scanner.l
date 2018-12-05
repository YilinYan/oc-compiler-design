%{

#include "lyutils.h"
#define YY_USER_ACTION  { lexer::advance(); }
#define RETURN(a) return yylval_token(a)

%}

%option 8bit
%option debug
%option nodefault
%option nounput
%option noyywrap
%option warn
/*%option verbose*/

/*MANTISSA        ({DIGIT}+\.?{DIGIT}*|\.{DIGIT}+)*/
/*EXPONENT        ([Ee][+-]?{DIGIT}+)*/
/*NUMBER          ({MANTISSA}{EXPONENT}?)*/
/*NOTNUMBER       ({MANTISSA}[Ee][+-]?)*/

LETTER          ([A-Za-z_])
DECDIGIT        ([0-9])
OCTDIGIT        ([0-7])
HEXDIGIT        ([0-9a-fA-F])
DECINT          ([1-9]{DECDIGIT}*)
OCTINT          (0[OCTDIGIT]*)
HEXINT          (0[x|X]{HEXDIGIT}+)

INT             ({DECINT}|{OCTINT}|{HEXINT})
IDENT           ({LETTER}({LETTER}|{DECDIGIT})*)
CHARC           ([^\\'\n]|\\[\\'"0nt])
CHARS           ([^\\"\n]|\\[\\'"0nt])
CHAR            ('{CHARC}')
STRING          (\"{CHARS}*\")

NOTESCAPE       (\\[^\\'"0nt])
NOTIDENT        {DECDIGIT}+{IDENT}
NOTCHAR         '{NOTESCAPE}'?|'{CHARC}?
NOTSTRING       \"{CHARS}*{NOTESCAPE}|\"{CHARS}*

%%

"#".*           { lexer::include(); }
[ \t]+          { }
\n              { lexer::newline(); }

"if"            { RETURN (TOK_IF); }
"else"          { RETURN (TOK_ELSE); }
"while"         { RETURN (TOK_WHILE); }
"return"        { RETURN (TOK_RETURN); }
"int"           { RETURN (TOK_INT); }
"string"        { RETURN (TOK_STRING); }
"struct"        { RETURN (TOK_STRUCT); }
"void"          { RETURN (TOK_VOID); }
"new"           { RETURN (TOK_NEW); }
"null"          { RETURN (TOK_NULL); }
"not"           { RETURN (TOK_NOT); }

{INT}           { RETURN (TOK_INTCON); }
{IDENT}         { RETURN (TOK_IDENT); }
{CHAR}          { RETURN (TOK_CHARCON); }
{STRING}        { RETURN (TOK_STRINGCON); }

"+"             { RETURN ('+'); }
"-"             { RETURN ('-'); }
"*"             { RETURN ('*'); }
"/"             { RETURN ('/'); }
"%"             { RETURN ('%'); }
"="             { RETURN ('='); }
"=="            { RETURN (TOK_EQ); }
"!="            { RETURN (TOK_NE); }
"<"             { RETURN ('<'); }
"<="            { RETURN (TOK_LE); }
">"             { RETURN ('>'); }
">="            { RETURN (TOK_GE); }
"->"            { RETURN (TOK_ARROW); }
","             { RETURN (','); }
";"             { RETURN (';'); }
"("             { RETURN ('('); }
")"             { RETURN (')'); }
"["             { RETURN ('['); }
"]"             { RETURN (']'); }
"{"             { RETURN ('{'); }
"}"             { RETURN ('}'); }
"[]"            { RETURN (TOK_ARRAY); }

{NOTIDENT}      { lexer::badtoken (yytext);
                  RETURN (TOK_IDENT); }
{NOTCHAR}       { lexer::badtoken (yytext);
                  RETURN (TOK_CHARCON); }
{NOTSTRING}     { lexer::badtoken (yytext);
                  RETURN (TOK_STRINGCON); }
.               { lexer::badchar (*yytext); }

%%

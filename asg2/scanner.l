%{

#include "lyutils.h"
/*
int yylval_token (int symbol) {
   yylval = new astree (symbol, lexer::lloc, yytext);
   return symbol;
}
*/

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
CHARS           ([^\\'\n]|\\[\\'"0nt])
CHAR            ('{CHARS}')
STRING          (\"{CHARS}\")

NOTESCAPE       (\\[^\\'"0nt])
NOTIDENT        {DECDIGIT}+{IDENT}
NOTCHAR         '{NOTESCAPE}'?|'{CHARS}
NOTSTRING       \"{CHARS}*{NOTESCAPE}|\"{CHARS}*

%%

"#".*           { lexer::include(); }
[ \t]+          { }
\n              { lexer::newline(); }

"if"            { return yylval_token (TOK_IF); }
"else"          { return yylval_token (TOK_ELSE); }
"while"         { return yylval_token (TOK_WHILE); }
"return"        { return yylval_token (TOK_RETURN); }
"int"           { return yylval_token (TOK_INT); }
"string"        { return yylval_token (TOK_STRING); }
"struct"        { return yylval_token (TOK_STRUCT); }
"void"          { return yylval_token (TOK_VOID); }
"new"           { return yylval_token (TOK_NEW); }
"null"          { return yylval_token (TOK_NULL); }
"not"           { return yylval_token (TOK_NOT); }

{INT}           { return yylval_token (TOK_INTCON); }
{IDENT}         { return yylval_token (TOK_IDENT); }
{CHAR}          { return yylval_token (TOK_CHARCON); }
{STRING}        { return yylval_token (TOK_STRINGCON); }

"+"             { return yylval_token ('+'); }
"-"             { return yylval_token ('-'); }
"*"             { return yylval_token ('*'); }
"/"             { return yylval_token ('/'); }
"%"             { return yylval_token ('%'); }
"="             { return yylval_token ('='); }
"=="            { return yylval_token (TOK_EQ); }
"!="            { return yylval_token (TOK_NE); }
"<"             { return yylval_token ('<'); }
"<="            { return yylval_token (TOK_LE); }
">"             { return yylval_token ('>'); }
">="            { return yylval_token (TOK_GE); }
"->"            { return yylval_token (TOK_ARROW); }
","             { return yylval_token (','); }
";"             { return yylval_token (';'); }
"("             { return yylval_token ('('); }
")"             { return yylval_token (')'); }
"["             { return yylval_token ('['); }
"]"             { return yylval_token (']'); }
"{"             { return yylval_token ('{'); }
"}"             { return yylval_token ('}'); }
"[]"            { return yylval_token (TOK_ARRAY); }

{NOTIDENT}      { lexer::badtoken (yytext);
                  return yylval_token (TOK_IDENT); }
{NOTCHAR}       { lexer::badtoken (yytext);
                  return yylval_token (TOK_CHARCON); }
{NOTSTRING}     { lexer::badtoken (yytext);
                  return yylval_token (TOK_STRINGCON); }
.               { lexer::badchar (*yytext); }

%%

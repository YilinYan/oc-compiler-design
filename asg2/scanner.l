%{

#include "lyutils.h"
#define ADVANCE lexer::advance()

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

"if"            { ADVANCE; return yylval_token (TOK_IF); }
"else"          { ADVANCE; return yylval_token (TOK_ELSE); }
"while"         { ADVANCE; return yylval_token (TOK_WHILE); }
"return"        { ADVANCE; return yylval_token (TOK_RETURN); }
"int"           { ADVANCE; return yylval_token (TOK_INT); }
"string"        { ADVANCE; return yylval_token (TOK_STRING); }
"struct"        { ADVANCE; return yylval_token (TOK_STRUCT); }
"void"          { ADVANCE; return yylval_token (TOK_VOID); }
"new"           { ADVANCE; return yylval_token (TOK_NEW); }
"null"          { ADVANCE; return yylval_token (TOK_NULL); }
"not"           { ADVANCE; return yylval_token (TOK_NOT); }

{INT}           { ADVANCE; return yylval_token (TOK_INTCON); }
{IDENT}         { ADVANCE; return yylval_token (TOK_IDENT); }
{CHAR}          { ADVANCE; return yylval_token (TOK_CHARCON); }
{STRING}        { ADVANCE; return yylval_token (TOK_STRINGCON); }

"+"             { ADVANCE; return yylval_token ('+'); }
"-"             { ADVANCE; return yylval_token ('-'); }
"*"             { ADVANCE; return yylval_token ('*'); }
"/"             { ADVANCE; return yylval_token ('/'); }
"%"             { ADVANCE; return yylval_token ('%'); }
"="             { ADVANCE; return yylval_token ('='); }
"=="            { ADVANCE; return yylval_token (TOK_EQ); }
"!="            { ADVANCE; return yylval_token (TOK_NE); }
"<"             { ADVANCE; return yylval_token ('<'); }
"<="            { ADVANCE; return yylval_token (TOK_LE); }
">"             { ADVANCE; return yylval_token ('>'); }
">="            { ADVANCE; return yylval_token (TOK_GE); }
"->"            { ADVANCE; return yylval_token (TOK_ARROW); }
","             { ADVANCE; return yylval_token (','); }
";"             { ADVANCE; return yylval_token (';'); }
"("             { ADVANCE; return yylval_token ('('); }
")"             { ADVANCE; return yylval_token (')'); }
"["             { ADVANCE; return yylval_token ('['); }
"]"             { ADVANCE; return yylval_token (']'); }
"{"             { ADVANCE; return yylval_token ('{'); }
"}"             { ADVANCE; return yylval_token ('}'); }
"[]"            { ADVANCE; return yylval_token (TOK_ARRAY); }

{NOTIDENT}      { ADVANCE; lexer::badtoken (yytext);
                  return yylval_token (TOK_IDENT); }
{NOTCHAR}       { ADVANCE; lexer::badtoken (yytext);
                  return yylval_token (TOK_CHARCON); }
{NOTSTRING}     { ADVANCE; lexer::badtoken (yytext);
                  return yylval_token (TOK_STRINGCON); }
.               { lexer::badchar (*yytext); }

%%

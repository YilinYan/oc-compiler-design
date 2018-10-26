%{

#include "lyutils.h"
#define ADVANCE lexer::advance()
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

"if"            { ADVANCE; RETURN (TOK_IF); }
"else"          { ADVANCE; RETURN (TOK_ELSE); }
"while"         { ADVANCE; RETURN (TOK_WHILE); }
"return"        { ADVANCE; RETURN (TOK_RETURN); }
"int"           { ADVANCE; RETURN (TOK_INT); }
"string"        { ADVANCE; RETURN (TOK_STRING); }
"struct"        { ADVANCE; RETURN (TOK_STRUCT); }
"void"          { ADVANCE; RETURN (TOK_VOID); }
"new"           { ADVANCE; RETURN (TOK_NEW); }
"null"          { ADVANCE; RETURN (TOK_NULL); }
"not"           { ADVANCE; RETURN (TOK_NOT); }

{INT}           { ADVANCE; RETURN (TOK_INTCON); }
{IDENT}         { ADVANCE; RETURN (TOK_IDENT); }
{CHAR}          { ADVANCE; RETURN (TOK_CHARCON); }
{STRING}        { ADVANCE; RETURN (TOK_STRINGCON); }

"+"             { ADVANCE; RETURN ('+'); }
"-"             { ADVANCE; RETURN ('-'); }
"*"             { ADVANCE; RETURN ('*'); }
"/"             { ADVANCE; RETURN ('/'); }
"%"             { ADVANCE; RETURN ('%'); }
"="             { ADVANCE; RETURN ('='); }
"=="            { ADVANCE; RETURN (TOK_EQ); }
"!="            { ADVANCE; RETURN (TOK_NE); }
"<"             { ADVANCE; RETURN ('<'); }
"<="            { ADVANCE; RETURN (TOK_LE); }
">"             { ADVANCE; RETURN ('>'); }
">="            { ADVANCE; RETURN (TOK_GE); }
"->"            { ADVANCE; RETURN (TOK_ARROW); }
","             { ADVANCE; RETURN (','); }
";"             { ADVANCE; RETURN (';'); }
"("             { ADVANCE; RETURN ('('); }
")"             { ADVANCE; RETURN (')'); }
"["             { ADVANCE; RETURN ('['); }
"]"             { ADVANCE; RETURN (']'); }
"{"             { ADVANCE; RETURN ('{'); }
"}"             { ADVANCE; RETURN ('}'); }
"[]"            { ADVANCE; RETURN (TOK_ARRAY); }

{NOTIDENT}      { ADVANCE; lexer::badtoken (yytext);
                  RETURN (TOK_IDENT); }
{NOTCHAR}       { ADVANCE; lexer::badtoken (yytext);
                  RETURN (TOK_CHARCON); }
{NOTSTRING}     { ADVANCE; lexer::badtoken (yytext);
                  RETURN (TOK_STRINGCON); }
.               { ADVANCE; lexer::badchar (*yytext); }

%%

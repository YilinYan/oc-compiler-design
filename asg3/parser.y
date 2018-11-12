%{
// $Id: parser.y,v 1.7 2018-11-12 14:02:13-08 - - $
// Dummy parser for scanner project.

#include <cassert>

#include "lyutils.h"
#include "astree.h"

%}

%debug
%defines
%error-verbose
%token-table
%verbose

%printer { astree::dump (yyoutput, $$); } <>
%initial-action {
   parser::root = new astree (TOK_ROOT, {0, 0, 0}, "");
}

%token TOK_VOID TOK_CHAR TOK_INT TOK_STRING
%token TOK_IF TOK_ELSE TOK_WHILE TOK_RETURN TOK_STRUCT
%token TOK_NULL TOK_NEW TOK_ARRAY TOK_ARROW
%token TOK_EQ TOK_NE TOK_LT TOK_LE TOK_GT TOK_GE TOK_NOT
%token TOK_IDENT TOK_INTCON TOK_CHARCON TOK_STRINGCON

%token TOK_ROOT TOK_BLOCK TOK_CALL TOK_IFELSE TOK_INITDECL
%token TOK_POS TOK_NEG TOK_NEWARRAY TOK_TYPEID TOK_FIELD

%token TOK_FUNCTION TOK_PARAM TOK_PROTO TOK_DECLID
%token TOK_NEWSTR TOK_INDEX TOK_VARDECL

%start start

%right TOK_IF TOK_ELSE
%right '='
%left  TOK_GE TOK_LE TOK_EQ TOK_NE '<' '>'
%left  '+' '-'
%left  '*' '/' '%'
%right TOK_POS TOK_NEG TOK_NOT TOK_NEW
%left  '[' TOK_ARROW TOK_FUNCTION

%%

start     : program                      { yyparse_astree = $1; }
          ;

program   : program structdef            { $$ = $1->adopt($2); }
          | program function             { $$ = $1->adopt($2); }
          | program globaldecl           { $$ = $1->adopt($2); }
          | program error '}'            { $$ = $1; }
          | program error ';'            { $$ = $1; }
          |                              { $$ = parser::root; }
          ;

globaldecl: identdecl '=' constant ';'   { $$ = ($2->change_sym(
                                           TOK_VARDECL))->
                                           adopt($1, $3); }
          ;

structdef : TOK_STRUCT TOK_IDENT '{' '}' { $$ = $1->adopt_new($2, 
                                           TOK_TYPEID); }
          | TOK_STRUCT TOK_IDENT structhaf '}'  
                                         { $$ = $1->adopt($2->change_sym
                                           (TOK_TYPEID), $3); }
          ;

structhaf : '{' fielddecl ';'            { $$ = $1->adopt($2); }
          | structhaf fielddecl ';'      { $$ = $1->adopt($2); }
          ;

fielddecl : basetype TOK_IDENT           { $$ = $1->adopt_new($2, 
                                           TOK_FIELD); }
          | basetype TOK_ARRAY TOK_IDENT { $$ = $2->adopt($1, 
                                           $3->change_sym(TOK_FIELD));}
          ;

basetype  : TOK_VOID                     { $$ = $1; }
          | TOK_INT                      { $$ = $1; }
          | TOK_STRING                   { $$ = $1; }
          | TOK_IDENT                    { $$ = $1->change_sym(
                                           TOK_TYPEID); }
          ;

function  : identdecl '(' ')' fnbody     { $$ = astree::function_(
                                           $1, $2, $4); }
          | identdecl param ')' fnbody   { $$ = astree::function_(
                                           $1, $2, $4); }
          | identdecl '(' ')' ';'        { $$ = astree::function_(
                                           $1, $2); }
          | identdecl param ')' ';'      { $$ = astree::function_(
                                           $1, $2); }
          ;

param     : param ',' identdecl          { $$ = $1->adopt($3); }
          | '(' identdecl                { $$ = $1->adopt_sym($2, 
                                           TOK_PARAM); }
          ;

identdecl : basetype TOK_IDENT           { $$ = $1->adopt_new($2, 
                                           TOK_DECLID); }
          | basetype TOK_ARRAY TOK_IDENT { $$ = $2->adopt($1, $3->
                                           change_sym(TOK_DECLID));}
          ;

fnbody    : '{' '}'                      { $$ = $1; }
          | fnbodyb '}'                  { $$ = $1; }
          | fnbodya '}'                  { $$ = $1; }
          ;

fnbodya   : '{' localdecl                { $$ = $1->adopt($2); }
          | fnbodya localdecl            { $$ = $1->adopt($2); }
          ;

fnbodyb   : '{' statement                { $$ = $1->adopt($2); }
          | fnbodyb statement            { $$ = $1->adopt($2); }
          | fnbodya statement            { $$ = $1->adopt($2); }
          ;

localdecl : identdecl '=' expr ';'       { $$ = ($2->change_sym(
                                           TOK_VARDECL))->
                                           adopt($1, $3); }
          ;

block     : '{' '}'                      { $$ = $1->change_sym(
                                           TOK_BLOCK); }
          | blockhaf '}'                 { $$ = $1; }
          ;

blockhaf  : blockhaf statement           { $$ = $1->adopt($2); }
          | '{' statement                { $$ = $1->adopt_sym($2, 
                                           TOK_BLOCK); }
          ;

statement : block                        { $$ = $1; }
          | while                        { $$ = $1; }
          | ifelse                       { $$ = $1; }
          | return                       { $$ = $1; }
          | expr ';'                     { $$ = $1; }
          | ';'                          { $$ = $1; }
          ;

while     : TOK_WHILE '(' expr ')' statement    
                                         { $$ = $1->adopt($3, $5); }
          ;

ifelse    : TOK_IF '(' expr ')' statement       
                                         { $$ = $1->adopt($3, $5); }
          | TOK_IF '(' expr ')' statement TOK_ELSE statement  
                                         { $$ = ($1->adopt($3, $5))->
                                           adopt($7); }
          ;

return    : TOK_RETURN expr ';'          { $$ = $1->adopt($2); }
          | TOK_RETURN ';'               { $$ = $1; }
          ;

expr      : expr '=' expr                { $$ = $2->adopt($1, $3); }
          | expr TOK_EQ expr             { $$ = $2->adopt($1, $3); }
          | expr TOK_NE expr             { $$ = $2->adopt($1, $3); }
          | expr TOK_LE expr             { $$ = $2->adopt($1, $3); }
          | expr TOK_GE expr             { $$ = $2->adopt($1, $3); }
          | expr '<' expr                { $$ = $2->adopt($1, $3); }
          | expr '>' expr                { $$ = $2->adopt($1, $3); }
          | expr '+' expr                { $$ = $2->adopt($1, $3); }
          | expr '-' expr                { $$ = $2->adopt($1, $3); }
          | expr '*' expr                { $$ = $2->adopt($1, $3); }
          | expr '/' expr                { $$ = $2->adopt($1, $3); }
          | expr '%' expr                { $$ = $2->adopt($1, $3); }
          | '+' expr                     { $$ = $1->adopt_sym($2, 
                                           TOK_POS); } %prec TOK_POS
          | '-' expr                     { $$ = $1->adopt_sym($2, 
                                           TOK_NEG); } %prec TOK_NEG
          | TOK_NOT expr                 { $$ = $1->adopt($2); }
          | allocation                   { $$ = $1; }
          | call                         { $$ = $1; }
          | '(' expr ')'                 { $$ = $2; }
          | variable                     { $$ = $1; }
          | constant                     { $$ = $1; }
          ;

allocation: TOK_NEW TOK_IDENT            { $$ = $1->adopt_new($2, 
                                           TOK_TYPEID); }
          | TOK_NEW TOK_STRING '(' expr ')'     
                                         { $$ = $1->adopt_sym($4, 
                                           TOK_NEWSTR); }
          | TOK_NEW basetype '[' expr ']'{ $$ = ($1->change_sym(
                                           TOK_NEWARRAY))->
                                           adopt($2, $4); }
          ;

call      : TOK_IDENT '(' ')'            { $$ = $2->adopt_sym($1, 
                                           TOK_CALL); }
          | callhaf ')'                  { $$ = $1; }
          ;

callhaf   : callhaf ',' expr             { $$ = $1->adopt($3); }
          | TOK_IDENT '(' expr           { $$ = ($2->change_sym(
                                           TOK_CALL))->
                                           adopt($1, $3); }
          ;

variable  : TOK_IDENT                    { $$ = $1; }
          | expr '[' expr ']'            { $$ = ($2->change_sym(
                                           TOK_INDEX))->
                                           adopt($1, $3); }
          | expr TOK_ARROW TOK_IDENT     { $$ = $2->adopt($1, $3->
                                           change_sym(TOK_FIELD)); }
          ;

constant  : TOK_INTCON                   { $$ = $1; }
          | TOK_CHARCON                  { $$ = $1; }
          | TOK_STRINGCON                { $$ = $1; }
          | TOK_NULL                     { $$ = $1; }
          ;
%%

const char *parser::get_tname (int symbol) {
   return yytname [YYTRANSLATE (symbol)];
}

bool is_defined_token (int symbol) {
   return YYTRANSLATE (symbol) > YYUNDEFTOK;
}

astree* astree::function_ (astree* a, astree* b, astree *c) {
    astree* func = new astree(TOK_PROTO, a->lloc, "");
    b->change_sym(TOK_PARAM);
    func->adopt(a, b);
    if(c != nullptr) {
        func->change_sym(TOK_FUNCTION);
        func->adopt_new(c, TOK_BLOCK);
    }
    return func;
}

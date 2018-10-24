#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "auxlib.h"
#include "astree.h"
#include "lyutils.h"
#include "string_set.h"

const string cpp_name = "/usr/bin/cpp";
string cpp_command;

// Open a pipe from the C preprocessor.
// Exit failure if can't.
// Assigns opened pipe to FILE* yyin.
void cpp_popen (const char* filename) {
   cpp_command = cpp_name + " " + filename;
   yyin = popen (cpp_command.c_str(), "r");

   if (yyin == nullptr) {
      syserrprintf (cpp_command.c_str());
      exit (exec::exit_status);
   }else {
      if (yy_flex_debug) {
          fprintf (stderr, "-- popen (%s), fileno(yyin) = %d\n",
                cpp_command.c_str(), fileno (yyin));
      }
      lexer::newfilename (cpp_command);
   } 
   
}

void cpp_pclose() {
   int pclose_rc = pclose (yyin);
   
   eprint_status (cpp_command.c_str(), pclose_rc);
   
   if (pclose_rc != 0) exec::exit_status = EXIT_FAILURE;
}

int main (int argc, char** argv) {
    exec::execname = basename (argv[0]);   
    cpp_popen (argv[1]);
       
    int token = 0;
    while ((token = yylex()) != YYEOF) {
       printf ("\t\t\t\t\t%s\t%s\n", 
               yytext, parser::get_tname(token));
    }

    cpp_pclose ();

    return exec::exit_status;
}

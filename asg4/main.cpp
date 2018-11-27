#include <string>
using namespace std;

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wait.h>
#include <libgen.h>
#include <stdlib.h>
#include <unistd.h>

#include "string_set.h"
#include "auxlib.h"
#include "astree.h"
#include "lyutils.h"

const string CPP = "/usr/bin/cpp";
FILE* tokfile = 0;

void popen_cpp (string& cmd) {
   yyin = popen (cmd.c_str(), "r");

   if (yyin == nullptr) {
      syserrprintf (cmd.c_str());
      exit (exec::exit_status);
   }
   else {
      if (yy_flex_debug) {
          fprintf (stderr, "-- popen (%s), fileno(yyin) = %d\n",
                cmd.c_str(), fileno (yyin));
      }
      lexer::newfilename (cmd);
   }
}

void pclose_cpp (string& cmd) {
   int pclose_rc = pclose (yyin);  
   eprint_status (cmd.c_str(), pclose_rc);
   if (pclose_rc != 0) exec::exit_status = EXIT_FAILURE;
}

void open_tok (string& ocname) {
    string outname = ocname + ".tok";
    DEBUGF ('w', "output: %s\n", outname.c_str());

    tokfile = fopen (outname.c_str(), "w");
    if (!tokfile) {
        fprintf (stderr, "oc: Fail to open %s\n", outname.c_str());
        exit (exec::exit_status);
    }
}

void readlines (string& ocname) {
    string outname = ocname + ".ast";
    FILE* outfile = fopen (outname.c_str(), "w");
    string symbol_outname = ocname + ".sym";
    FILE* symbol_outfile = fopen(symbol_outname.c_str(), "w");

    yyparse();
    symbol_generator* generator = new symbol_generator(symbol_outfile);
    generator->generate(yyparse_astree);
    astree::print(outfile, yyparse_astree, 0);
    
    fclose (outfile);
    fclose (symbol_outfile);
    fclose (tokfile);
}

void write_str (string_set& table, string& ocname) {
    string outname = ocname + ".str";
    DEBUGF ('w', "output: %s\n", outname.c_str());

    FILE* outfile = fopen (outname.c_str(), "w");
    if (!outfile) {
        fprintf (stderr, "oc: Fail to open %s\n", outname.c_str());
        exit (exec::exit_status);
    }
    table.dump (outfile);
    fclose (outfile);
}

int getoptions (int argc, char* argv[], string& cmd, string& ocname) {
    //  set error print
    opterr = 1;
    yy_flex_debug = yydebug = 0;
    cmd += CPP;
    int opt;
    while ((opt = getopt (argc, argv, "ly@:D:")) != -1) {
        //  printf ("%c: %s \t next:%d\n", opt, optarg, optind);
        switch (opt) {
            case 'l':
                yy_flex_debug = 1;
                break;
            case 'y':
                yydebug = 1;
                break;
            case '@':
                set_debugflags (optarg);
                break;
            case 'D':
                cmd += " -D ";
                cmd += string (optarg);
                break;
            case '?':
                return -1;
        }
    }
    if (optind < argc) {
        char* prog = argv[optind];
        char* progname = basename (prog);
        char* suffixptr = strrchr (progname, '.');
        if (suffixptr == nullptr || strcmp (suffixptr, ".oc") != 0) {
            fprintf (stderr, "oc: Input must be .oc file.\n");
            return -1;
        }

        ocname = string (progname, suffixptr - progname);
        DEBUGF ('o', "ocname: %s\n", ocname.c_str());

        cmd += " ";
        cmd += string (prog);
        DEBUGF ('o', "cmd: %s\n", cmd.c_str());
        return 0;
    }
    else {
        fprintf (stderr, "oc: No input file.\n");
        return -1;
    }
}

int main (int argc, char* argv[]) {
    string cmd, ocname;
    
    int getoptions_rc = getoptions (argc, argv, cmd, ocname);
    if (getoptions_rc != 0) {
        exec::exit_status = EXIT_FAILURE;
    }
    else {
        exec::execname = ocname;
        string_set table;
        popen_cpp (cmd);
        open_tok (ocname);
        readlines (ocname);
        pclose_cpp(cmd);
        write_str (table, ocname);
    }
    return exec::exit_status;
}

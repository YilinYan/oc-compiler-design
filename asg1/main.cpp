#include "string_set.h"
#include "auxlib.h"

#include <string>
using namespace std;

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wait.h>
#include <libgen.h>
#include <stdlib.h>
#include <unistd.h>

#define LINESIZE 1024

const string CPP = "/usr/bin/cpp -nostdinc";
char line[LINESIZE], buf[LINESIZE];

int readlines (string_set& table, string& cmd) {
	FILE* pipe = popen (cmd.c_str(), "r");
	if (!pipe) {
		fprintf (stderr, "oc: %s: %s\n", 
						cmd.c_str(), strerror(errno));
		return -1;
	}

	for (int linenum = 1;; ++linenum) {
		char* fgets_rc = fgets (buf, LINESIZE, pipe);
		if (fgets_rc == nullptr) break;
		DEBUGF ('r', "line: %d: %s\n", 
					linenum, fgets_rc);
		
		char* pos = nullptr;
		char* bufptr = buf;
		for (int cnt = 1;; ++cnt) {
			char* token = strtok_r (bufptr, " \t\n", &pos);
			bufptr = nullptr;
			if (token == nullptr) break;
			DEBUGF ('r', "token: %d.%d: [%s]\n",
						linenum, cnt, token);			
			table.intern (token);
		}
	}
	
	int pclose_rc = pclose (pipe);
	eprint_status (cmd.c_str(), pclose_rc);
	if (pclose_rc != 0) return -1;
	return 0;
}

int writefile (string_set& table, string& ocname) {
	string outname = ocname + ".str";
	DEBUGF ('w', "output: %s\n", outname.c_str());
	
	FILE* outfile = fopen (outname.c_str(), "w");
	table.dump (outfile);
	fclose (outfile);
	return 0;
}

int getoptions (int argc, char* argv[], string& cmd, string& ocname) {
// 	set error print
	opterr = 1;
	cmd += CPP;
	int opt;
	while ((opt = getopt (argc, argv, "ly@:D:")) != -1) {
//		printf ("%c: %s \t next:%d\n", opt, optarg, optind);	
		switch (opt) {
			case 'l':
				//Debug yylex() with yy_flex_debug = 1
				break;
			case 'y':
				//Debug yyparse() with yydebug = 1
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
	int exit_status = EXIT_SUCCESS;
	
	string cmd, ocname;
    int getoptions_rc = getoptions (argc, argv, cmd, ocname);	
	if (getoptions_rc != 0) {
		exit_status = EXIT_FAILURE;
	}
	else {
		string_set table;
		int readlines_rc = readlines (table, cmd);
		if (readlines_rc != 0) {
			exit_status = EXIT_FAILURE;
		}
		else {
			int writefile_rc = writefile (table, ocname);
			if (writefile_rc != 0) {
				exit_status = EXIT_FAILURE;
			}
		}
	}
	return exit_status;
}

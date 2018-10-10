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

void chomp (char* line) {
	int len = strlen (line);
	if (len == 0) return;
	char* tail = line + len -1;
	if (*tail == '\n') *tail = '\0';
}

char line[LINESIZE], buf[LINESIZE];
string_set S;
void readlines (FILE* pipe) {
	for (int linenum = 1;; ++linenum) {
		char* fgets_rc = fgets (buf, LINESIZE, pipe);
		if (fgets_rc == nullptr) break;
		chomp (fgets_rc);
		DEBUGF ('r', "line: %d: %s\n", linenum, fgets_rc);
		
		int sscanf_rc = sscanf (buf, "# %d \"%[^\"]\"",
				&linenum, line);
		if (sscanf_rc == 2) {
			DEBUGF ('r', "DIRECTIVE: %s\n", line);
			continue;
		}

		char* pos = nullptr;
		char* bufptr = buf;
		for (int cnt = 1;; ++cnt) {
			char* token = strtok_r (bufptr, " \t\n", &pos);
			bufptr = nullptr;
			if (token == nullptr) break;
			DEBUGF ('r', "token: %d.%d: [%s]\n",
							linenum, cnt, token);			
			S.intern (token);
		}
	}
}

int getoptions (int argc, char* argv[], string& cmd, string& ocname) {
// 	set error print
	opterr = 1;
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
			fprintf (stderr, "oc: Input must be .oc file.");
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
		fprintf (stderr, "oc: No input file.");
		return -1;	
	}
}

int main (int argc, char* argv[]) {
	int exit_status = EXIT_SUCCESS;
	string cmd, ocname;
	cmd += CPP; 
	if (getoptions (argc, argv, cmd, ocname) == -1) {
		exit_status = EXIT_FAILURE;
	}
	else {
		FILE* pipe = popen (cmd.c_str(), "r");
		if (!pipe) {
			exit_status = EXIT_FAILURE;
			fprintf (stderr, "oc: %s: %s\n", 
					cmd.c_str(), strerror(errno));
		}
		else {
			readlines (pipe);
			int pclose_rc = pclose (pipe);
			// eprint_status (cmd.c_str(), pclose_rc);
			if (pclose_rc != 0) exit_status = EXIT_FAILURE;
		}
	
		string outname = ocname + ".str";
		FILE* outfile = fopen (outname.c_str(), "w");
		DEBUGF ('w', "output: %s\n", outname.c_str());
		S.dump (outfile);
	}
	return exit_status;
}

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
string_set S;
void readlines (FILE* pipe) {
	for (int linenum = 1;; ++linenum) {
		char* fgets_rc = fgets (buf, LINESIZE, pipe);
		//		printf("%d: %s\n", linenum, fgets_rc);
		//		? why "chomp" : trun \n to \0
		if (fgets_rc == nullptr) break;
		int sscanf_rc = sscanf (buf, "# %d \"%[^\"]\"",
				&linenum, line);
		if (sscanf_rc == 2) {
			//This is a DIRECTIVE
			continue;
		}
		char* pos = nullptr;
		char* bufptr = buf;
		for (int cnt = 1;; ++cnt) {
			char* token = strtok_r (bufptr, " \t\n", &pos);
			bufptr = nullptr;
			if (token == nullptr) break;
			//			printf ("token: %d.%d: [%s]\n",
			//				linenum, cnt, token);			
			S.intern (token);
		}
	}
}

int getoptions (int argc, char* argv[], string& cmd) {
	int opt;
// 	set error print
	opterr = 1;
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
		cmd += " ";
		cmd += string (argv[optind]);
		DEBUGF ('o', "cmd: %s\n", cmd.c_str());
		return 0;
	}
	else {
		return -1;	
	}
}

int main (int argc, char* argv[]) {
	char* exename = basename (argv[0]);	
	int exit_status = EXIT_SUCCESS;
	string cmd;
	cmd += CPP; 
	getoptions (argc, argv, cmd);
	return 0;
/*
	char* file = argv[argc-1];
	char* filename = basename (file);
	char* suffixptr = strrchr (filename, '.');
	if (suffixptr == nullptr || 
*/

	FILE* pipe = popen (cmd.c_str(), "r");
	if (!pipe) {
		exit_status = EXIT_FAILURE;
		fprintf (stderr, "%s: %s: %s\n",
				exename, cmd.c_str(), strerror(errno));
	}
	else {
		readlines (pipe);
		int pclose_rc = pclose (pipe);
		// eprint_status (cmd.c_str(), pclose_rc);
		if (pclose_rc != 0) exit_status = EXIT_FAILURE;
	}

	FILE* dumpfile = fopen ("dump.out", "w");
	S.dump (dumpfile);

	return exit_status;
}

#include "string_set.h"
#include <stdio.h>
#include <string>
#include <errno.h>
using namespace std;

#define LINESIZE 1024
const string CPP = "/usr/bin/cpp -nostdinc";


char line[LINESIZE], buf[LINESIZE];
void readlines(FILE* pipe, const char* file) {
	for(int linenum = 1;; ++linenum) {
		char* fgets_rc = fgets (buf, LINESIZE, pipe);
		printf("%d: %s\n", linenum, fgets_rc);
	}
}

int main (int argc, char* argv[]) {
	char* exename = basename (argv[0]);
	int exit_status = EXIT_SUCCESS;
	for (int i = 1; i < argc; ++i) {
		char* file = argv[i];
		string cmd = CPP + " " + file; 
		FILE* pipe = popen (cmd.c_str(), "r");
		if (!pipe) {
			exit_status = EXIT_FAILURE;
			fprintf (stderr, "%s: %s: %s\n",
					exename, cmd.c_str(), strerror(errno));
		}
		else {
			readlines (pipe, file);
			int pclose_rc = pclose (pipe);
			// eprint_status (cmd.c_str(), pclose_rc);
			if (pclose_rc != 0) exit_status = EXIT_FAILURE;
		}
	}
	return exit_status;
}

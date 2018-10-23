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

int main (int argc, char** argv) {
    exec::execname = basename (argv[0]);
    return exec::execname;
}

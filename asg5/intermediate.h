#ifndef __INTERMEDIATE_H__
#define __INTERMEDIATE_H__

#include "auxlib.h"
#include "astree.h"

struct interm_generator {
    int seq_nr;
    FILE* outfile;
    interm_generator(FILE* file);
        
    const char* type_name;
    void generate(astree* root);
    void gen_struct(astree* root);
    void gen_field(astree* root);
    
    void gen_str_con(astree* root);
};

#endif
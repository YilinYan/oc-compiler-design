#include "intermediate.h"
#include "lyutils.h"
#include "symbol.h"

#include <string.h>

const char* get_yy_name(astree* root) {
    const char* tname = parser::get_tname (root->symbol);
    if(tname && strstr (tname, "TOK_") == tname) tname += 4;
    return tname;
}

interm_generator::interm_generator(FILE* file) {
    outfile = file;
    type_name = NULL;
}

const char* get_oil_type(astree* root) {
    //int string void struct []
    if(type_test(root, attr::ARRAY)) {
        if(type_test(root, attr::INT))
            return "int*";
        if(type_test(root, attr::STRING))
            return "char**";
        if(type_test(root, attr::STRUCT))
            
    }
    else if(type_test(root, attr::INT)) {
    
    }
    else if(type_test(root, attr::STRING)) {
    
    }
    else if(type_test(root, attr::VOID)) {
    
    }
    else if(type_test(root, attr::STRUCT)) {
        
    }
    else {
        DEBUGF('I', "get oil type INVALID: %s\n\n",
                get_decl_name(root));
    }
}

void interm_generator::gen_field(astree* root) {
    fprintf(outfile, "%s ", get_oil_type(root));
    fprintf(outfile, "%s_%s\n", type_name, get_decl_name(root));
}

void interm_generator::gen_struct(astree* root) {
    astree* name;
    astree* block;
    get_children(root, name, block);
    type_name = get_decl_name(name);

    DEBUGF('I', "gen struct: %s\n\n", 
            type_name);
    
    fprintf(outfile, "struct %s {\n", 
            type_name);
    for(int i = 0; i < block->children.size(); ++i) {
        gen_field(block->children[i]);
    }
    fprintf(outfile, "}\n");
    
    type_name = NULL;
}

void interm_generator::generate(astree* root) {
    const char* name = get_yy_name(root);
    if(strcmp(name, "ROOT") != 0) {
        errllocprintf(root->lloc, "%s",
                "INVALID root\n");
        return;
    }
    // get all struct
    for(int i = 0; i < root->children.size(); ++i) {
        astree* child = root->children[i];
        name = get_yy_name(child);
        if(strcmp(name, "STRUCT") == 0)
            gen_struct(child);
    }
}

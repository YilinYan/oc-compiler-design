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
    astree* var;
    symbol_node* node;
    if(root->children.size())
        var = *(root->children.end() - 1);
    else {
        var = root;
        DEBUGF('I', "get oil type struct: %s\n\n",
                get_decl_name(var));
    }
    if(type_test(var, attr::ARRAY)) {
        if(type_test(var, attr::INT))
            return "int*";
        if(type_test(var, attr::STRING))
            return "char**";
        if(type_test(var, attr::STRUCT)) {
            node = var->symbol_item;
            if(node && node->type_name)
                return ("struct " + string(node->type_name) + "**"
                        ).c_str();
            DEBUGF('I', "get oil type struct[] INVALID: %s\n\n",
                    get_decl_name(var));
        }
        DEBUGF('I', "get oil type [] INVALID: %s\n\n", 
                get_decl_name(var));
    }
    else if(type_test(var, attr::INT)) {
        return "int";
    }
    else if(type_test(var, attr::STRING)) {
        return "char*";
    }
    else if(type_test(var, attr::VOID)) {
        return "void";
    }
    else if(type_test(var, attr::STRUCT)) {
        node = var->symbol_item;
        if(node && node->type_name)
            return ("struct " + string(node->type_name) + "*"
                   ).c_str();
        DEBUGF('I', "get oil type struct INVALID: %s\n\n",
                get_decl_name(var));
    }
    else {
        DEBUGF('I', "get oil type INVALID: %s\n\n",
                get_decl_name(var));
    }
    return NULL;
}

void interm_generator::gen_field(astree* root) {
    fprintf(outfile, "\t%s ", get_oil_type(root));
    fprintf(outfile, "%s_%s;\n", type_name, get_decl_name(root));
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
    for(size_t i = 0; i < block->children.size(); ++i) {
        gen_field(block->children[i]);
    }
    fprintf(outfile, "};\n");
    
    type_name = NULL;
}

void interm_generator::gen_str_con(astree* root) {
    for(size_t i = 0; i < root->children.size(); ++i) {
        gen_str_con(root->children[i]);
    }

    const char* name = get_yy_name(root);
    if(strcmp(name, "STRINGCON")) return;

    const char* reg_name = ("s" + to_string(++seq_nr)).c_str();
    root->reg_name = reg_name;
    fprintf(outfile, "char* %s = %s;\n", reg_name,
            root->lexinfo->c_str());
}

void interm_generator::generate(astree* root) {
    const char* name = get_yy_name(root);
    if(strcmp(name, "ROOT") != 0) {
        errllocprintf(root->lloc, "%s",
                "INVALID root\n");
        return;
    }
    // get all struct
    for(size_t i = 0; i < root->children.size(); ++i) {
        astree* child = root->children[i];
        name = get_yy_name(child);
        if(strcmp(name, "STRUCT") == 0)
            gen_struct(child);
    }

    // get all STRINGCON
    gen_str_con(root);
}

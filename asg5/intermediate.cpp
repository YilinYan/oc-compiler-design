#include "intermediate.h"
#include "lyutils.h"
#include "symbol.h"

#include <string>

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

const char* string_to_char(string s) {
//    DEBUGF('I', "string to char: %s\n", s.c_str());

    char* rt = new char[s.size() + 1];
    memset(rt, 0, sizeof(char) * (s.size() + 1));
    snprintf(rt, s.size() + 1, "%s", s.c_str());
    return rt;
}

const char* get_oil_type(astree* root) {
    //int string void struct []
    astree* var;
    symbol_node* node;
    if(root->children.size())
        var = *(root->children.end() - 1);
    else {
        var = root;
//        DEBUGF('I', "get oil type struct: %s\n\n",
//                get_decl_name(var));
    }
    if(type_test(var, attr::ARRAY)) {
        if(type_test(var, attr::INT))
            return "int*";
        if(type_test(var, attr::STRING))
            return "char**";
        if(type_test(var, attr::STRUCT)) {
            node = var->symbol_item;
            if(node && node->type_name) {
                return string_to_char("struct " 
                        + string(node->type_name) + "**");
            }
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
        //overflow ??
        if(node && node->type_name)
            return string_to_char("struct " + string(node->type_name) 
                    + "*");
        DEBUGF('I', "get oil type struct INVALID: %s\n\n",
                get_decl_name(var));
    }
    else {
        DEBUGF('I', "get oil type INVALID: %s\n\n",
                get_decl_name(var));
    }
    return NULL;
}

const char* get_array_type(astree* root) {
    astree* var = root->children[0];
    symbol_node* node;
    if(type_test(var, attr::INT))
        return "int*";
    if(type_test(var, attr::STRING))
        return "char**";
    if(type_test(var, attr::STRUCT)) {
        node = var->symbol_item;
        if(node && node->type_name) {
            return string_to_char("struct " 
                    + string(node->type_name) + "**");
        }
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

    const char* reg_name = string_to_char("s" + to_string(++seq_nr));
    root->reg_name = reg_name;
    fprintf(outfile, "char* %s = %s;\n", reg_name,
            root->lexinfo->c_str());
}

void interm_generator::gen_global_var(astree* root) {
    astree* type;
    if(root->children.size())
        type = root->children[0];
    else {
        DEBUGF('I', "gen global var: %s NO children\n",
                get_decl_name(root));
        return;
    }
    const char* reg_name = get_decl_name(type);
    root->reg_name = reg_name;

    fprintf(outfile, "%s ", get_oil_type(type));
    fprintf(outfile, "%s;\n", reg_name);
}

void interm_generator::gen_param(astree* root) {
    DEBUGF('I', "gen param: %d %s\n",
            root->block_nr, get_decl_name(root));
    const char* reg_name;    
    
    fprintf(outfile, "%s ", get_oil_type(root));
    
    reg_name = string_to_char("_" + to_string(root->block_nr)
        + "_" + string(get_decl_name(root)));
    root->reg_name = reg_name;

    fprintf(outfile, "%s", reg_name);
}

const char* get_rid_star(const char* type) {
    int len = strlen(type);
    char* rt = new char[len + 1];
    memset(rt, 0, sizeof(char) * (len + 1));
    snprintf(rt, len + 1, "%s", type);
    rt[len-1] = '\0';
    return rt;
}

const char* add_a_star(const char* type) {
    int len = strlen(type);
    char* rt = new char[len + 2];
    memset(rt, 0, sizeof(char) * (len + 1));
    snprintf(rt + 1, len + 1, "%s", type);
    rt[0] = '*';
    return rt;
}

const char* get_field_reg(astree* root) {
    symbol_node* node = root->symbol_item;
    if(!node || !node->type_name) {
        DEBUGF('I', "get field reg INVALID\n");
        return NULL;
    }
    string s = string(node->type_name) + "_"
        + string(get_decl_name(root));
    return string_to_char(s);
}

const char* interm_generator::gen_expr(astree* root) {
    attr_bitset& attrs = root->attributes;
    const char* oper = get_yy_name(root);
    
    if(type_test(attrs, attr::VREG)) {
        if(!strcmp(oper, "CALL")) {
            if(!root->children.size()) {
                DEBUGF('I', "call INVALID\n");
                return NULL;
            }
            astree* func = root->children[0];
            attr_bitset& attrs = func->attributes;
            const char* type = NULL;
            const char* reg = NULL;
            
            fprintf(outfile, "\t");
            // not void, need a REG
            if(!type_test(attrs, attr::VOID)) {
                type = get_oil_type(func);
                if(!type_test(attrs, attr::ARRAY) &&
                        type_test(attrs, attr::INT))
                    reg = string_to_char("i" + to_string(++seq_nr));
                else
                    reg = string_to_char("p" + to_string(++seq_nr));

                if(!type || !reg) {
                    DEBUGF('I', "call ret INVALID\n");
                    return NULL;
                }
                fprintf(outfile, "%s %s = ", type, reg);
            }
            //print name
            fprintf(outfile, "%s (", get_decl_name(func));
            //print params
            for(size_t i = 1; i < root->children.size(); ++i) {
                if(i != 1) fprintf(outfile, ", ");
                fprintf(outfile, "%s", gen_expr(root->children[i]));
            }
            fprintf(outfile, ");\n");
            return reg;
        }
        else if(!strcmp(oper, "NEWSTR")) {
            if(!root->children.size()) {
                DEBUGF('I', "newstr INVALID\n");
                return NULL;
            }
            const char* reg = string_to_char("p" + 
                    to_string(++seq_nr));
            const char* opnd = gen_expr(root->children[0]);
            fprintf(outfile, 
                    "\tchar* %s = xcalloc (%s, sizeof (char));\n",
                    reg, opnd);
            return reg;
        }
        else if(!strcmp(oper, "NEW")) {
            if(!root->children.size()) {
                DEBUGF('I', "new INVALID\n");
                return NULL;
            }
            const char* type = get_oil_type(root->children[0]);
            const char* reg = string_to_char("p" + 
                    to_string(++seq_nr));
            fprintf(outfile, "\t%s %s = xcalloc (1, sizeof (%s));\n",
                    type, reg, get_rid_star(type));
            return reg;
        }
        else if(!strcmp(oper, "NEWARRAY")) {
            if(root->children.size() < 2) {
                DEBUGF('I', "newarray INVALID\n");
                return NULL;
            }
            const char* type = get_array_type(root);
            const char* reg = string_to_char("p" +
                    to_string(++seq_nr));
            const char* opnd = gen_expr(root->children[1]);
            fprintf(outfile, "\t%s %s = xcalloc (%s, sizeof (%s));\n",
                    type, reg, opnd, get_rid_star(type));
            return reg;
        }
        // unop
        else if(root->children.size() == 1) {
            const char* rreg = gen_expr(root->children[0]);
            const char* lreg = string_to_char("i" + 
                    to_string(++seq_nr));
            fprintf(outfile, "\t%s = %s %s;\n", lreg,
                    root->lexinfo->c_str(), rreg);
            return lreg;
        }
        // binop
        else if(root->children.size() == 2) {
            const char* lreg = gen_expr(root->children[0]);
            const char* rreg = gen_expr(root->children[1]);
            const char* mreg = string_to_char("i" + 
                    to_string(++seq_nr));
            fprintf(outfile, "\t%s = %s %s %s;\n", mreg, lreg,
                    root->lexinfo->c_str(), rreg);
            return mreg;
        } 
        else {
            DEBUGF('I', "get expr INVALID VREG: %s\n",
                    root->lexinfo->c_str());
        }
    }
    else if(type_test(attrs, attr::CONST)) {
        if(type_test(attrs, attr::NULLX)) {
            return string_to_char("0");
        }
        else if(type_test(attrs, attr::INT)) {
            return string_to_char(*(root->lexinfo));
        }
        else if(type_test(attrs, attr::STRING)) {
            return root->reg_name;
        }
        else {
            DEBUGF('I', "get expr INVALID CONS: %s\n",
                    root->lexinfo->c_str());
        }
    }
    else if(type_test(attrs, attr::VARIABLE)) {
        if(type_test(attrs, attr::LOCAL) ||
                type_test(attrs, attr::PARAM))
            return string_to_char("_" + to_string(root->block_nr)
                    + "_" + *(root->lexinfo));
        else
            return string_to_char(*(root->lexinfo));
    }
    // selection !
    else if(type_test(attrs, attr::VADDR)) {
        const char* select = get_yy_name(root);
        astree* l;
        astree* r;
        get_children(root, l, r);
        if(!strcmp(select, "ARROW")) {
            const char* expr = gen_expr(l);
            const char* field = get_field_reg(r);
            const char* type = get_oil_type(r);
            const char* reg = string_to_char("a"
                    + to_string(++seq_nr));
            fprintf(outfile, "\t%s* %s = &%s->%s;\n",
                    type, reg, expr, field);
            return add_a_star(reg);
        }
        else if(!strcmp(select, "INDEX")) {
            const char* lreg = gen_expr(l);
            const char* rreg = gen_expr(r);
            const char* type = get_oil_type(root);
            const char* reg = string_to_char("a"
                    + to_string(++seq_nr));
            fprintf(outfile, "\t%s* %s = &%s[%s];\n",
                    type, reg, lreg, rreg);
            return add_a_star(reg);
        }
        else
            DEBUGF('I', "selection INVALID\n");
        return NULL;
    }
    else {
        DEBUGF('I', "gen expr INVALID: %s",
                root->lexinfo->c_str());
    }
    return "some_reg_name";
}

void interm_generator::gen_local_var(astree* root) {
    astree* name;
    astree* expr;
    get_children(root, name, expr);
    if(!name || !expr) {
        DEBUGF('I', "gen local var: %s INVALID\n\n",
                get_decl_name(root));
        return;
    }
    DEBUGF('I', "gen local var: %s\n", get_decl_name(name));

    const char* type = get_oil_type(name);
    const char* rreg = gen_expr(expr);
    const char* lreg = string_to_char(
            "_" + to_string(root->block_nr) + 
            "_" + string(get_decl_name(name)));
    fprintf(outfile, "\t%s %s = %s;\n", type, lreg, rreg);
}

void interm_generator::gen_func(astree* root) {
    astree* name;
    astree* param;
    astree* block;
    get_children(root, name, param, block);
    if(!name || !param || !block) {
        DEBUGF('I', "gen func: NOT enough children\n");
        return;
    }
    // dump func name
    fprintf(outfile, "%s ", get_oil_type(name));
    fprintf(outfile, "%s (", get_decl_name(name));
    
    // dump params
    if(!param->children.size())
        fprintf(outfile, "void)\n");
    else
        fprintf(outfile, "\n");
    for(size_t i = 0; i < param->children.size(); ++i) {
        fprintf(outfile, "\t");
        gen_param(param->children[i]);
        if(i + 1 == param->children.size())
            fprintf(outfile, ")\n");
        else
            fprintf(outfile, ",\n");
    }

    // dump stmts
    fprintf(outfile, "{\n");
    // dump local decl
    size_t i = 0;
    for(; i < block->children.size(); ++i) {
        astree* child = block->children[i];
        const char* name = get_yy_name(child);
       
        if(strcmp(name, "VARDECL")) break;
        gen_local_var(child);
    }
    fprintf(outfile, "}\n");
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

    // get all global var
    for(size_t i = 0; i < root->children.size(); ++i) {
        astree* child = root->children[i];
        name = get_yy_name(child);
        if(strcmp(name, "VARDECL") == 0)
            gen_global_var(child);
    }

    //get all functions
    for(size_t i = 0; i < root->children.size(); ++i) {
        astree* child = root->children[i];
        name = get_yy_name(child);
        if(strcmp(name, "FUNCTION") == 0)
            gen_func(child);
    }

}

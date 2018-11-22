#include <string.h>

#include "astree.h"
#include "lyutils.h"
#include "symbol.h"

symbol_generator::symbol_generator() {
    structure = new symbol_table();
    global = new symbol_table();
    local = global;
    block_nr = 0;
}

symbol_node::symbol_node(location l, size_t nr) {
    attributes = *(new attr_bitset());
    sequence = 0;
    fields = nullptr;
    lloc = l;
    block_nr = nr;
    parameters = nullptr;
}

enum class types {
    BINOP, UNOP, COMPARE, RETURN, ASSIGN, ALLOC, IDENT,
  CALL, INDEX, FILED, CON  
};

types type_hash(const char* s) {
    static const unordered_map<string, types> hash {
        {"+",    types::BINOP},
            {"-",    types::BINOP},
            {"*",    types::BINOP},
            {"/",    types::BINOP},
            {"%",    types::BINOP},
            {"POS",  types::UNOP},
            {"NEG",  types::UNOP},
            {"NOT",  types::UNOP},
            {"EQ",   types::COMPARE},
            {"NQ",   types::COMPARE},
            {"<",    types::COMPARE},
            {">",    types::COMPARE},
            {"LE",   types::COMPARE},
            {"GE",   types::COMPARE},
            {"=",       types::ASSIGN},
            {"VARDECL", types::ASSIGN},
            {"RETURN", types::RETURN},
            {"NEW", types::ALLOC},
            {"NEWSTR", types::ALLOC},
            {"NEWARRAY", types::ALLOC},
            {"IDENT", types::IDENT},
            {"CALL", types::CALL},
            {"INDEX", types::INDEX},
            {"FILED", types::FILED},
            {"CHARCON", types::CON},
            {"STRINGCON", types::CON},
            {"INTCON", types::CON},
            {"NULL", types::CON}
    };

    return hash.find(string(s))->second;
}

void symbol_generator::generate(astree* root) {
//    symbol_node* node = new symbol_node(root->lloc, block_nr);
    for(const auto& child: root->children) {
        generate(child);
    }

    const char* tname = parser::get_tname (root->symbol);
    if (strstr (tname, "TOK_") == tname) tname += 4;
    root->block_nr = block_nr;

    if (!strcmp(tname, "FUNCTION")) {
    }
    else if (!strcmp(tname, "STRUCT")) {
    }
    else {
        type_check(root, type_hash(tname));     
    }
}

void type_check(const astree* root, types type) {
    switch(type) {
        case types::BINOP:
;
        default:
;
    }
}




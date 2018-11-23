#include <string.h>

#include "astree.h"
#include "lyutils.h"
#include "symbol.h"

symbol_generator::symbol_generator() {
    structure = new symbol_table();
    global = new symbol_table();
    local = global;
    block_nr = 0;
    func_node = nullptr;
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
            {"VARDECL", types::VARDECL},
            {"RETURN", types::RETURN},
            {"NEW", types::NEW},
            {"NEWSTR", types::NEWSTR},
            {"NEWARRAY", types::NEWARRAY},
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

void type_set(astree* root, attr attri) {
    root->attributes.set(static_cast<int> (attri));
}

void type_set(astree* root, attr_set& attris) {
    root->attributes = attris;
}

bool type_test(const astree* root, attr attri) {
    return root->attributes.test(static_cast<int> (attri));
}

void type_check(astree* root, types type) {
    const astree* a = nullptr;
    const astree* b = nullptr;
    if(root->children.size())
        a = root->children[0];
    if(root->children.size() > 1)
        b = root->children[1];

    int shr{};
    switch(type) {
        case types::BINOP:
            if(type_test(a, attr::INT) &&
                        type_test(b, attr::INT)) {
                type_set(root, attr::INT);
                type_set(root, attr::VREG);
            }
            else {
              //  err_print("incompatible types");
            }
            break;
        case types::UNOP:
            if(type_test(a, attr::INT)) {
                type_set(root, attr::INT);
                type_set(root, attr::VREG);    
            }
            else {}
            break;
        case types::COMPARE:
            shr = static_cast<int>(attr::BITSET_SIZE) -
                        static_cast<int>(attr::ARRAY);
            if(a->attributes>>shr == b->attributes>>shr) {
                type_set(root, attr::INT);
                type_set(root, attr::VREG);
            }
            else {}
            break;
        case types::RETURN:
            //compatible with func
            break;
        case types::VARDECL:
            shr = static_cast<int>(attr::BITSET_SIZE) -
                        static_cast<int>(attr::ARRAY);
            if(a->attributes>>shr == b->attributes>>shr) {
            }
            else {}
            break;
        case types::ASSIGN:
            shr = static_cast<int>(attr::BITSET_SIZE) -
                        static_cast<int>(attr::ARRAY);
            if(a->attributes>>shr == b->attributes>>shr &&
                    a->attributes.test(attr::LVAL)) {
                type_set(root, a->attributes);
                type_set(root, attr::VREG);
            }
            else {}
            break;
        case types::NEW:
            type_set(root, a->attributes);
            type_set(root, attr::VREG);
            break;
        default:
            break;
    }
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



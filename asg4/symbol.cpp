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

enum class types;

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
            {"DECLID", types::IDENT},
            {"TYPEID", types::TYPEID},
            {"CALL", types::CALL},
            {"INDEX", types::INDEX},
            {"FILED", types::FILED},
            {"CHARCON", types::INTCON},
            {"STRINGCON", types::STRCON},
            {"INTCON", types::INTCON},
            {"NULL", types::NULLCON}
    };

    return hash.find(string(s))->second;
}

void type_set(astree* root, attr attri) {
    root->attributes.set(static_cast<size_t> (attri));
}

void type_set(astree* root, const attr_bitset& attris) {
    root->attributes = attris;
}

bool type_test(const astree* root, attr attri) {
    return root->attributes.test(static_cast<size_t> (attri));
}

bool is_compatible(const attr_bitset& a, const attr_bitset& b) {
    static size_t shr = static_cast<size_t>(attr::BITSET_SIZE) -
        static_cast<size_t>(attr::ARRAY);
    return (a>>shr) == (b>>shr);
}

void symbol_generator::type_check(astree* root, types type) {
    const astree* a = nullptr;
    const astree* b = nullptr;
    symbol_node* found = nullptr;
    if(root->children.size())
        a = root->children[0];
    if(root->children.size() > 1)
        b = root->children[1];

    size_t shr{};
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
            if(is_compatible(a->attributes, b->attributes)) {
                type_set(root, attr::INT);
                type_set(root, attr::VREG);
            }
            else {}
            break;
        case types::RETURN:
            //compatible with func
            break;
        case types::VARDECL:
            if(is_compatible(a->attributes, b->attributes)) {
            }
            else {}
            break;
        case types::ASSIGN:
            if(is_compatible(a->attributes, b->attributes) &&
                    type_test(a, attr::LVAL)) {
                type_set(root, a->attributes);
                type_set(root, attr::VREG);
            }
            else {}
            break;
        case types::NEW:
            type_set(root, a->attributes);
            type_set(root, attr::VREG);
            break;
        case types::NEWSTR:
            type_set(root, attr::STRING);
            type_set(root, attr::VREG);
            break;
        case types::NEWARRAY:
            type_set(root, a->attributes);
            type_set(root, attr::ARRAY);
            type_set(root, attr::VREG);
            break;
        case types::CALL: 
            {
                vector<symbol_node*>* params = a->symbol_item->parameters;
                if(params->size() == root->children.size() - 1) {
                    auto i = root->children.begin() + 1;
                    auto j = params->begin();
                    for(; i < root->children.end(); ++i, ++j) {
                        if(is_compatible((*i)->attributes, (*j)->attributes)) continue;
                        else {}
                    }
                }
                else{}
                break;
            }
        case types::IDENT: 
            {
                auto found = local->find(*root->lexinfo);
                if(found == local->end())
                    found = global->find(*root->lexinfo);
                if(found != global->end()) {
                    root->symbol_item = found->second;
                    type_set(root, found->second->attributes);
                }
                else{}
                break;
            }
        case types::TYPEID: 
            {
                auto found = structure->find(*root->lexinfo);
                if(found != structure->end()) {
                    root->symbol_item = found->second;
                    type_set(root, found->second->attributes);
                }
                else{}
                break;
            }
        case types::INDEX: 
            {
                shr = static_cast<size_t>(attr::BITSET_SIZE) -
                    static_cast<size_t>(attr::STRUCT);
                if((type_test(a, attr::INT) || type_test(a, attr::STRING) || 
                            type_test(a, attr::STRUCT) || type_test(a, attr::VOID)) 
                        && type_test(a, attr::ARRAY) && type_test(b, attr::INT)) {
                    type_set(root, (a->attributes>>shr)<<shr);
                    type_set(root, attr::VADDR);
                    type_set(root, attr::LVAL);
                }
                else if(type_test(a, attr::STRING) && type_test(b, attr::INT)) {
                    type_set(root, attr::INT);
                    type_set(root, attr::VADDR);
                    type_set(root, attr::LVAL);
                }
                else {}
                break;
            }
        case types::FILED:
            break;
        case types::INTCON:
            type_set(root, attr::INT);
            type_set(root, attr::CONST);
            break;
        case types::STRCON:
            type_set(root, attr::STRING);
            type_set(root, attr::CONST);
            break;
        case types::NULLCON:
            type_set(root, attr::NULLX);
            type_set(root, attr::CONST);
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



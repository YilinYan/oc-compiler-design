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

void type_set(symbol_node* node, attr attri) {
    node->attributes.set(static_cast<size_t> (attri));
}

bool type_test(const astree* root, attr attri) {
    return root->attributes.test(static_cast<size_t> (attri));
}

bool type_test(const attr_bitset& attrs, attr attri) {
    return attrs.test(static_cast<size_t> (attri));
}

bool is_compatible(const attr_bitset& a, const attr_bitset& b) {
    bool rt = false;
    static size_t shr = static_cast<size_t>(attr::BITSET_SIZE) -
        static_cast<size_t>(attr::ARRAY);
    rt |= ((a>>shr) == (b>>shr));
    rt |= ((type_test(a, attr::ARRAY)
                || type_test(a, attr::STRUCT)
                || type_test(a, attr::STRING)
                ) && type_test(b, attr::NULLX)); 
    return rt; 
}

void symbol_generator::type_check(astree* root) {
    types type = type_hash(root->lexinfo->c_str());
    const astree* a = nullptr;
    const astree* b = nullptr;
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
            lookup_var(root);
            break;
            
        case types::TYPEID: 
            lookup_struct(root);
            break;
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
            {
                auto i = a->symbol_item->fields->find(*(b->lexinfo)); 
                if(i != a->symbol_item->fields->end()) {
                    type_set(root, attr::VADDR);
                    type_set(root, attr::LVAL);
                    type_set(root, i->second->attributes);
                }
                else
                    errllocprintf(root->lloc, "no such field in type %s\n", 
                            a->lexinfo->c_str());
                break;
            }
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

attr get_base(const astree* root) {
    const string& a = *(root->lexinfo);
    if(a == "int") return attr::INT;
    else if(a == "string") return attr::STRING;
    else if(a == "[]") return attr::ARRAY;
    else if(a == "void") {
        errllocprintf(root->lloc, 
                "invalid void type declaration: %s",
                a.c_str());
        return attr::VOID;
    }
    else return attr::STRUCT;
}

symbol_node* symbol_generator::lookup_struct(astree* root) {
    auto type = structure->find(*(root->lexinfo));
    if(type != structure->end()) {
        root->symbol_item = type->second;
        root->attributes = type->second->attributes;
        return type->second;
    }
    errllocprintf(root->lloc, 
            "no such type: %s",
            root->lexinfo->c_str());
    return nullptr;    
}

symbol_node* symbol_generator::lookup_var(astree* root) {
    auto type = local->find(*(root->lexinfo));
    if(type == local->end())
        type = global->find(*(root->lexinfo));
    if(type != global->end()) {
        root->symbol_item = type->second;
        root->attributes = type->second->attributes;
        return type->second;
    }
    errllocprintf(root->lloc, 
            "no such variable: %s",
            root->lexinfo->c_str());
    return nullptr;
}

symbol_node* symbol_generator::ident_decl
(astree* root, symbol_table* table) {
    astree* l = nullptr;
    astree* r = nullptr;
    astree* var = nullptr;
    if(root->children.size())
        l = root->children[0];
    if(root->children.size() > 1)
        r = root->children[1];
    symbol_node* symbol = new symbol_node(root->lloc, root->block_nr);

    attr rootbase = get_base(root);
    type_set(symbol, rootbase);
    type_set(symbol, attr::VARIABLE);
    type_set(symbol, attr::LVAL);
    if(rootbase == attr::STRUCT) {
        symbol_node* type = lookup_struct(root);
        symbol->lloc = l->lloc;
        symbol->fields = type->fields;
        var = l;
    }
    else if(rootbase == attr::ARRAY) {
        attr lbase = get_base(l);
        if(lbase == attr::STRUCT) {
            symbol_node* type = lookup_struct(l);
            symbol->fields = type->fields;
        }
        type_set(symbol, lbase);
        symbol->lloc = r->lloc;
        var = r;
    }
    else {
        symbol->lloc = l->lloc;
        var = l;
    }
    
    table->insert({*(var->lexinfo), symbol});
    return symbol;
}

void symbol_generator::generate(astree* root) {
    /*
     * symbol_node* node = new symbol_node(root->lloc, block_nr);
    for(const auto& child: root->children) {
        generate(child);
    }
    */
    astree* l = nullptr;
    astree* r = nullptr;
    if(root->children.size())
        l = root->children[0];
    if(root->children.size() > 1)
        r = root->children[1];

    const char* tname = parser::get_tname (root->symbol);
    if (strstr (tname, "TOK_") == tname) tname += 4;
    root->block_nr = block_nr;

    if (!strcmp(tname, "FUNCTION")) {
    }
    else if (!strcmp(tname, "STRUCT")) {
    }
    else if(!strcmp(tname, "VARDECL")) {
        type_check(r);
        symbol_node* var = ident_decl(l, global);       
        if(is_compatible(var->attributes, r->attributes))
            type_set(root, var->attributes);
        else
            errllocprintf(root->lloc,
                    "incompatible types for %s\n", root->lexinfo->c_str());
    }
    else {
        errllocprintf(root->lloc, 
                "symbol_generate: invalid: %s", 
                root->lexinfo->c_str());
    }
}



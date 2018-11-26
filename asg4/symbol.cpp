#include <string.h>
#include <iostream>

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
    type_name = "";
}

enum class types;
const string attr_to_string (size_t attri);

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
    auto iter = hash.find(string(s));
    if(iter != hash.end())
        return iter->second;

    throw invalid_argument (string (__PRETTY_FUNCTION__) + ": "
            + string (s));       
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
    rt |= ((a<<shr) == (b<<shr));
    rt |= ((type_test(a, attr::ARRAY)
                || type_test(a, attr::STRUCT)
                || type_test(a, attr::STRING)
                ) && type_test(b, attr::NULLX)); 
    return rt; 
}

void symbol_generator::type_check(astree* root) {
    const char* tname = parser::get_tname (root->symbol);
    if (strstr (tname, "TOK_") == tname) tname += 4;
    types type = type_hash(tname);
        
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
                    type_set(root, (a->attributes<<shr)>>shr);
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
            "undefined type: %s\n",
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
            "undefined variable: %s\n",
            root->lexinfo->c_str());
    return nullptr;
}

void table_insert(const string& s, symbol_node* node, symbol_table* table) {
    auto i = table->find(s);
    if(i == table->end()) {
        table->insert({s, node});
        return;
    }
    errllocprintf(node->lloc, "duplicate variable %s\n", s.c_str()); 
}

symbol_node* symbol_generator::ident_decl
(astree* root, symbol_table* table, const string& decl_type, size_t seq) {
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
    if(decl_type == "ident") {
        type_set(symbol, attr::VARIABLE);
        type_set(symbol, attr::LVAL);
    }
    else if(decl_type == "func") {
        // insert or get proto 
        type_set(symbol, attr::FUNCTION);       
    }
    else if(decl_type == "field") {
        type_set(symbol, attr::FIELD);
    }
    else if(decl_type == "param") {
        symbol->block_nr = root->block_nr = block_nr;
        type_set(symbol, attr::VARIABLE);
        type_set(symbol, attr::PARAM);
        type_set(symbol, attr::LVAL);
    }
    else if(decl_type == "local") {
        symbol->block_nr = root->block_nr = block_nr;
        type_set(symbol, attr::VARIABLE);
        type_set(symbol, attr::LOCAL);
        type_set(symbol, attr::LVAL);
    }

    if(rootbase == attr::STRUCT) {
        symbol_node* type = lookup_struct(root);
        if(type == nullptr) {
            return nullptr;
        }
        symbol->lloc = l->lloc;
        symbol->fields = type->fields;
        symbol->type_name = type->type_name;
        var = l;
    }
    else if(rootbase == attr::ARRAY) {
        attr lbase = get_base(l);
        if(lbase == attr::STRUCT) {
            symbol_node* type = lookup_struct(l);
            if(type == nullptr) {
                return nullptr;
            }
            symbol->fields = type->fields;
            symbol->type_name = type->type_name;
        }
        type_set(symbol, lbase);
        symbol->lloc = r->lloc;
        var = r;
    }
    else {
        symbol->lloc = l->lloc;
        var = l;
    }
 
    symbol->sequence = seq;   
    var->block_nr = root->block_nr;
    var->symbol_item = symbol;
    var->attributes = symbol->attributes;

    table_insert(*(var->lexinfo), symbol, table);
    return symbol;
}
/*
symbol_node* symbol_generator::field_decl
(astree* root, symbol_table* table, int seq) {
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
    type_set(symbol, attr::FIELD);
    if(rootbase == attr::STRUCT) {
        symbol_node* type = lookup_struct(root);
        if(type == nullptr) {
            return nullptr;
        }
        symbol->lloc = l->lloc;
        symbol->fields = type->fields;
        symbol->type_name = type->type_name;
        var = l;
    }
    else if(rootbase == attr::ARRAY) {
        attr lbase = get_base(l);
        if(lbase == attr::STRUCT) {
            symbol_node* type = lookup_struct(l);
            if(type == nullptr) {
                return nullptr;
            }
            symbol->fields = type->fields;
            symbol->type_name = type->type_name;
        }
        type_set(symbol, lbase);
        symbol->lloc = r->lloc;
        var = r;
    }
    else {
        symbol->lloc = l->lloc;
        var = l;
    }
    
    symbol->sequence = seq;
    var->block_nr = root->block_nr;
    var->symbol_item = symbol;
    var->attributes = symbol->attributes;

    table_insert(*(var->lexinfo), symbol, table);
    return symbol;
}

symbol_node* symbol_generator::local_decl
(astree* root, symbol_table* table, size_t seq) {
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
        if(type == nullptr) {
            return nullptr;
        }
        symbol->lloc = l->lloc;
        symbol->fields = type->fields;
        symbol->type_name = type->type_name;
        var = l;
    }
    else if(rootbase == attr::ARRAY) {
        attr lbase = get_base(l);
        if(lbase == attr::STRUCT) {
            symbol_node* type = lookup_struct(l);
            if(type == nullptr) {
                return nullptr;
            }
            symbol->fields = type->fields;
            symbol->type_name = type->type_name;
        }
        type_set(symbol, lbase);
        symbol->lloc = r->lloc;
        var = r;
    }
    else {
        symbol->lloc = l->lloc;
        var = l;
    }
    
    symbol->sequence = seq;
    var->block_nr = root->block_nr;
    var->symbol_item = symbol;
    var->attributes = symbol->attributes;

    table_insert(*(var->lexinfo), symbol, table);
    return symbol;
}
*/

void print_attr(attr_bitset& attrs, const string& name) {
    for(size_t i = 0; i < static_cast<size_t>(attr::BITSET_SIZE); ++i) {
        if(attrs.test(i)) {
            const char* s = attr_to_string(i).c_str();
            printf(" %s", s);
            if(!strcmp(s, "struct")) {
                printf(" \"%s\"", name.c_str());
            }
        }
    }
    printf("\n");
}

void symbol_generator::generate(astree* root) {
    
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
        symbol_node* func = ident_decl(l, global, "func", -1);

        if(func != nullptr) {
            symbol_table* table = new symbol_table();
            ++block_nr;
            int j = 0;
            for(auto i = r->children.begin();
                    i != r->children.end(); ++i, ++j) {
                symbol_node* para = ident_decl(*i, table, "param", j);
                func->parameters->push_back(para);
            }
        }
    }
    else if(!strcmp(tname, "PROTO")) {
        symbol_node* func = ident_decl(l, global, "func", -1);

        if(func != nullptr) {
            symbol_table* table = new symbol_table();

            ++block_nr;
            int j = 0;
            for(auto i = r->children.begin();
                    i != r->children.end(); ++i, ++j) {
                symbol_node* para = ident_decl(*i, table, "param", j);
                func->parameters->push_back(para);
            }
        }
    }
    else if (!strcmp(tname, "STRUCT")) {
        symbol_table* table = new symbol_table();
        symbol_node* node = new symbol_node(l->lloc, 0);
        type_set(node, attr::STRUCT);
        type_set(node, attr::TYPEID);
        node->fields = table;
        node->type_name = *(l->lexinfo);
        table_insert(*(l->lexinfo), node, structure);
        table_insert(*(l->lexinfo), node, table); 
        
        l->symbol_item = node;
        l->attributes = node->attributes;

        int j = 0;
        for(auto i = r->children.begin();
                i != r->children.end(); ++i, ++j) {
            ident_decl(*i, table, "field", j);
        }
    }
    else if(!strcmp(tname, "VARDECL")) {       
        type_check(r);
        symbol_node* var = ident_decl(l, global, "ident", -1);       
        if(var == nullptr) {
        }
        else if(is_compatible(var->attributes, r->attributes)){
 //           type_set(root, var->attributes);
        }
        else {
            errllocprintf(root->lloc,
                    "incompatible types for %s\n", root->lexinfo->c_str());
            print_attr(var->attributes, var->type_name);
            print_attr(r->attributes, r->symbol_item->type_name);
        }
    }
    else if(!strcmp(tname, "ROOT")) {
        for(auto i = root->children.begin();
                i != root->children.end(); ++i)
            generate(*i);
    }
    else {
        errllocprintf(root->lloc, 
                "symbol_generate: invalid: %s\n", 
                root->lexinfo->c_str());
    }
}



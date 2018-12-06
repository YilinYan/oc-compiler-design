#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "astree.h"
#include "lyutils.h"
#include "symbol.h"

#define SOME_NUM 0x3f3f3f3f

const char* get_decl_name(astree* root) {
    if (root->children.size() == 0) {
        DEBUGF('S', "get_decl_name: %s have NO children\n\n",
                root->lexinfo->c_str());
        return root->lexinfo->c_str();
    }
    return (*(root->children.end() - 1))->lexinfo->c_str();
}

symbol_generator::symbol_generator() {
    structure = new symbol_table();
    global = new symbol_table();
    local = global;
    block_nr = 0;
    block_nxt = 0;
    func_node = nullptr;
    outfile = nullptr;
}

symbol_generator::symbol_generator(FILE* file) {
    structure = new symbol_table();
    global = new symbol_table();
    local = global;
    block_nr = 0;
    block_nxt = 0;
    func_node = nullptr;
    outfile = file;
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

types type_name_hash(const char* s) {
    static const unordered_map<string, types> hash {
            {"'+'",    types::BINOP},
            {"'-'",    types::BINOP},
            {"'*'",    types::BINOP},
            {"'/'",    types::BINOP},
            {"'%'",    types::BINOP},
            {"POS",    types::UNOP},
            {"NEG",    types::UNOP},
            {"NOT",    types::UNOP},
            {"EQ",     types::COMPARE},
            {"NE",     types::COMPARE},
            {"'<'",    types::COMPARE},
            {"'>'",    types::COMPARE},
            {"LE",     types::COMPARE},
            {"GE",     types::COMPARE},
            {"'='",    types::ASSIGN},
            {"VARDECL",types::VARDECL},
            {"RETURN", types::RETURN},
            {"NEW",    types::NEW},
            {"NEWSTR", types::NEWSTR},
            {"NEWARRAY", types::NEWARRAY},
            {"IDENT",  types::IDENT},
            {"DECLID", types::IDENT},
            {"TYPEID", types::TYPEID},
            {"CALL",   types::CALL},
            {"INDEX",  types::INDEX},
            {"ARROW",  types::ARROW},
            {"FIELD",  types::FIELD},
            {"CHARCON",types::INTCON},
            {"STRINGCON", types::STRCON},
            {"INTCON", types::INTCON},
            {"NULL",   types::NULLCON},
            {"STRING", types::STRING},
            {"INT",    types::INT},
    };
    auto iter = hash.find(string(s));

    if(iter != hash.end())
        return iter->second;

    return types::NOMATTER;

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
/*
    cout << "--------------" << endl;
    cout << a << "\t" << b << endl;
    cout << (a << shr) << "\t" << (b << shr) << endl;
    cout << ((a<<shr) == (b<<shr)) << endl;
  */      
    rt |= ((a<<shr) == (b<<shr));
    
//    cout << "-----"<< rt << endl;
    rt |= ((type_test(a, attr::ARRAY)
                || type_test(a, attr::STRUCT)
                || type_test(a, attr::STRING)
           ) && type_test(b, attr::NULLX)); 
//    cout << "-----"<< rt << endl;
    
    return rt; 
}

bool is_compatible(const vector<symbol_node*>* a, 
        const vector<symbol_node*>* b) {
    if(a->size() != b->size()) return false;
    int len = a->size();
    for(int i = 0; i < len; ++i) {
        if(!is_compatible((*a)[i]->attributes, (*b)[i]->attributes))
            return false;
    }
    return true;
}

void symbol_generator::type_check(astree* root) {
    const char* tname = parser::get_tname (root->symbol);
    if (strstr (tname, "TOK_") == tname) tname += 4;
    types type = type_name_hash(tname);

    for(auto child : root->children)
        type_check(child);

    root->block_nr = block_nr;
    astree* a = nullptr;
    astree* b = nullptr;
    if(root->children.size())
        a = root->children[0];
    if(root->children.size() > 1)
        b = root->children[1];

    DEBUGF('S', "type check: %s ---- %s\n\n",
            root->lexinfo->c_str(), tname);

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
            {
                if(!func_node) {
                    errllocprintf(root->lloc, 
                        "%s", "return: NOT in a function\n\n");
                    break;
                }
                if(root->children.size() == 0 && 
                        type_test(func_node->attributes, 
                            attr::VOID)) {
                    DEBUGF('S', "return void\n\n");            
                    break;
                }
                if(a && is_compatible(func_node->attributes, 
                        a->attributes)) {
                    DEBUGF('S', "return compatible\n\n");
                    break;
                }
                errllocprintf(root->lloc, 
                        "%s", "incompatible return types\n");
                break;
            }
        case types::ASSIGN:
            if(is_compatible(a->attributes, b->attributes) &&
                    type_test(a, attr::LVAL)) {
                type_set(root, a->attributes);
                type_set(root, attr::VREG);
            }
            else {
                DEBUGF('S', "---------------assign\n%s\n%s\n",
                        attrs_to_string(a->attributes, "").c_str(),
                        attrs_to_string(b->attributes, "").c_str());
                errllocprintf(root->lloc, 
                    "%s", "incompatible assign\n");
            }
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
                if(!a || a->symbol_item == nullptr) {
                    errllocprintf(root->lloc, "%s",
                            "call INVALID function\n");
                    break; 
                }
                vector<symbol_node*>* params = 
                    a->symbol_item->parameters;
                if(params->size() == root->children.size() - 1) {
                    auto i = root->children.begin() + 1;
                    auto j = params->begin();

                    //cout << "------  " << *(a->lexinfo) << endl;
                    //cout << *((*i)->lexinfo) << "    " << 
                    // j - params->begin() << endl;
                    for(; i < root->children.end(); ++i, ++j) {
                        if(is_compatible((*i)->attributes, 
                                    (*j)->attributes)) continue;
                        else {
                            astree* l = *i;
                            symbol_node* r = *j;
                            
                            //__fUNC__
                            if(!strcmp("__FUNC__", get_decl_name(l)))
                                    return;
                            
                            errllocprintf(root->lloc, 
                                    "incompatible parameter \n\t%s\n",
                                    (
                                        attrs_to_string(l->attributes, 
                                            l->symbol_item ? 
                                            l->symbol_item->
                                            type_name : "") + "\n\t"
                                        + attrs_to_string(
                                            r->attributes, 
                                            r->type_name)).c_str());
                            return;
                        }
                    }
                    type_set(root, a->symbol_item->attributes);
                    type_set(root, attr::VREG);
                }
                else{
                    errllocprintf(a->lloc, 
                            "incompatible parameter %s\n",
                            a->lexinfo->c_str());
                }
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
                if((type_test(a, attr::INT) 
                            || type_test(a, attr::STRING) 
                            || type_test(a, attr::STRUCT) 
                            || type_test(a, attr::VOID)) 
                        && type_test(a, attr::ARRAY) && 
                        type_test(b, attr::INT)) {
                    type_set(root, (a->attributes<<shr)>>shr);
                    type_set(root, attr::VADDR);
                    type_set(root, attr::LVAL);
                }
                else if(type_test(a, attr::STRING) 
                        && type_test(b, attr::INT)) {
                    type_set(root, attr::INT);
                    type_set(root, attr::VADDR);
                    type_set(root, attr::LVAL);
                }
                else {
                    errllocprintf(root->lloc, 
                            "incompatible index \n\t%s\n\t%s",
                            (attrs_to_string(a->attributes, 
                                             a->symbol_item ? 
                                             a->symbol_item->
                                             type_name : "") +
                             attrs_to_string(b->attributes, 
                                 b->symbol_item ? 
                                 b->symbol_item->type_name : "")
                            ).c_str());
                }
                break;
            }
        case types::ARROW:
            {
                if(!a || !b) break;
                if(a->symbol_item == nullptr) break;
                if(a->symbol_item->fields == nullptr) break;

                DEBUGF('S', "type check: %s -> %s\n\n",
                        get_decl_name(a), get_decl_name(b));

                auto i = a->symbol_item->fields->find(*(b->lexinfo)); 
                if(i != a->symbol_item->fields->end()) {
                    DEBUGF('S', "field found: %s -> %s\n\n",
                            get_decl_name(a), get_decl_name(b));
                    type_set(root, i->second->attributes);
                    type_set(root, attr::VADDR);
                    type_set(root, attr::LVAL);
                    root->symbol_item = i->second;
                    break;
                }
                const astree* l = a;
                symbol_node* r = i->second;
                errllocprintf(root->lloc, 
                        "undefined field \n\t%s\n", (
                            attrs_to_string(l->attributes, 
                                l->symbol_item ? 
                                l->symbol_item->type_name : "") 
                            + "\n\t"
                            + attrs_to_string(r->attributes, 
                                r->type_name)).c_str());

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
        case types::STRING:
            type_set(root, attr::STRING);
            break;
        case types::INT:
            type_set(root, attr::INT);
            break;
        case types::FIELD:
            break;
        default:
//            errllocprintf(root->lloc, "type check: default: %s\n",
//                    root->lexinfo->c_str());
            break;
    }

}

attr get_base(const astree* root) {
    const string& a = *(root->lexinfo);
    if(a == "int") return attr::INT;
    else if(a == "string") return attr::STRING;
    else if(a == "[]") return attr::ARRAY;
    else if(a == "void") {
        /*        errllocprintf(root->lloc, 
                  "invalid void type declaration: %s",
                  a.c_str());
                  */
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

    //__FUNC__
    if(!strcmp("__FUNC__", get_decl_name(root)))
        return nullptr;

    errllocprintf(root->lloc, 
            "undefined variable: %s\n",
            root->lexinfo->c_str());
    return nullptr;
}

int table_insert(const string& s, symbol_node* node, 
        symbol_table* table) {
    auto i = table->find(s);
    if(i == table->end()) {
        table->insert({s, node});
        return 0;
    }
    errllocprintf(node->lloc, "duplicate variable %s\n", s.c_str()); 
    return -1;
}

symbol_node* symbol_generator::ident_decl(
        astree* root, symbol_table* table, const string& decl_type,
        size_t seq) {
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
//    root->attributes = symbol->attributes;

    table_insert(*(var->lexinfo), symbol, table);
    return symbol;
}

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

const string attrs_to_string(const attr_bitset& attrs, 
        const string& name) {
    string s = "";
    for(size_t i = 0; i < static_cast<size_t>(attr::BITSET_SIZE); 
            ++i) {
        if(attrs.test(i)) {
            s += " " + attr_to_string(i);
            if(attr_to_string(i) == "struct") {
                s += " \"" + name + "\"";
            }
        }
    }
    return s;
}

bool cmp(const symbol_entry& a, 
        const symbol_entry& b) {
    const location& l = (a.second)->lloc;
    const location& r = (b.second)->lloc;
    return l.linenr < r.linenr;
}

void symbol_table_dump(symbol_table* table, FILE* outfile) {
    vector<pair<string, symbol_node*>> V(table->begin(), table->end());
    sort(V.begin(), V.end(), 
            [](symbol_entry a, symbol_entry b) {
            const location& l = (a.second)->lloc;
            const location& r = (b.second)->lloc;
            if(l.filenr != r.filenr) return l.filenr < r.filenr; 
            if(l.linenr != r.linenr) return l.linenr < r.linenr;
            return l.offset < r.offset; });
    for(auto i: V) {
        fprintf(outfile, "   ");
        i.second->dump(i.first.c_str(), outfile);
    }
}

void symbol_node::dump(const char* name, FILE* outfile) {
    fprintf(outfile, "%s (%zd.%zd.%zd) {%zd} %s",
            name, lloc.filenr, lloc.linenr, lloc.offset,
            block_nr, attrs_to_string(attributes, type_name).c_str());
    if(sequence != SOME_NUM)
        fprintf(outfile, " %zd", sequence);
    fprintf(outfile, "\n");
}

symbol_node* lookup_fun(const char* s, symbol_table* global) {
    auto type = global->find(string(s));
    if(type != global->end()) {
        return type->second;
    }
    return nullptr;
}

void symbol_generator::func_stmt(astree* root, symbol_table* table) {
    int len = root->children.size();
    for(int i = 0; i < len; ++i) {
        astree* child = root->children[i];
        astree* l = nullptr;
        astree* r = nullptr;
        if(child->children.size())
            l = child->children[0];
        if(child->children.size() > 1)
            r = child->children[1];
        child->block_nr = block_nr;

        const char* tname = parser::get_tname (child->symbol);
        if (strstr (tname, "TOK_") == tname) tname += 4;

        if(!strcmp(tname, "VARDECL")) {
            type_check(r);
            symbol_node* var = ident_decl(l, table, "local", i);       
            if(var == nullptr) {}
            else if(is_compatible(var->attributes, r->attributes)){
            }
            else {
                errllocprintf(root->lloc,
                        "incompatible types for %s\n", 
                        child->lexinfo->c_str());
                print_attr(var->attributes, var->type_name);
                string tmp = "";
                if(r->symbol_item != nullptr)
                    tmp = r->symbol_item->type_name;
                print_attr(r->attributes, tmp);
            }
        }
        else {
            type_check(child);
        }
    }
}
void get_children(astree* root, astree* &l, astree* &m, astree* &r) {
    if(root->children.size() < 3) {
        DEBUGF('S', "get_children: %s DONT have 3 children\n\n",
                root->lexinfo->c_str());
        return;
    }
    l = root->children[0];
    m = root->children[1];
    r = root->children[2];
}

void get_children(astree* root, astree* &l, astree* &r) {
    if(root->children.size() < 2) {
        DEBUGF('S', "get_children: %s DONT have 2 children\n\n",
                root->lexinfo->c_str());
        if(root->children.size()) l = root->children[0];
        else
            DEBUGF('S', "get_children: %s DONT have 1 children\n\n",
                root->lexinfo->c_str());
        return;
    }
    l = root->children[0];
    r = root->children[1];
}

void symbol_generator::_generate(astree* root) {
    const char* tname = parser::get_tname (root->symbol);
    DEBUGF('S', "generate: get_tname %s\n\n", tname);
    if (!tname) return;
    if(strstr(tname, "TOK_") == tname) tname += 4;

    if (!strcmp(tname, "FUNCTION")) {
        astree* a_ret = nullptr;
        astree* a_param = nullptr;
        astree* a_stmt = nullptr;
        //create a vector of params
        vector<symbol_node*>* params = new vector<symbol_node*>();
        // create a new table
        symbol_table* table = new symbol_table();

        get_children(root, a_ret, a_param, a_stmt); 
        block_nr = ++block_nxt;

        //add params
        int count = 0;
        for(auto i = a_param->children.begin();
                i != a_param->children.end(); ++i, ++count) {
            symbol_node* para = ident_decl(*i, table, "param", count);
            if(para != nullptr) params->push_back(para);
            DEBUGF('S', "param: %s -> %s\n\n",
                   get_decl_name(a_ret),
                   get_decl_name(*i));
        }

        //find if there is a proto
        symbol_node* proto = lookup_fun(get_decl_name(a_ret), global);
        //do not match
        if(proto != nullptr &&
                !is_compatible(params, proto->parameters)) {
            errllocprintf(root->lloc, 
                    "incompatible function prototype %s\n", 
                    get_decl_name(a_ret));
            return;
        }

        //do have a proto
        if(proto) {
            func_node = proto;
            DEBUGF('S', "proto exists: %s\n\n", 
                    get_decl_name(a_ret));
        }
        //do not have a proto
        else {
            func_node = ident_decl(a_ret, global, "func", 
                    SOME_NUM);
            if(func_node != nullptr)
                func_node->parameters = params;
        }

        //switch local table
        local = table;
        //add stmts
        func_stmt(a_stmt, local);
        //dump
        func_node->dump(get_decl_name(a_ret), outfile);
        symbol_table_dump(local, outfile);
        //switch back to global table
        local = global;
    
        //out of a func
        func_node = nullptr;
    }

    else if(!strcmp(tname, "PROTO")) {
        astree* l = nullptr;
        astree* r = nullptr;
        get_children(root, l, r);
        
        symbol_node* func = ident_decl(l, global, "func", SOME_NUM);

        if(func != nullptr) {
            func->dump(get_decl_name(l), outfile);
            func->parameters = new vector<symbol_node*>();
            symbol_table* table = new symbol_table();
            local = table;

            block_nr = ++block_nxt;
            int j = 0;
            for(auto i = r->children.begin();
                    i != r->children.end(); ++i, ++j) {
                symbol_node* para = ident_decl(*i, table, "param", j);
                if(para != nullptr) {   
                    func->parameters->push_back(para);
                }
            }

            symbol_table_dump(local, outfile);
            local = global;
        }

    }
    else if (!strcmp(tname, "STRUCT")) {
        astree* a_name = nullptr;
        astree* a_field = nullptr;
        get_children(root, a_name, a_field);

        block_nr = 0;
        //create a new table for field
        symbol_table* table = new symbol_table();
        //create a new node
        symbol_node* node = new symbol_node(a_name->lloc, 0);
        type_set(node, attr::STRUCT);
        type_set(node, attr::TYPEID);
        node->fields = table;
        node->type_name = get_decl_name(a_name);
        node->sequence = SOME_NUM;
        //insert into struct table
        int rt = table_insert(string(get_decl_name(a_name)),
                    node, structure);
        if(rt == -1) return;

        //bind to astree node
        a_name->symbol_item = node;
        a_name->attributes = node->attributes;

        if(a_field) {
            int j = 0;
            for(auto i = a_field->children.begin();
                    i != a_field->children.end(); ++i, ++j) {
                ident_decl(*i, table, "field", j);
                DEBUGF('S', "field: %s -> %s\n\n",
                       node->type_name,
                       get_decl_name(*i)); 
            }
        }
        //dump
        node->dump(node->type_name, outfile);
        symbol_table_dump(table, outfile); 
    }

    else if(!strcmp(tname, "VARDECL")) {       
        astree* l = nullptr;
        astree* r = nullptr;
        get_children(root, l, r);

        block_nr = 0;
        type_check(r);
        symbol_node* var = ident_decl(l, global, "ident", SOME_NUM);
        if(var == nullptr) return;

        if(is_compatible(var->attributes, r->attributes)) {
            var->dump(get_decl_name(l), outfile);
            DEBUGF('S', "global var decl: %s\n\n", 
                    get_decl_name(l));
            return;
        }
        errllocprintf(root->lloc,
                "incompatible types for %s\n", 
                root->lexinfo->c_str());
        print_attr(var->attributes, var->type_name);
        string tmp = "";
        if(r->symbol_item != nullptr)
            tmp = r->symbol_item->type_name;
        print_attr(r->attributes, tmp);
    }
    else {
        errllocprintf(root->lloc, 
                "symbol_generate: invalid: %s\n", 
                root->lexinfo->c_str());
    }
}

void symbol_generator::generate(astree* root) {
    const char* tname = parser::get_tname (root->symbol);
    if(tname && strstr (tname, "TOK_") == tname) tname += 4;

    if(tname && !strcmp(tname, "ROOT")) {
        for(auto i = root->children.begin();
                i != root->children.end(); ++i)
            _generate(*i);
    }
    else {
        errllocprintf(root->lloc, 
            "symbol_generate: invalid root: %s\n", 
            root->lexinfo->c_str());
    }
}


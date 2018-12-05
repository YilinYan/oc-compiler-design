#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include <iostream>
#include <bitset>
#include <vector>
#include <unordered_map>
#include <string>

#include "auxlib.h"

struct astree;

enum class attr {
    VOID, INT, NULLX, STRING, STRUCT, ARRAY, FUNCTION, VARIABLE, FIELD,
    TYPEID, PARAM, LOCAL, LVAL, CONST, VREG, VADDR, BITSET_SIZE
};
using attr_bitset = bitset<static_cast<int>(attr::BITSET_SIZE)>;

struct symbol_node;
using symbol_table = unordered_map<string, symbol_node*>;
using symbol_entry = symbol_table::value_type;

void symbol_table_dump(symbol_table* table);
struct symbol_node {
    attr_bitset attributes;
    size_t sequence;
    symbol_table* fields;
    location lloc;
    size_t block_nr;
    vector<symbol_node*>* parameters;
    const char* type_name;

    symbol_node(location lloc, size_t nr);
    symbol_node();
    void dump(const char* name, FILE* file);
};

enum class types {
    BINOP, UNOP, COMPARE, RETURN, VARDECL, ASSIGN,
    NEW, NEWSTR, NEWARRAY, IDENT, TYPEID,
    CALL, INDEX, ARROW, FIELD, INTCON, STRCON, NULLCON,
    STRING, INT, NOMATTER
};

struct symbol_generator {
    symbol_table* structure;
    symbol_table* global;
    symbol_table* local;
    size_t block_nr;
    size_t block_nxt;
    symbol_node* func_node;
    FILE* outfile;

    symbol_generator(FILE* file);
    symbol_generator();
    void generate(astree* root);
    void _generate(astree* root);
    void type_check(astree* root);
    symbol_node* lookup_struct(astree* root);
    symbol_node* lookup_var(astree* root);
    symbol_node* ident_decl(
            astree* root, symbol_table* table,
            const string& decl_type, size_t seq = 0); 
    void func_stmt(astree* root, symbol_table* table);
    //   symbol_node* field_decl(astree* root, 
    //   symbol_table* table, int seq); 
};

void type_check(const astree* root, types type);
void type_set(astree* root, attr attri);
void type_set(astree* root, const attr_bitset& attris);
void type_set(symbol_node* node, attr attri);
bool type_test(const astree* root, attr attri);
bool type_test(const attr_bitset& attrs, attr attri);
bool is_compatible(const attr_bitset& a, const attr_bitset& b);
attr get_base(const astree* root);
const string attrs_to_string(const attr_bitset& attrs, 
        const string& name);

#endif

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

struct symbol_node {
    attr_bitset attributes;
    size_t sequence;
    symbol_table* fields;
    location lloc;
    size_t block_nr;
    vector<symbol_node*>* parameters;

    symbol_node(location lloc, size_t nr);
};

struct symbol_generator {
    symbol_table* structure;
    symbol_table* global;
    symbol_table* local;
    size_t block_nr;
    
    symbol_generator();
    void generate(astree* root);
};

enum class types;
void type_check(const astree* root, types type);
#endif

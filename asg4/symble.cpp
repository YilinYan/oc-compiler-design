#include <iostream>
#include <bitset>
#include <vector>
#include <map>

#include "astree.h"

enum class attr {
    VOID, INT, NULLX, STRING, STRUCT, ARRAY, FUNCTION, VARIABLE, FIELD,
    TYPEID, PARAM, LOCAL, LVAL, CONST, VREG, VADDR, BITSET_SIZE
};
using attr_bitset = bitset<attr::BITSET_SIZE>

struct symbol {
    attr_bitset attributes;
    size_t sequence;
    symbol_table* fields;
    location lloc;
    size_t block_nr;
    vector<symbol*>* parameters;
};
using symbol_table = unordered_map<string*, symbol*>;
using symbol_entry = symbol_table::value_type;

void traverse(const astree* root) {
    for(const auto& child : root->children) {
        traverse(child);
    }


}

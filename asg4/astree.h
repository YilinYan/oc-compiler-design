// $Id: astree.h,v 1.1 2018-11-26 17:41:08-08 - - $

#ifndef __ASTREE_H__
#define __ASTREE_H__

#include <string>
#include <vector>
using namespace std;

#include "auxlib.h"

struct location {
   size_t filenr;
   size_t linenr;
   size_t offset;
};

#include "symbol.h"

struct astree {

   // Fields.
   int symbol;               // token code
   location lloc;            // source location
   const string* lexinfo;    // pointer to lexical information
   vector<astree*> children; // children of this n-way node
   size_t block_nr;
   attr_bitset attributes;
   symbol_node* symbol_item; 

   // Functions.
   astree (int symbol, const location&, const char* lexinfo);
   ~astree();
   astree* adopt (astree* child1, astree* child2 = nullptr);
   astree* adopt_sym (astree* child, int symbol);
   astree* adopt_new (astree* child, int symbol);
   astree* change_sym (int symbol);
   void dump_node (FILE*);
   void dump_tree (FILE*, int depth = 0);
   static void dump (FILE* outfile, astree* tree);
   static void print (FILE* outfile, astree* tree, int depth = 0);
   static astree* function_(astree* a, astree* b, astree* c = nullptr);
};

void destroy (astree* tree1, astree* tree2 = nullptr);

void errllocprintf (const location&, const char* format, const char*);


#endif


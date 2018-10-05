#include "string_set.h"
#include <cstdio>
using namespace std;

int main(){
	string_set S;
	S.intern_stringset("hello");
	S.intern_stringset("hi");
	S.intern_stringset("hey");
	FILE* f;
	f = fopen("out.txt", "r");
	S.dump(f);
}

#include "generic_cache.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../util/string_buffer.h"
#include "type_impl.h"
#include "generic_type.h"
#include <assert.h>

//proto
static void generic_cache_tree_delete(VectorItem item);

generic_cache * generic_cache_new() {
	generic_cache* ret = (generic_cache*)MEM_MALLOC(sizeof(generic_cache));
	ret->fqcn = fqcn_cache_new();
	ret->type_args = NewVector();
	return ret;
}

void generic_cache_print(generic_cache * self) {
	fqcn_cache_print(self->fqcn);
	if (self->type_args->length <= 0) {
		return;
	}
	printf("<");
	for (int i = 0; i < self->type_args->length; i++) {
		generic_cache* e = (generic_cache*)AtVector(self->type_args, i);
		generic_cache_print(e);
		if (i != self->type_args->length - 1) {
			printf(", ");
		}
	}
	printf(">");
}

void generic_cache_dump(generic_cache * self, int depth) {
	Printi(depth);
	generic_cache_print(self);
	Println();
}

char* generic_cache_tostr(generic_cache* self) {
	string_buffer* sb = NewBuffer();
	//Namespace::Class
	char* name = fqcn_cache_tostr(self->fqcn);
	AppendsBuffer(sb, name);
	//Namespace::Class<|
	if(self->type_args->length > 0) {
		AppendsBuffer(sb, "<|");
	}
	//Namespace::Class<|...
	for(int i=0; i<self->type_args->length; i++) {
		generic_cache* e = (generic_cache*)AtVector(self->type_args, i);
		char* type = generic_cache_tostr(e);
		AppendsBuffer(sb, type);
		if(i != (self->type_args->length - 1)) {
			AppendsBuffer(sb, ", ");
		}
		MEM_FREE(type);
	}
	//Namespace::Class<|...|>
	if(self->type_args->length > 0) {
		AppendsBuffer(sb, "|>");
	}
	MEM_FREE(name);
	return ReleaseBuffer(sb);
}

void generic_cache_delete(generic_cache * self) {
	fqcn_cache_delete(self->fqcn);
	DeleteVector(self->type_args, generic_cache_tree_delete);
	MEM_FREE(self);
}

bool generic_cache_equals(generic_cache* a, generic_cache* b) {
	if(a->type_args->length != b->type_args->length) {
		return false;
	}
	if(!fqcn_cache_equals(a->fqcn, b->fqcn)) {
		return false;
	}
	if(a == b) {
		return true;
	}
	for(int i=0; i<a->type_args->length; i++) {
		generic_cache* ag = AtVector(a->type_args, i);
		generic_cache* bg = AtVector(b->type_args, i);
		if(!generic_cache_equals(ag, bg)) {
			return false;
		}
	}
	return true;
}
//private
static void generic_cache_tree_delete(VectorItem item) {
	generic_cache* e = (generic_cache*)item;
	generic_cache_delete(e);
}
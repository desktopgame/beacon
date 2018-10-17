#include "generic_cache.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../util/string_buffer.h"
#include "TYPE_IMPL.h"
#include "generic_type.h"
#include <assert.h>

//proto
static void generic_cache_tree_delete(VectorItem item);

generic_cache * NewGenericCache() {
	generic_cache* ret = (generic_cache*)MEM_MALLOC(sizeof(generic_cache));
	ret->fqcn = fqcn_cache_new();
	ret->type_args = NewVector();
	return ret;
}

void PrintGenericCache(generic_cache * self) {
	PrintFQCNCache(self->fqcn);
	if (self->type_args->length <= 0) {
		return;
	}
	printf("<");
	for (int i = 0; i < self->type_args->length; i++) {
		generic_cache* e = (generic_cache*)AtVector(self->type_args, i);
		PrintGenericCache(e);
		if (i != self->type_args->length - 1) {
			printf(", ");
		}
	}
	printf(">");
}

void DumpGenericCache(generic_cache * self, int depth) {
	Printi(depth);
	PrintGenericCache(self);
	Println();
}

char* GenericCacheToString(generic_cache* self) {
	StringBuffer* sb = NewBuffer();
	//Namespace::Class
	char* name = FQCNCacheToString(self->fqcn);
	AppendsBuffer(sb, name);
	//Namespace::Class<|
	if(self->type_args->length > 0) {
		AppendsBuffer(sb, "<|");
	}
	//Namespace::Class<|...
	for(int i=0; i<self->type_args->length; i++) {
		generic_cache* e = (generic_cache*)AtVector(self->type_args, i);
		char* type = GenericCacheToString(e);
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

void DeleteGenericCache(generic_cache * self) {
	DeleteFQCNCache(self->fqcn);
	DeleteVector(self->type_args, generic_cache_tree_delete);
	MEM_FREE(self);
}

bool EqualsGenericCache(generic_cache* a, generic_cache* b) {
	if(a->type_args->length != b->type_args->length) {
		return false;
	}
	if(!EqualsFQCNCache(a->fqcn, b->fqcn)) {
		return false;
	}
	if(a == b) {
		return true;
	}
	for(int i=0; i<a->type_args->length; i++) {
		generic_cache* ag = AtVector(a->type_args, i);
		generic_cache* bg = AtVector(b->type_args, i);
		if(!EqualsGenericCache(ag, bg)) {
			return false;
		}
	}
	return true;
}
//private
static void generic_cache_tree_delete(VectorItem item) {
	generic_cache* e = (generic_cache*)item;
	DeleteGenericCache(e);
}
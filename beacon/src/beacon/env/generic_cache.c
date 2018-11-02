#include "generic_cache.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../util/string_buffer.h"
#include "TYPE_IMPL.h"
#include "generic_type.h"
#include <assert.h>

//proto
static void tree_delete(VectorItem item);

GenericCache * NewGenericCache() {
	GenericCache* ret = (GenericCache*)MEM_MALLOC(sizeof(GenericCache));
	ret->FQCN = NewFQCNCache();
	ret->TypeArgs = NewVector();
	return ret;
}

void PrintGenericCache(GenericCache * self) {
	PrintFQCNCache(self->FQCN);
	if (self->TypeArgs->Length <= 0) {
		return;
	}
	printf("[");
	for (int i = 0; i < self->TypeArgs->Length; i++) {
		GenericCache* e = (GenericCache*)AtVector(self->TypeArgs, i);
		PrintGenericCache(e);
		if (i != self->TypeArgs->Length - 1) {
			printf(", ");
		}
	}
	printf("]");
}

void DumpGenericCache(GenericCache * self, int depth) {
	Printi(depth);
	PrintGenericCache(self);
	Println();
}

char* GenericCacheToString(GenericCache* self) {
	Buffer* sb = NewBuffer();
	//Namespace::Class
	char* name = FQCNCacheToString(self->FQCN);
	AppendsBuffer(sb, name);
	//Namespace::Class[
	if(self->TypeArgs->Length > 0) {
		AppendsBuffer(sb, "[");
	}
	//Namespace::Class[...
	for(int i=0; i<self->TypeArgs->Length; i++) {
		GenericCache* e = (GenericCache*)AtVector(self->TypeArgs, i);
		char* type = GenericCacheToString(e);
		AppendsBuffer(sb, type);
		if(i != (self->TypeArgs->Length - 1)) {
			AppendsBuffer(sb, ", ");
		}
		MEM_FREE(type);
	}
	//Namespace::Class[...]
	if(self->TypeArgs->Length > 0) {
		AppendsBuffer(sb, "]");
	}
	MEM_FREE(name);
	return ReleaseBuffer(sb);
}

void DeleteGenericCache(GenericCache * self) {
	DeleteFQCNCache(self->FQCN);
	DeleteVector(self->TypeArgs, tree_delete);
	MEM_FREE(self);
}

bool EqualsGenericCache(GenericCache* a, GenericCache* b) {
	if(a->TypeArgs->Length != b->TypeArgs->Length) {
		return false;
	}
	if(!EqualsFQCNCache(a->FQCN, b->FQCN)) {
		return false;
	}
	if(a == b) {
		return true;
	}
	for(int i=0; i<a->TypeArgs->Length; i++) {
		GenericCache* ag = AtVector(a->TypeArgs, i);
		GenericCache* bg = AtVector(b->TypeArgs, i);
		if(!EqualsGenericCache(ag, bg)) {
			return false;
		}
	}
	return true;
}
//private
static void tree_delete(VectorItem item) {
	GenericCache* e = (GenericCache*)item;
	DeleteGenericCache(e);
}
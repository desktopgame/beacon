#include "generic_cache.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../util/string_buffer.h"
#include "TYPE_IMPL.h"
#include "generic_type.h"
#include <assert.h>

//proto
static void tree_delete(VectorItem item);

bc_GenericCache * bc_NewGenericCache() {
	bc_GenericCache* ret = (bc_GenericCache*)MEM_MALLOC(sizeof(bc_GenericCache));
	ret->FQCN = bc_NewFQCNCache();
	ret->TypeArgs = NewVector();
	return ret;
}

void bc_PrintGenericCache(bc_GenericCache * self) {
	bc_PrintFQCNCache(self->FQCN);
	if (self->TypeArgs->Length <= 0) {
		return;
	}
	printf("[");
	for (int i = 0; i < self->TypeArgs->Length; i++) {
		bc_GenericCache* e = (bc_GenericCache*)AtVector(self->TypeArgs, i);
		bc_PrintGenericCache(e);
		if (i != self->TypeArgs->Length - 1) {
			printf(", ");
		}
	}
	printf("]");
}

void bc_DumpGenericCache(bc_GenericCache * self, int depth) {
	bc_Printi(depth);
	bc_PrintGenericCache(self);
	bc_Println();
}

char* bc_GenericCacheToString(bc_GenericCache* self) {
	Buffer* sb = NewBuffer();
	//Namespace::Class
	char* name = bc_FQCNCacheToString(self->FQCN);
	AppendsBuffer(sb, name);
	//Namespace::Class[
	if(self->TypeArgs->Length > 0) {
		AppendsBuffer(sb, "[");
	}
	//Namespace::Class[...
	for(int i=0; i<self->TypeArgs->Length; i++) {
		bc_GenericCache* e = (bc_GenericCache*)AtVector(self->TypeArgs, i);
		char* type = bc_GenericCacheToString(e);
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

void bc_DeleteGenericCache(bc_GenericCache * self) {
	bc_DeleteFQCNCache(self->FQCN);
	DeleteVector(self->TypeArgs, tree_delete);
	MEM_FREE(self);
}

bool bc_EqualsGenericCache(bc_GenericCache* a, bc_GenericCache* b) {
	if(a->TypeArgs->Length != b->TypeArgs->Length) {
		return false;
	}
	if(!bc_EqualsFQCNCache(a->FQCN, b->FQCN)) {
		return false;
	}
	if(a == b) {
		return true;
	}
	for(int i=0; i<a->TypeArgs->Length; i++) {
		bc_GenericCache* ag = AtVector(a->TypeArgs, i);
		bc_GenericCache* bg = AtVector(b->TypeArgs, i);
		if(!bc_EqualsGenericCache(ag, bg)) {
			return false;
		}
	}
	return true;
}
//private
static void tree_delete(VectorItem item) {
	bc_GenericCache* e = (bc_GenericCache*)item;
	bc_DeleteGenericCache(e);
}
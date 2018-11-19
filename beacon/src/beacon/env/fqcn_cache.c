#include "fqcn_cache.h"
#include "../util/mem.h"
#include "../util/string_buffer.h"
#include "../util/text.h"
#include "namespace.h"
#include "type_interface.h"
#include "TYPE_IMPL.h"
#include <assert.h>
#include <string.h>

//proto
static bc_Type* resolve_type(bc_FQCNCache * self, bc_Namespace* current);

/*
FQCNCache * NewFQCNCache() {
}
*/

bc_FQCNCache* bc_MallocFQCNCache(const char* filename, int lineno) {
	bc_FQCNCache* ret = (bc_FQCNCache*)bc_MXMalloc(sizeof(bc_FQCNCache), filename, lineno);
	ret->Scope = MallocVector(filename, lineno);
	ret->Name = 0;
	return ret;
}

void bc_DumpFQCNCache(bc_FQCNCache * self, int depth) {
	bc_Printi(depth);
	printf("type %s", Ref2Str(self->Name));
	bc_Println();
	//X::C.call() のような呼び出しなら
	if (self->Scope->Length > 0) {
		bc_Printi(depth);
		printf("scope");
		bc_Println();
		for (int i = 0; i < self->Scope->Length; i++) {
			StringView sv = (StringView)AtVector(self->Scope, i);
			bc_Printi(depth + 1);
			printf("%s", Ref2Str(sv));
			bc_Println();
		}
	}
}

void bc_PrintFQCNCache(bc_FQCNCache * self) {
	if(self == NULL) {
		printf("NULL");
		return;
	}
	if (self->Scope->Length == 0) {
		printf("%s", Ref2Str(self->Name));
	} else {
		for (int i = 0; i < self->Scope->Length; i++) {
			printf("%s", Ref2Str((StringView)AtVector(self->Scope, i)));
			printf("::");
		}
		printf("%s", Ref2Str(self->Name));
	}
}

bc_Namespace * bc_GetScopeFQCN(bc_FQCNCache * self, bc_Namespace* current) {
	if (self->Scope->Length == 0) {
		return current;
	}
	bc_Namespace* top = NULL;
	for (int i = 0; i < self->Scope->Length; i++) {
		StringView ev = (StringView)AtVector(self->Scope, i);
		if (top == NULL) {
			top = bc_FindNamespaceFromRoot(ev);
		} else {
			top = bc_FindNamespaceFromNamespace(top, ev);
		}
	}
	return top;
}

bc_Type* bc_GetTypeFQCN(bc_FQCNCache * self, bc_Namespace * current) {
	bc_Type* ret = resolve_type(self, current);
	//Console(X::Yを含まない)のような指定なら
	//signal::lang空間も探索する
	if (ret == NULL && self->Scope->Length == 0) {
		ret = resolve_type(self, bc_GetLangNamespace());
	}
	return ret;
}

bc_Interface* bc_GetInterfaceFQCN(bc_FQCNCache * self, bc_Namespace * current) {
	return bc_TypeToInterface(bc_GetTypeFQCN(self, current));
}

bc_Class* bc_GetClassFQCN(bc_FQCNCache * self, bc_Namespace * current) {
	return bc_TypeToClass(bc_GetTypeFQCN(self, current));
}

char* bc_FQCNCacheToString(bc_FQCNCache* self) {
	Buffer* sb = NewBuffer();
	for(int i=0; i<self->Scope->Length; i++) {
		StringView ev = (StringView)AtVector(self->Scope, i);
		AppendsBuffer(sb, Ref2Str(ev));
		if(i == (self->Scope->Length - 1)) {
			break;
		}
		AppendsBuffer(sb, "::");
	}
	AppendsBuffer(sb, Ref2Str(self->Name));
	return ReleaseBuffer(sb);
}

void bc_DeleteFQCNCache(bc_FQCNCache * self) {
	if(self == NULL) {
		return;
	}
	DeleteVector(self->Scope, VectorDeleterOfNull);
	MEM_FREE(self);
}

bool bc_EqualsFQCNCache(bc_FQCNCache* a, bc_FQCNCache* b) {
	if(a->Name != b->Name || a->Scope->Length != b->Scope->Length) {
		return false;
	}
	if(a == b) {
		return true;
	}
	for(int i=0; i<a->Scope->Length; i++) {
		StringView as = (StringView)AtVector(a->Scope, i);
		StringView bs = (StringView)AtVector(b->Scope, i);
		if(as != bs) {
			return false;
		}
	}
	return true;
}
//private
static bc_Type* resolve_type(bc_FQCNCache * self, bc_Namespace* current) {
	//Y形式
	if (self->Scope->Length == 0) {
		StringView namev = self->Name;
		//プリミティブ型はどこからでも参照できる
		if (namev == InternString("Object")) {
			return BC_TYPE_OBJECT;
		} else if (namev == InternString("Int")) {
			return BC_TYPE_INT;
		} else if (namev == InternString("Double")) {
			return BC_TYPE_DOUBLE;
		} else if (namev == InternString("Char")) {
			return BC_TYPE_CHAR;
		} else if (namev == InternString("String")) {
			return BC_TYPE_STRING;
		} else if (namev == InternString("Bool")) {
			return BC_TYPE_BOOL;
		} else if (namev == InternString("Void")) {
			return BC_TYPE_VOID;
		}
		if (current == NULL) {
			return NULL;
		}
		return bc_FindTypeFromNamespace(current, self->Name);
	}
	//X::Yのような形式
	bc_Namespace* c = bc_GetScopeFQCN(self, current);
	if (c == NULL) {
		return NULL;
	}
	return bc_FindTypeFromNamespace(c, self->Name);
}

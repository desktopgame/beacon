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
static type * fqcn_TYPE_IMPL(FQCNCache * self, Namespace* current);

/*
FQCNCache * FQCNCache_new() {
}
*/

FQCNCache* MallocFQCNCache(const char* filename, int lineno) {
	FQCNCache* ret = (FQCNCache*)mem_malloc(sizeof(FQCNCache), filename, lineno);
	ret->Scope = MallocVector(filename, lineno);
	ret->Name = 0;
	return ret;
}

void DumpFQCNCache(FQCNCache * self, int depth) {
	Printi(depth);
	printf("type %s", Ref2Str(self->Name));
	Println();
	//X::C.call() のような呼び出しなら
	if (self->Scope->Length > 0) {
		Printi(depth);
		printf("scope");
		Println();
		for (int i = 0; i < self->Scope->Length; i++) {
			StringView sv = (StringView)AtVector(self->Scope, i);
			Printi(depth + 1);
			printf("%s", Ref2Str(sv));
			Println();
		}
	}
}

void PrintFQCNCache(FQCNCache * self) {
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

Namespace * GetScopeFQCN(FQCNCache * self, Namespace* current) {
	if (self->Scope->Length == 0) {
		return current;
	}
	Namespace* top = NULL;
	for (int i = 0; i < self->Scope->Length; i++) {
		StringView ev = (StringView)AtVector(self->Scope, i);
		if (top == NULL) {
			top = FindNamespaceFromRoot(ev);
		} else {
			top = FindNamespaceFromNamespace(top, ev);
		}
	}
	return top;
}

type * GetTypeFQCN(FQCNCache * self, Namespace * current) {
	type* ret = fqcn_TYPE_IMPL(self, current);
	//Console(X::Yを含まない)のような指定なら
	//signal::lang空間も探索する
	if (ret == NULL && self->Scope->Length == 0) {
		ret = fqcn_TYPE_IMPL(self, GetLangNamespace());
	}
	return ret;
}

interface_ * GetInterfaceFQCN(FQCNCache * self, Namespace * current) {
	return TypeToInterface(GetTypeFQCN(self, current));
}

class_ * GetClassFQCN(FQCNCache * self, Namespace * current) {
	return TypeToClass(GetTypeFQCN(self, current));
}

char* FQCNCacheToString(FQCNCache* self) {
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

void DeleteFQCNCache(FQCNCache * self) {
	if(self == NULL) {
		return;
	}
	DeleteVector(self->Scope, VectorDeleterOfNull);
	MEM_FREE(self);
}

bool EqualsFQCNCache(FQCNCache* a, FQCNCache* b) {
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
static type * fqcn_TYPE_IMPL(FQCNCache * self, Namespace* current) {
	//Y形式
	if (self->Scope->Length == 0) {
		StringView namev = self->Name;
		//プリミティブ型はどこからでも参照できる
		if (namev == InternString("Object")) {
			return TYPE_OBJECT;
		} else if (namev == InternString("Int")) {
			return TYPE_INT;
		} else if (namev == InternString("Double")) {
			return TYPE_DOUBLE;
		} else if (namev == InternString("Char")) {
			return TYPE_CHAR;
		} else if (namev == InternString("String")) {
			return TYPE_STRING;
		} else if (namev == InternString("Bool")) {
			return TYPE_BOOL;
		} else if (namev == InternString("Void")) {
			return TYPE_VOID;
		}
		if (current == NULL) {
			return NULL;
		}
		return FindTypeFromNamespace(current, self->Name);
	}
	//X::Yのような形式
	Namespace* c = GetScopeFQCN(self, current);
	if (c == NULL) {
		return NULL;
	}
	return FindTypeFromNamespace(c, self->Name);
}

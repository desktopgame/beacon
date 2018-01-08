#include "fqcn_cache.h"
#include "../util/mem.h"
#include "namespace.h"
#include "type_interface.h"


fqcn_cache * fqcn_cache_new() {
	fqcn_cache* ret = (fqcn_cache*)MEM_MALLOC(sizeof(fqcn_cache));
	ret->scope_vec = vector_new();
	ret->name = NULL;
	return ret;
}

void fqcn_cache_dump(fqcn_cache * self, int depth) {
	text_putindent(depth);
	printf("class %s", self->name);
	text_putline();
	//X::C.call() のような呼び出しなら
	if (self->scope_vec->length > 0) {
		text_putindent(depth);
		printf("scope");
		text_putline();
		for (int i = 0; i < self->scope_vec->length; i++) {
			char* e = (char*)vector_at(self->scope_vec, i);
			text_putindent(depth + 1);
			printf("%s", e);
			text_putline();
		}
	}
}

void fqcn_cache_print(fqcn_cache * self) {
	if (self->scope_vec->length == 0) {
		printf("%s", self->name);
	} else {
		for (int i = 0; i < self->scope_vec->length; i++) {
			printf("%s", (char*)vector_at(self->scope_vec, i));
			printf("::");
		}
		printf("%s", self->name);
	}
}

namespace_ * fqcn_scope(fqcn_cache * self, namespace_* current) {
	if (self->scope_vec->length == 0) {
		return current;
	}
	namespace_* top = NULL;
	for (int i = 0; i < self->scope_vec->length; i++) {
		char* e = (char*)vector_at(self->scope_vec, i);
		if (top == NULL) {
			top = namespace_get_at_root(e);
		} else {
			top = namespace_get_namespace(top, e);
		}
	}
	return top;
}

type * fqcn_type(fqcn_cache * self, namespace_* current) {
	//Y形式
	if (self->scope_vec->length == 0) {
		char* name = self->name;
		//プリミティブ型はどこからでも参照できる
		if (!strcmp(name, "Int")) {
			return CL_INT;
		} else if (!strcmp(name, "Double")) {
			return CL_DOUBLE;
		} else if (!strcmp(name, "Char")) {
			return CL_CHAR;
		} else if (!strcmp(name, "String")) {
			return CL_STRING;
		} else if (!strcmp(name, "Void")) {
			return CL_VOID;
		}
		if (current == NULL) { return NULL; }
		return namespace_get_type(current, self->name);
	}
	//X::Yのような形式
	namespace_* c = fqcn_scope(self, current);
	if (c == NULL) { return NULL; }
	return namespace_get_type(c, self->name);
}

void fqcn_cache_delete(fqcn_cache * self) {
	vector_delete(self->scope_vec, vector_deleter_free);
	MEM_FREE(self->name);
	MEM_FREE(self);
}

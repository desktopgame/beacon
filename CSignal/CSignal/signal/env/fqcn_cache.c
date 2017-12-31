#include "fqcn_cache.h"
#include "../util/mem.h"

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

void fqcn_cache_delete(fqcn_cache * self) {
	vector_delete(self->scope_vec, vector_deleter_free);
	MEM_FREE(self->name);
	MEM_FREE(self);
}

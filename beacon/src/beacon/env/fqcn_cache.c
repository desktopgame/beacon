#include "fqcn_cache.h"
#include "../util/mem.h"
#include "../util/string_buffer.h"
#include "../util/text.h"
#include "namespace.h"
#include "type_interface.h"
#include "type_impl.h"
#include <assert.h>
#include <string.h>

//proto
static type * fqcn_type_impl(fqcn_cache * self, namespace_* current);

/*
fqcn_cache * fqcn_cache_new() {
}
*/

fqcn_cache* fqcn_cache_malloc(const char* filename, int lineno) {
	fqcn_cache* ret = (fqcn_cache*)mem_malloc(sizeof(fqcn_cache), filename, lineno);
	ret->scope_vec = vector_malloc(filename, lineno);
	ret->namev = 0;
	return ret;
}

void fqcn_cache_dump(fqcn_cache * self, int depth) {
	io_printi(depth);
	printf("type %s", string_pool_ref2str(self->namev));
	io_println();
	//X::C.call() のような呼び出しなら
	if (self->scope_vec->length > 0) {
		io_printi(depth);
		printf("scope");
		io_println();
		for (int i = 0; i < self->scope_vec->length; i++) {
			string_view sv = (string_view)vector_at(self->scope_vec, i);
			io_printi(depth + 1);
			printf("%s", string_pool_ref2str(sv));
			io_println();
		}
	}
}

void fqcn_cache_print(fqcn_cache * self) {
	if(self == NULL) {
		printf("NULL");
		return;
	}
	if (self->scope_vec->length == 0) {
		printf("%s", string_pool_ref2str(self->namev));
	} else {
		for (int i = 0; i < self->scope_vec->length; i++) {
			printf("%s", string_pool_ref2str((string_view)vector_at(self->scope_vec, i)));
			printf("::");
		}
		printf("%s", string_pool_ref2str(self->namev));
	}
}

namespace_ * fqcn_scope(fqcn_cache * self, namespace_* current) {
	if (self->scope_vec->length == 0) {
		return current;
	}
	namespace_* top = NULL;
	for (int i = 0; i < self->scope_vec->length; i++) {
		string_view ev = (string_view)vector_at(self->scope_vec, i);
		if (top == NULL) {
			top = namespace_get_at_root(ev);
		} else {
			top = namespace_get_namespace(top, ev);
		}
	}
	return top;
}

type * fqcn_type(fqcn_cache * self, namespace_ * current) {
	type* ret = fqcn_type_impl(self, current);
	//Console(X::Yを含まない)のような指定なら
	//signal::lang空間も探索する
	if (ret == NULL && self->scope_vec->length == 0) {
		ret = fqcn_type_impl(self, namespace_lang());
	}
	return ret;
}

interface_ * fqcn_interface(fqcn_cache * self, namespace_ * current) {
	return type_as_interface(fqcn_type(self, current));
}

class_ * fqcn_class(fqcn_cache * self, namespace_ * current) {
	return type_as_class(fqcn_type(self, current));
}

char* fqcn_cache_tostr(fqcn_cache* self) {
	string_buffer* sb = string_buffer_new();
	for(int i=0; i<self->scope_vec->length; i++) {
		string_view ev = (string_view)vector_at(self->scope_vec, i);
		string_buffer_appends(sb, string_pool_ref2str(ev));
		if(i == (self->scope_vec->length - 1)) {
			break;
		}
		string_buffer_appends(sb, "::");
	}
	string_buffer_appends(sb, string_pool_ref2str(self->namev));
	return string_buffer_release(sb);
}

void fqcn_cache_delete(fqcn_cache * self) {
	if(self == NULL) {
		return;
	}
	vector_delete(self->scope_vec, vector_deleter_null);
	MEM_FREE(self);
}

bool fqcn_cache_equals(fqcn_cache* a, fqcn_cache* b) {
	if(a->namev != b->namev || a->scope_vec->length != b->scope_vec->length) {
		return false;
	}
	if(a == b) {
		return true;
	}
	for(int i=0; i<a->scope_vec->length; i++) {
		string_view as = (string_view)vector_at(a->scope_vec, i);
		string_view bs = (string_view)vector_at(b->scope_vec, i);
		if(as != bs) {
			return false;
		}
	}
	return true;
}
//private
static type * fqcn_type_impl(fqcn_cache * self, namespace_* current) {
	//Y形式
	if (self->scope_vec->length == 0) {
		string_view namev = self->namev;
		//プリミティブ型はどこからでも参照できる
		if (namev == string_pool_intern("Object")) {
			return TYPE_OBJECT;
		} else if (namev == string_pool_intern("Int")) {
			return TYPE_INT;
		} else if (namev == string_pool_intern("Double")) {
			return TYPE_DOUBLE;
		} else if (namev == string_pool_intern("Char")) {
			return TYPE_CHAR;
		} else if (namev == string_pool_intern("String")) {
			return TYPE_STRING;
		} else if (namev == string_pool_intern("Bool")) {
			return TYPE_BOOL;
		} else if (namev == string_pool_intern("Void")) {
			return TYPE_VOID;
		}
		if (current == NULL) {
			return NULL;
		}
		return namespace_get_type(current, self->namev);
	}
	//X::Yのような形式
	namespace_* c = fqcn_scope(self, current);
	if (c == NULL) {
		return NULL;
	}
	return namespace_get_type(c, self->namev);
}

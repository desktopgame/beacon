#include "enviroment.h"
#include "../env/type_interface.h"
#include "../env/type_impl.h"
#include "../env/object.h"
#include "../env/fqcn_cache.h"
#include <stdlib.h>
#include <assert.h>
#include "../util/mem.h"

//proto
static void enviroment_constant_pool_delete(vector_item item);

enviroment * enviroment_new() {
	enviroment* ret = (enviroment*)MEM_MALLOC(sizeof(enviroment));
	ret->buf = opcode_buf_new();
	ret->constant_pool = vector_new();
	ret->sym_table = symbol_table_new();
	//ret->class_ = NULL;
	ret->context_cll = NULL;
	ret->namespace_vec = vector_new();
	ret->class_vec = vector_new();
	ret->toplevel = false;
	return ret;
}

int enviroment_add_constant_int(enviroment * self, int i) {
	int len = self->constant_pool->length;
	vector_push(self->constant_pool, object_int_new(i));
	return len;
}

int enviroment_add_constant_double(enviroment * self, double d) {
	int len = self->constant_pool->length;
	vector_push(self->constant_pool, object_double_new(d));
	return len;
}

int enviroment_add_constant_char(enviroment * self, char c) {
	int len = self->constant_pool->length;
	vector_push(self->constant_pool, object_char_new(c));
	return len;
}

int enviroment_add_constant_string(enviroment * self, const char * s) {
	int len = self->constant_pool->length;
	vector_push(self->constant_pool, object_string_new(s));
	return len;
}

vector_item enviroment_source_at(enviroment * self, int index) {
	return vector_at(self->buf->source, index);
}

object* enviroment_constant_at(enviroment * self, int index) {
	return (object*)vector_at(self->constant_pool, index);
}

object* enviroment_constant_int_at(enviroment * self, int index) {
	object* e = enviroment_constant_at(self, index);
	assert(e->tag == object_int);
	return e;
}

object* enviroment_constant_double_at(enviroment * self, int index) {
	object* e = enviroment_constant_at(self, index);
	assert(e->tag == object_double);
	return e;
}

object* enviroment_constant_char_at(enviroment * self, int index) {
	object* e = enviroment_constant_at(self, index);
	assert(e->tag == object_char);
	return e;
}

object* enviroment_constant_string_at(enviroment * self, int index) {
	object* e = enviroment_constant_at(self, index);
	assert(e->tag == object_string);
	return e;
}

class_ * enviroment_class(enviroment * self, fqcn_cache * fqcn) {
	vector_item e = vector_top(self->namespace_vec);
	class_* tp = NULL;
	if (e != NULL) {
		namespace_* scope = (namespace_*)e;
		tp = fqcn_class(fqcn, scope);
	} else {
		tp = fqcn_class(fqcn, NULL);
	}
	return tp;
}

void enviroment_delete(enviroment * self) {
	vector_delete(self->namespace_vec, vector_deleter_null);
	vector_delete(self->class_vec, vector_deleter_null);
	
	opcode_buf_delete(self->buf);
	vector_delete(self->constant_pool, enviroment_constant_pool_delete);
	symbol_table_delete(self->sym_table);
	MEM_FREE(self);
}

//private
static void enviroment_constant_pool_delete(vector_item item) {
	object_delete((object*)item);
}

#include "enviroment.h"
#include "../env/class.h"
#include "constant_element.h"
#include <stdlib.h>
#include <assert.h>

//proto
static void enviroment_constant_pool_delete(vector_item item);

enviroment * enviroment_new() {
	enviroment* ret = (enviroment*)malloc(sizeof(enviroment));
	ret->buf = opcode_buf_new();
	ret->constant_pool = vector_new();
	ret->class_ = NULL;
	return ret;
}

int enviroment_add_constant_int(enviroment * self, int i) {
	int len = self->constant_pool->length;
	vector_push(self->constant_pool, constant_int_new(i));
	return len;
}

int enviroment_add_constant_double(enviroment * self, double d) {
	int len = self->constant_pool->length;
	vector_push(self->constant_pool, constant_double_new(d));
	return len;
}

int enviroment_add_constant_char(enviroment * self, char c) {
	int len = self->constant_pool->length;
	vector_push(self->constant_pool, constant_char_new(c));
	return len;
}

int enviroment_add_constant_string(enviroment * self, const char * s) {
	int len = self->constant_pool->length;
	vector_push(self->constant_pool, constant_string_new(s));
	return len;
}

vector_item enviroment_source_at(enviroment * self, int index) {
	return vector_at(self->buf->source, index);
}

constant_element* enviroment_constant_at(enviroment * self, int index) {
	return (constant_element*)vector_at(self->constant_pool, index);
}

int enviroment_constant_int_at(enviroment * self, int index) {
	constant_element* e = enviroment_constant_at(self, index);
	assert(e->type == constant_int);
	return e->u.int_;
}

double enviroment_constant_double_at(enviroment * self, int index) {
	constant_element* e = enviroment_constant_at(self, index);
	assert(e->type == constant_double);
	return e->u.double_;
}

char enviroment_constant_char_at(enviroment * self, int index) {
	constant_element* e = enviroment_constant_at(self, index);
	assert(e->type == constant_char);
	return e->u.char_;
}

char * enviroment_constant_string_at(enviroment * self, int index) {
	constant_element* e = enviroment_constant_at(self, index);
	assert(e->type == constant_string);
	return e->u.string_;
}

void enviroment_delete(enviroment * self) {
	opcode_buf_delete(self->buf);
	vector_delete(self->constant_pool, enviroment_constant_pool_delete);
	free(self);
}

//private
static void enviroment_constant_pool_delete(vector_item item) {
	constant_element_delete((constant_element*)item);
}

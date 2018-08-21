#include "enviroment.h"
#include "../env/class_loader.h"
#include "../env/type_interface.h"
#include "../env/type_impl.h"
#include "../env/object.h"
#include "../env/fqcn_cache.h"
#include "../lib/beacon/lang/bc_array.h"
#include "line_range.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "../util/mem.h"
#include "../util/string_buffer.h"
#include "../util/text.h"
#include "../env/generic_type.h"

//proto
static void enviroment_constant_pool_vec_delete(vector_item item);
static void enviroment_line_range_delete(vector_item item);
static void enviroment_add_constant(enviroment* self, object* o);
static void enviroment_object_delete_self(vector_item item);
static void enviroment_object_delete(object* obj);

enviroment * enviroment_new() {
	enviroment* ret = (enviroment*)MEM_MALLOC(sizeof(enviroment));
	ret->buf = opcode_buf_new();
	ret->constant_pool_vec = vector_new();
	ret->sym_table = symbol_table_new();
	ret->context_ref = NULL;
	ret->line_range_vec = vector_new();
	return ret;
}

void enviroment_add_range(enviroment* self, int lineno) {
	assert(lineno >= 0);
	//空なので追加
	if (vector_empty(self->line_range_vec)) {
		line_range* lr = line_range_new();
		lr->start_offset = 0;
		lr->end_offset = 0;
		lr->lineno = lineno;
		vector_push(self->line_range_vec, lr);
		return;
	}
	//空ではないなら、
	//最後についかしたレンジを伸ばすか新たに追加する
	line_range* lrt = (line_range*)vector_top(self->line_range_vec);
	if (lrt->lineno == lineno) {
		lrt->end_offset = self->buf->source_vec->length;
	} else {
		line_range* lr = line_range_new();
		lr->start_offset = self->buf->source_vec->length;
		lr->end_offset = self->buf->source_vec->length;
		lr->lineno = lineno;
		vector_push(self->line_range_vec, lr);
	}
}

void enviroment_op_dump(enviroment * self, int depth) {
	opcode_buf* buf = self->buf;
	line_range* lr = NULL;
	int lrPos = -1;
	for (int i = 0; i < buf->source_vec->length; i++) {
		io_printi(depth);
		i = opcode_print(buf->source_vec, i);
		if (!vector_empty(self->line_range_vec)) {
			if (lr == NULL) {
				lr = vector_at(self->line_range_vec, 0);
				lrPos = 0;
			} else {
				if (i > lr->end_offset) {
					lrPos++;
					if (lrPos < self->line_range_vec->length) {
						lr = vector_at(self->line_range_vec, lrPos);
					}
				}
			}
		}
		if (lr != NULL) {
			printf("<%d>", lr->lineno);
		}
		io_println();
	}
	io_println();
}

int enviroment_add_constant_int(enviroment * self, int i) {
	int len = self->constant_pool_vec->length;
	enviroment_add_constant(self, object_int_T_new(i));
	return len;
}

int enviroment_add_constant_double(enviroment * self, double d) {
	int len = self->constant_pool_vec->length;
	enviroment_add_constant(self, object_double_T_new(d));
	return len;
}

int enviroment_add_constant_char(enviroment * self, char c) {
	int len = self->constant_pool_vec->length;
	enviroment_add_constant(self, object_char_T_new(c));
	return len;
}

int enviroment_add_constant_string(enviroment * self, string_view sv) {
	int len = self->constant_pool_vec->length;
	enviroment_add_constant(self, object_string_T_new(string_pool_ref2str(sv)));
	return len;
}

vector_item enviroment_source_at(enviroment * self, int index) {
	return vector_at(self->buf->source_vec, index);
}

object* enviroment_constant_at(enviroment * self, int index) {
	return (object*)vector_at(self->constant_pool_vec, index);
}

object* enviroment_constant_int_at(enviroment * self, int index) {
	object* e = enviroment_constant_at(self, index);
	assert(e->tag == object_int_T);
	return e;
}

object* enviroment_constant_double_at(enviroment * self, int index) {
	object* e = enviroment_constant_at(self, index);
	assert(e->tag == object_double_T);
	return e;
}

object* enviroment_constant_char_at(enviroment * self, int index) {
	object* e = enviroment_constant_at(self, index);
	assert(e->tag == object_char_T);
	return e;
}

object* enviroment_constant_string_at(enviroment * self, int index) {
	object* e = enviroment_constant_at(self, index);
	assert(e->tag == object_string_T);
	return e;
}

void enviroment_delete(enviroment * self) {
	if(self == NULL) {
		return;
	}
	vector_delete(self->constant_pool_vec, enviroment_constant_pool_vec_delete);
	vector_delete(self->line_range_vec, enviroment_line_range_delete);
	opcode_buf_delete(self->buf);
	symbol_table_delete(self->sym_table);
	MEM_FREE(self);
}

//private
static void enviroment_constant_pool_vec_delete(vector_item item) {
	//StringやArrayはここで中身を削除する必要がある
	enviroment_object_delete((object*)item);
}

static void enviroment_line_range_delete(vector_item item) {
	line_range* e = (line_range*)item;
	line_range_delete(e);
}

static void enviroment_add_constant(enviroment* self, object* o) {
	vector_push(self->constant_pool_vec, o);
	assert(o->paint == paint_onexit_T);
}

static void enviroment_object_delete_self(vector_item item) {
}

static void enviroment_object_delete(object* obj) {
	object_destroy(obj);
}

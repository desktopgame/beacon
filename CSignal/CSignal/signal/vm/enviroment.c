#include "enviroment.h"
#include "../env/class_loader.h"
#include "../env/type_interface.h"
#include "../env/type_impl.h"
#include "../env/object.h"
#include "../env/fqcn_cache.h"
#include "../lib/signal/lang/sg_array.h"
#include "line_range.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "../util/mem.h"
#include "../util/string_buffer.h"
#include "../util/text.h"

//proto
static void enviroment_constant_pool_delete(vector_item item);
static void enviroment_line_range_delete(vector_item item);
static void enviroment_add_constant(enviroment* self, object* o);
static void enviroment_object_delete(object* obj);

enviroment * enviroment_new() {
	enviroment* ret = (enviroment*)MEM_MALLOC(sizeof(enviroment));
	ret->buf = opcode_buf_new();
	ret->constant_pool = vector_new();
	ret->sym_table = symbol_table_new();
	//ret->class_ = NULL;
	ret->context_ref = NULL;
	ret->line_rangeVec = vector_new();
	return ret;
}

void enviroment_add_range(enviroment* self, int lineno) {
	//空なので追加
	if (vector_empty(self->line_rangeVec)) {
		line_range* lr = line_range_new();
		lr->start_offset = 0;
		lr->end_offset = 0;
		lr->lineno = lineno;
		vector_push(self->line_rangeVec, lr);
		return;
	}
	//空ではないなら、
	//最後についかしたレンジを伸ばすか新たに追加する
	line_range* lrt = (line_range*)vector_top(self->line_rangeVec);
	if (lrt->lineno == lineno) {
		lrt->end_offset = self->buf->source->length;
	} else {
		line_range* lr = line_range_new();
		lr->start_offset = self->buf->source->length;
		lr->end_offset = self->buf->source->length;
		lr->lineno = lineno;
		vector_push(self->line_rangeVec, lr);
	}
}

void enviroment_op_dump(enviroment * self, int depth) {
	opcode_buf* buf = self->buf;
	line_range* lr = NULL;
	int lrPos = -1;
	for (int i = 0; i < buf->source->length; i++) {
		text_putindent(depth);
		i = opcode_print(buf->source, i);
		if (!vector_empty(self->line_rangeVec)) {
			if (lr == NULL) {
				lr = vector_at(self->line_rangeVec, 0);
				lrPos = 0;
			} else {
				if (i > lr->end_offset) {
					lrPos++;
					if (lrPos < self->line_rangeVec->length) {
						lr = vector_at(self->line_rangeVec, lrPos);
					}
				}
			}
		}
		if (lr != NULL) {
			text_printf("<%d>", lr->lineno);
		}
		text_putline();
	}
	text_putline();
}

int enviroment_add_constant_int(enviroment * self, int i) {
	int len = self->constant_pool->length;
	enviroment_add_constant(self, object_int_new(i));
	return len;
}

int enviroment_add_constant_double(enviroment * self, double d) {
	int len = self->constant_pool->length;
	enviroment_add_constant(self, object_double_new(d));
	return len;
}

int enviroment_add_constant_char(enviroment * self, char c) {
	int len = self->constant_pool->length;
	enviroment_add_constant(self, object_char_new(c));
	return len;
}

int enviroment_add_constant_string(enviroment * self, const char * s) {
	int len = self->constant_pool->length;
	enviroment_add_constant(self, object_string_new(s));
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

void enviroment_delete(enviroment * self) {
	//text_printfln("deleted env %s", self->context_cll->filename);
	//text_printfln("delete pool---");
	vector_delete(self->constant_pool, enviroment_constant_pool_delete);

	vector_delete(self->line_rangeVec, enviroment_line_range_delete);
	
	opcode_buf_delete(self->buf);
	symbol_table_delete(self->sym_table);
	MEM_FREE(self);
	//text_printfln("---delete pool");
}

//private
static void enviroment_constant_pool_delete(vector_item item) {
	//StringやArrayはここで中身を削除する必要がある
	enviroment_object_delete((object*)item);
	//object_delete((object*)item);
}

static void enviroment_line_range_delete(vector_item item) {
	line_range* e = (line_range*)item;
	line_range_delete(e);
}

static void enviroment_add_constant(enviroment* self, object* o) {
	vector_push(self->constant_pool, o);
	assert(o->paint == paint_onexit);
}

static void enviroment_object_delete(object* obj) {
	if (obj == NULL) {
		return;
	}
	type* tp = obj->type;
	char* name = type_name(tp);
	assert(obj->paint == paint_onexit);
	//*
	//enviromentが削除される時点では、
	//すでにスレッドとVMの関連付けが解除されていて、
	//GCを実行することができないので自分で開放する。
	//FIXME:この方法だと、
	//定数がフィールドに定数を含む場合に二重開放される
	if (obj->tag == object_ref) {
		for (int i = 0; i < obj->u.field_vec->length; i++) {
			object* e = (object*)vector_at(obj->u.field_vec, i);
			enviroment_object_delete(e);
		}
	}
	if (obj->tag == object_string) {
		for (int i = 0; i < obj->u.field_vec->length; i++) {
			object* e = (object*)vector_at(obj->u.field_vec, i);
			enviroment_object_delete(e);
		}
	}
	if (obj->type == sg_array_class()) {
		for (int i = 0; i < obj->native_slot_vec->length; i++) {
			object* e = (object*)vector_at(obj->native_slot_vec, i);
			enviroment_object_delete(e);
		}
	}
	//text_printfln("delete object %s", type_name(obj->type));
	object_delete(obj);
}

#include "opcode_buf.h"
#include <stdlib.h>
#include "opcode.h"
#include "../util/mem.h"
#include "../util/text.h"

//proto
static void opcode_buf_delete_label(vector_item item);
static void opcode_buf_delete_lazy_int(vector_item item);
static void opcode_buf_copy(opcode_buf* src, opcode_buf* dst);

opcode_buf * opcode_buf_new() {
	opcode_buf* ret = (opcode_buf*)MEM_MALLOC(sizeof(opcode_buf));
	ret->labels = vector_new();
	ret->source = vector_new();
	ret->lazy_tbl = vector_new();
	return ret;
}

int opcode_buf_add(opcode_buf * self, vector_item item) {
	int len = self->source->length;
	vector_push(self->source, item);
	return len;
}

label * opcode_buf_label(opcode_buf * self, int index) {
	label* ret = label_new(index);
	vector_push(self->labels, ret);
	return ret;
}

lazy_int* opcode_buf_lazy(opcode_buf* self, int val) {
	lazy_int* ret = lazy_int_new(val);
	vector_push(self->lazy_tbl, ret);
	return ret;
}

int opcode_buf_nop(opcode_buf * self) {
	int len = self->source->length;
	opcode_buf_add(self, op_nop);
	return len;
}

void opcode_buf_dump(opcode_buf * self, int depth) {
	//opcode_buf* buf = self->u.script_method->env->buf;
	for (int i = 0; i < self->source->length; i++) {
		text_putindent(depth);
		i = opcode_print(self->source, i);
		text_putline();
	}
	text_putline();
}

opcode_buf * opcode_buf_merge(opcode_buf * a, opcode_buf * b) {
	opcode_buf* ret = opcode_buf_new();
	opcode_buf_copy(a, ret);
	opcode_buf_copy(b, ret);
	return ret;
}

void opcode_buf_delete(opcode_buf * self) {
	if (self == NULL) {
		return;
	}
	vector_delete(self->source, vector_deleter_null);
	vector_delete(self->labels, opcode_buf_delete_label);
	vector_delete(self->lazy_tbl, opcode_buf_delete_lazy_int);
	MEM_FREE(self);
}


//private
static void opcode_buf_delete_label(vector_item item) {
	label* l = (label*)item;
	label_delete(l);
}

static void opcode_buf_delete_lazy_int(vector_item item) {
	lazy_int* l = (lazy_int*)item;
	lazy_int_delete(l);
}

static void opcode_buf_copy(opcode_buf* src, opcode_buf* dst) {
	for (int i = 0; i < src->source->length; i++) {
		vector_item e = vector_at(src->source, i);
		if (e == op_goto ||
			e == op_goto_if_false ||
			e == op_goto_if_true) {

			opcode_buf_add(dst, e);
			label* lb = (label*)vector_at(src->source, ++i);
			opcode_buf_add(dst, e);
			vector_push(dst->labels, lb);
		} else {
			opcode_buf_add(dst, e);
		}
	}
}

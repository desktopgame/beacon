#include "opcode_buf.h"
#include <stdlib.h>
#include "opcode.h"
#include "../util/mem.h"
#include "../util/text.h"

//proto
static void opcode_buf_delete_label(vector_item item);
static void opcode_buf_copy(opcode_buf* src, opcode_buf* dst);

opcode_buf * opcode_buf_new() {
	opcode_buf* ret = (opcode_buf*)MEM_MALLOC(sizeof(opcode_buf));
	ret->label_vec = vector_new();
	ret->source_vec = vector_new();
	return ret;
}

int opcode_buf_add(opcode_buf * self, vector_item item) {
	int len = self->source_vec->length;
	vector_push(self->source_vec, item);
	return len;
}

label * opcode_buf_label(opcode_buf * self, int index) {
	label* ret = label_new(index);
	vector_push(self->label_vec, ret);
	return ret;
}

int opcode_buf_nop(opcode_buf * self) {
	int len = self->source_vec->length;
	opcode_buf_add(self, op_nop);
	return len;
}

void opcode_buf_dump(opcode_buf * self, int depth) {
	for (int i = 0; i < self->source_vec->length; i++) {
		io_printi(depth);
		i = opcode_print(self->source_vec, i);
		io_println();
	}
	io_println();
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
	vector_delete(self->source_vec, vector_deleter_null);
	vector_delete(self->label_vec, opcode_buf_delete_label);
	MEM_FREE(self);
}


//private
static void opcode_buf_delete_label(vector_item item) {
	label* l = (label*)item;
	label_delete(l);
}

static void opcode_buf_copy(opcode_buf* src, opcode_buf* dst) {
	for (int i = 0; i < src->source_vec->length; i++) {
		vector_item e = vector_at(src->source_vec, i);
		if (e == op_goto ||
			e == op_goto_if_false ||
			e == op_goto_if_true) {

			opcode_buf_add(dst, e);
			label* lb = (label*)vector_at(src->source_vec, ++i);
			opcode_buf_add(dst, e);
			vector_push(dst->label_vec, lb);
		} else {
			opcode_buf_add(dst, e);
		}
	}
}

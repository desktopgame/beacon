#include "opcode_buf.h"
#include <stdlib.h>
#include "opcode.h"
#include "../util/mem.h"
#include "../util/text.h"

//proto
static void opcode_buf_delete_label(VectorItem item);
static void opcode_buf_copy(opcode_buf* src, opcode_buf* dst);

opcode_buf * opcode_buf_new() {
	opcode_buf* ret = (opcode_buf*)MEM_MALLOC(sizeof(opcode_buf));
	ret->label_vec = NewVector();
	ret->source_vec = NewVector();
	return ret;
}

int opcode_buf_add(opcode_buf * self, VectorItem item) {
	int len = self->source_vec->length;
	PushVector(self->source_vec, item);
	return len;
}

label * opcode_buf_label(opcode_buf * self, int index) {
	label* ret = label_new(index);
	PushVector(self->label_vec, ret);
	return ret;
}

int opcode_buf_nop(opcode_buf * self) {
	int len = self->source_vec->length;
	opcode_buf_add(self, op_nop);
	return len;
}

void opcode_buf_dump(opcode_buf * self, int depth) {
	for (int i = 0; i < self->source_vec->length; i++) {
		Printi(depth);
		i = opcode_print(self->source_vec, i);
		Println();
	}
	Println();
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
	DeleteVector(self->source_vec, VectorDeleterOfNull);
	DeleteVector(self->label_vec, opcode_buf_delete_label);
	MEM_FREE(self);
}


//private
static void opcode_buf_delete_label(VectorItem item) {
	label* l = (label*)item;
	label_delete(l);
}

static void opcode_buf_copy(opcode_buf* src, opcode_buf* dst) {
	for (int i = 0; i < src->source_vec->length; i++) {
		VectorItem e = AtVector(src->source_vec, i);
		if (e == op_goto ||
			e == op_goto_if_false ||
			e == op_goto_if_true) {

			opcode_buf_add(dst, e);
			label* lb = (label*)AtVector(src->source_vec, ++i);
			opcode_buf_add(dst, e);
			PushVector(dst->label_vec, lb);
		} else {
			opcode_buf_add(dst, e);
		}
	}
}

#include "opcode_buf.h"
#include <stdlib.h>
#include "opcode.h"
#include "../util/mem.h"
#include "../util/text.h"

//proto
static void DeleteOpcodeBuf_label(VectorItem item);
static void opcode_buf_copy(opcode_buf* src, opcode_buf* dst);

opcode_buf * NewOpcodeBuf() {
	opcode_buf* ret = (opcode_buf*)MEM_MALLOC(sizeof(opcode_buf));
	ret->label_vec = NewVector();
	ret->source_vec = NewVector();
	return ret;
}

int AddOpcodeBuf(opcode_buf * self, VectorItem item) {
	int len = self->source_vec->Length;
	PushVector(self->source_vec, item);
	return len;
}

label * AddLabelOpcodeBuf(opcode_buf * self, int index) {
	label* ret = NewLabel(index);
	PushVector(self->label_vec, ret);
	return ret;
}

int AddNOPOpcodeBuf(opcode_buf * self) {
	int len = self->source_vec->Length;
	AddOpcodeBuf(self, OP_NOP);
	return len;
}

void DumpOpcodeBuf(opcode_buf * self, int depth) {
	for (int i = 0; i < self->source_vec->Length; i++) {
		Printi(depth);
		i = PrintOpcode(self->source_vec, i);
		Println();
	}
	Println();
}

opcode_buf * MergeOpcodeBuf(opcode_buf * a, opcode_buf * b) {
	opcode_buf* ret = NewOpcodeBuf();
	opcode_buf_copy(a, ret);
	opcode_buf_copy(b, ret);
	return ret;
}

void DeleteOpcodeBuf(opcode_buf * self) {
	if (self == NULL) {
		return;
	}
	DeleteVector(self->source_vec, VectorDeleterOfNull);
	DeleteVector(self->label_vec, DeleteOpcodeBuf_label);
	MEM_FREE(self);
}


//private
static void DeleteOpcodeBuf_label(VectorItem item) {
	label* l = (label*)item;
	DeleteLabel(l);
}

static void opcode_buf_copy(opcode_buf* src, opcode_buf* dst) {
	for (int i = 0; i < src->source_vec->Length; i++) {
		VectorItem e = AtVector(src->source_vec, i);
		if (e == OP_GOTO ||
			e == OP_GOTO_if_false ||
			e == OP_GOTO_if_true) {

			AddOpcodeBuf(dst, e);
			label* lb = (label*)AtVector(src->source_vec, ++i);
			AddOpcodeBuf(dst, e);
			PushVector(dst->label_vec, lb);
		} else {
			AddOpcodeBuf(dst, e);
		}
	}
}

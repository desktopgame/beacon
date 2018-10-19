#include "opcode_buf.h"
#include <stdlib.h>
#include "opcode.h"
#include "../util/mem.h"
#include "../util/text.h"

//proto
static void DeleteOpcodeBuf_label(VectorItem item);
static void OpcodeBuf_copy(OpcodeBuf* src, OpcodeBuf* dst);

OpcodeBuf * NewOpcodeBuf() {
	OpcodeBuf* ret = (OpcodeBuf*)MEM_MALLOC(sizeof(OpcodeBuf));
	ret->LabelTable = NewVector();
	ret->Instructions = NewVector();
	return ret;
}

int AddOpcodeBuf(OpcodeBuf * self, VectorItem item) {
	int len = self->Instructions->Length;
	PushVector(self->Instructions, item);
	return len;
}

Label * AddLabelOpcodeBuf(OpcodeBuf * self, int index) {
	Label* ret = NewLabel(index);
	PushVector(self->LabelTable, ret);
	return ret;
}

int AddNOPOpcodeBuf(OpcodeBuf * self) {
	int len = self->Instructions->Length;
	AddOpcodeBuf(self, OP_NOP);
	return len;
}

void DumpOpcodeBuf(OpcodeBuf * self, int depth) {
	for (int i = 0; i < self->Instructions->Length; i++) {
		Printi(depth);
		i = PrintOpcode(self->Instructions, i);
		Println();
	}
	Println();
}

OpcodeBuf * MergeOpcodeBuf(OpcodeBuf * a, OpcodeBuf * b) {
	OpcodeBuf* ret = NewOpcodeBuf();
	OpcodeBuf_copy(a, ret);
	OpcodeBuf_copy(b, ret);
	return ret;
}

void DeleteOpcodeBuf(OpcodeBuf * self) {
	if (self == NULL) {
		return;
	}
	DeleteVector(self->Instructions, VectorDeleterOfNull);
	DeleteVector(self->LabelTable, DeleteOpcodeBuf_label);
	MEM_FREE(self);
}


//private
static void DeleteOpcodeBuf_label(VectorItem item) {
	Label* l = (Label*)item;
	DeleteLabel(l);
}

static void OpcodeBuf_copy(OpcodeBuf* src, OpcodeBuf* dst) {
	for (int i = 0; i < src->Instructions->Length; i++) {
		VectorItem e = AtVector(src->Instructions, i);
		if (e == OP_GOTO ||
			e == OP_GOTO_if_false ||
			e == OP_GOTO_if_true) {

			AddOpcodeBuf(dst, e);
			Label* lb = (Label*)AtVector(src->Instructions, ++i);
			AddOpcodeBuf(dst, e);
			PushVector(dst->LabelTable, lb);
		} else {
			AddOpcodeBuf(dst, e);
		}
	}
}

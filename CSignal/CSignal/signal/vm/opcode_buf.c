#include "opcode_buf.h"
#include <stdlib.h>

//proto
static opcode_buf_delete_label(vector_item item);

opcode_buf * opcode_buf_new() {
	opcode_buf* ret = (opcode_buf*)malloc(sizeof(opcode_buf));
	ret->labels = vector_new();
	ret->source = vector_new();
	return ret;
}

void opcode_buf_add(opcode_buf * self, vector_item item) {
	vector_push(self->source, item);
}

label * opcode_buf_label(opcode_buf * self, int index) {
	label* ret = label_new(index);
	vector_push(self->labels, ret);
	return ret;
}

void opcode_buf_delete(opcode_buf * self) {
	vector_delete(self->source, vector_deleter_null);
	vector_delete(self->labels, opcode_buf_delete_label);
	free(self);
}


//private
static opcode_buf_delete_label(vector_item item) {
	label* l = (label*)item;
	label_delete(l);
}
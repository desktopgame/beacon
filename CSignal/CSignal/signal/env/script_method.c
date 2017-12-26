#include "script_method.h"
#include <stdlib.h>
#include "../vm/vm.h"
#include "method.h"

script_method * script_method_new() {
	script_method* ret = (script_method*)malloc(sizeof(script_method));
	//ret->source = vector_new();
	ret->buf = NULL;
	return ret;
}

void script_method_execute(script_method * self, method* parent, vm * vm) {
}

void script_method_delete(script_method * self) {
	opcode_buf_delete(self->buf);
//	vector_delete(self->source, vector_deleter_null);
	free(self);
}

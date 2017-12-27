#include "method.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"
#include "parameter.h"
#include "../vm/vm.h"

//proto
static void method_parameter_delete(vector_item item);

method * method_new(const char * name) {
	method* ret = (method*)malloc(sizeof(method));
	ret->name = text_strdup(name);
	ret->parameter_list = vector_new();
	ret->type = method_type_script;
	return ret;
}

void method_execute(method* self, vm * vm) {
	if (self->type == method_type_script) {
		script_method_execute(self->u.script_method, self, vm);
	} else if (self->type == method_type_native) {
		native_method_execute(self->u.native_method, self, vm);
	}
}

void method_dump(method * self, int depth) {
	text_putindent(depth);
	printf("method %s", self->name);
	printf("(");
	for (int i = 0; i < self->parameter_list->length; i++) {
		vector_item e = vector_at(self->parameter_list, i);
		parameter* p = (parameter*)e;
		printf("%s", p->name);
		if ((i + 1) < self->parameter_list->length) {
			printf(" ");
		}
	}
	printf(")");
	text_putline();
	if (self->type == method_type_script) {
		text_putindent(depth);

		opcode_buf* buf = self->u.script_method->buf;
		for (int i = 0; i < buf->source->length; i++) {
			text_putindent(depth + 1);
			i = opcode_print(buf, i);
			text_putline();
		}
		text_putline();
	}
}

void method_delete(method * self) {
	free(self->name);
	vector_delete(self->parameter_list, method_parameter_delete);
	if (self->type == method_type_script) {
		script_method_delete(self->u.script_method);
	} else if (self->type == method_type_native) {
		native_method_delete(self->u.native_method);
	}
	free(self);
}

//private
static void method_parameter_delete(vector_item item) {
	parameter* e = (parameter*)item;
	parameter_delete(e);
}

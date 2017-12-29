#include "method.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"
#include "class.h"
#include "parameter.h"
#include "../util/mem.h"
#include "../vm/vm.h"

//proto
static void method_parameter_delete(vector_item item);

method * method_new(const char * name) {
	method* ret = (method*)MEM_MALLOC(sizeof(method));
	ret->name = text_strdup(name);
	ret->parameter_list = vector_new();
	ret->type = method_type_script;
	ret->access = access_public;
	ret->modifier = modifier_none;
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
	access_print(self->access);
	printf(" ");
	modifier_print(self->modifier);
	printf(" method %s", self->name);
	printf("(");
	for (int i = 0; i < self->parameter_list->length; i++) {
		vector_item e = vector_at(self->parameter_list, i);
		parameter* p = (parameter*)e;
		printf("%s %s", p->classz->name, p->name);
		if ((i + 1) < self->parameter_list->length) {
			printf(" ");
		}
	}
	if (self->return_type == NULL) {
		printf(") -> NULL");
	} else {
		printf(") -> %s", self->return_type->name);
	}
	text_putline();
	if (self->type == method_type_script) {
		opcode_buf_dump(self->u.script_method->env->buf, depth + 1);
	}
}

void method_delete(method * self) {
	MEM_FREE(self->name);
	vector_delete(self->parameter_list, method_parameter_delete);
	if (self->type == method_type_script) {
		script_method_delete(self->u.script_method);
	} else if (self->type == method_type_native) {
		native_method_delete(self->u.native_method);
	}
	MEM_FREE(self);
}

//private
static void method_parameter_delete(vector_item item) {
	parameter* e = (parameter*)item;
	parameter_delete(e);
}

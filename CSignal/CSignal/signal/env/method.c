#include "method.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"
#include "parameter.h"
#include "parameter_list.h"
#include "../vm/vm.h"

method * method_new(const char * name) {
	method* ret = (method*)malloc(sizeof(method));
	ret->name = text_strdup(name);
	ret->parameter_list = parameter_list_new();
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
	parameter_list* pointee = self->parameter_list;
	while (1) {
		parameter* param = (parameter*)pointee->item;
		printf("%s", param->name);
		pointee = pointee->next;
		if (pointee == NULL || pointee->item == NULL) {
			break;
		} else printf(" ");
	}
	printf(")");
	text_putline();
}

void method_delete(method * self) {
	free(self->name);
	parameter_list_delete(self->parameter_list);
	if (self->type == method_type_script) {
		script_method_delete(self->u.script_method);
	} else if (self->type == method_type_native) {
		native_method_delete(self->u.native_method);
	}
	free(self);
}

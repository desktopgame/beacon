#include "method.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../util/text.h"
#include "type_interface.h"
#include "parameter.h"
#include "../util/mem.h"
#include "../vm/vm.h"
#include "type_parameter.h"

//proto
static void method_parameter_delete(vector_item item);
static void method_type_parameter_delete(vector_item item);

method * method_new(const char * name) {
	method* ret = (method*)MEM_MALLOC(sizeof(method));
	ret->name = text_strdup(name);
	ret->parameter_list = vector_new();
	ret->type = method_type_script;
	ret->access = access_public;
	ret->modifier = modifier_none;
	ret->parent = NULL;
	ret->type_parameter_list = vector_new();
	return ret;
}

void method_execute(method* self, vm * vm, enviroment* env) {
	if (self->type == method_type_script) {
		script_method_execute(self->u.script_method, self, vm, env);
	} else if (self->type == method_type_native) {
		native_method_execute(self->u.native_method, self, vm, env);
	}
}

void method_dump(method * self, int depth) {
	text_putindent(depth);
	access_print(self->access);
	text_printf(" ");
	modifier_print(self->modifier);
	text_printf(" method %s", self->name);
	type_parameter_print(self->type_parameter_list);
	text_printf("(");
	for (int i = 0; i < self->parameter_list->length; i++) {
		vector_item e = vector_at(self->parameter_list, i);
		parameter* p = (parameter*)e;
		text_printf("%s %s", type_name(p->type), p->name);
		if ((i + 1) < self->parameter_list->length) {
			text_printf(" ");
		}
	}
	if (self->return_type == NULL) {
		text_printf(") -> NULL");
	} else {
		text_printf(") -> %s", type_name(self->return_type));
	}
	text_putline();
	if (self->type == method_type_script) {
		opcode_buf_dump(self->u.script_method->env->buf, depth + 1);
	}
}

bool method_equal(method * a, method * b) {
	if (strcmp(a->name, b->name) ||
		a->parameter_list->length != b->parameter_list->length) {
		return false;
	}
	for (int i = 0; i < a->parameter_list->length; i++) {
		type* ap = ((parameter*)vector_at(a->parameter_list, i))->type;
		type* bp = ((parameter*)vector_at(b->parameter_list, i))->type;
		if (ap != bp) { return false; }
	}
	type* ar = a->return_type;
	type* br = b->return_type;
	if (ar == br) {
		return true;
	}
	//共変戻り値
	//FIXME:あとで
	return false;
	//return class_castable(b, a);
}

void method_delete(method * self) {
	MEM_FREE(self->name);
	vector_delete(self->type_parameter_list, method_parameter_delete);
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

static void method_type_parameter_delete(vector_item item) {
	type_parameter* e = (type_parameter*)item;
	type_parameter_delete(e);
}

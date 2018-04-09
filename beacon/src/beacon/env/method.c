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
#include "generic_type.h"
#include <assert.h>

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
		virtual_type_print(&p->vtype);
		text_printf(" %s", p->name);
		if ((i + 1) < self->parameter_list->length) {
			text_printf(" ");
		}
	}
	text_printf(") -> ");
	virtual_type_print(&self->return_vtype);
	text_putline();
	if (self->type == method_type_script) {
		opcode_buf_dump(self->u.script_method->env->buf, depth + 1);
	}
}

bool method_override(method* superM, method* subM) {
	//名前が違うか引数の数が違う
	if (strcmp(superM->name, subM->name) ||
		superM->parameter_list->length != subM->parameter_list->length) {
		return false;
	}
	return true;
	/*
	//全ての引数を比較
	for (int i = 0; i < superM->parameter_list->length; i++) {
		virtual_type ap = ((parameter*)vector_at(superM->parameter_list, i))->vtype;
		virtual_type bp = ((parameter*)vector_at(subM->parameter_list, i))->vtype;
		if (!virtual_type_eq(&ap, &bp)) { return false; }
	}
	virtual_type ar = superM->return_vtype;
	virtual_type br = subM->return_vtype;
	if (virtual_type_eq(&ar, &br)) {
		return true;
	}
	//共変戻り値
	//FIXME:あとで
	return false;
	//return class_castable(b, a);
	//*/
}

int method_for_generic_index(method * self, const char * name) {
	int ret = -1;
	for (int i = 0; i < self->type_parameter_list->length; i++) {
		type_parameter* e = (type_parameter*)vector_at(self->type_parameter_list, i);
		if (!strcmp(e->name, name)) {
			ret = i;
			break;
		}
	}
	return ret;
}

void method_delete(method * self) {
	text_printf("%s#%s\n", type_name(self->parent), self->name);
	MEM_FREE(self->name);
	vector_delete(self->type_parameter_list, method_type_parameter_delete);
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

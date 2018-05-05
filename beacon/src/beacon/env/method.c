#include "method.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../util/text.h"
#include "type_interface.h"
#include "parameter.h"
#include "namespace.h"
#include "object.h"
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
	ret->return_gtype = NULL;
	return ret;
}

void method_execute(method* self, frame * fr, enviroment* env) {
	if (self->type == method_type_script) {
		script_method_execute(self->u.script_method, self, fr, env);
	} else if (self->type == method_type_native) {
		frame* a = frame_sub(fr);
		//レシーバも
		if(!modifier_is_static(self->modifier)) {
			vector_assign(a->ref_stack, 0, vector_pop(fr->value_stack));
		}
		//引数を引き継ぐ
		int len = self->parameter_list->length;
		for(int i=0; i<len; i++) {
			object* ARG = vector_pop(fr->value_stack);
			assert(ARG != NULL);
			vector_assign(a->ref_stack, (len - i), ARG);
		}
		//メソッドに渡された型引数を引き継ぐ
		int typeparams = self->type_parameter_list->length;
		for(int i=0; i<typeparams; i++) {
			vector_assign(a->type_args_vec, (typeparams - i) - 1, vector_pop(fr->type_args_vec));
		}
		native_method_execute(self->u.native_method, self, a, env);
		//戻り値を残す
		if(self->return_gtype != TYPE_VOID->generic_self) {
			vector_push(fr->value_stack, vector_pop(a->value_stack));
		}
		frame_delete(a);
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
		generic_type_print(p->gtype);
		text_printf(" %s", p->name);
		if ((i + 1) < self->parameter_list->length) {
			text_printf(" ");
		}
	}
	text_printf(") -> ");
	generic_type_print(self->return_gtype);
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
	//text_printf("%s#%s\n", type_name(self->parent), self->name);
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

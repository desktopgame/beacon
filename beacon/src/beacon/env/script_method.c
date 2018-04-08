#include "script_method.h"
#include <stdlib.h>
#include "../vm/vm.h"
#include "method.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "type_interface.h"
#include "virtual_type.h"
#include "namespace.h"
#include "object.h"
#include "generic_type.h"

script_method * script_method_new() {
	script_method* ret = (script_method*)MEM_MALLOC(sizeof(script_method));
	//ret->source = vector_new();
	ret->env = NULL;
	return ret;
}

void script_method_execute(script_method * self, method* parent, vm * vmachine, enviroment* env) {
	vm* sub = vm_sub(vmachine);
	if (!modifier_is_static(parent->modifier)) {
		vector_push(sub->value_stack, vector_pop(vmachine->value_stack));
	}
	for (int i = 0; i < parent->parameter_list->length; i++) {
		vector_push(sub->value_stack, object_copy(vector_pop(vmachine->value_stack)));
	}
	text_putindent(sub->level);
	text_printfln("[ %s#%s ]", type_name(parent->parent), parent->name);
	//enviroment_op_dump(self->env, sub->level);
	//opcode_buf_dump(self->env->buf, sub->level);
	vm_execute(sub, self->env);
	//戻り値が Void 以外ならスタックトップの値を引き継ぐ
	if (!virtual_type_void(&parent->return_vtype)) {
		object* o = (object*)vector_pop(sub->value_stack);
		vector_push(vmachine->value_stack, o);
	}
	vm_delete(sub);
}

void script_method_delete(script_method * self) {
	enviroment_delete(self->env);
//	vector_delete(self->source, vector_deleter_null);
	MEM_FREE(self);
}

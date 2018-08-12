#include "script_method.h"
#include <stdlib.h>
#include "../vm/vm.h"
#include "method.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "type_interface.h"
//#include "virtual_type.h"
#include "namespace.h"
#include "object.h"
#include "generic_type.h"

script_method * script_method_new() {
	script_method* ret = (script_method*)MEM_MALLOC(sizeof(script_method));
	ret->env = NULL;
	return ret;
}

void script_method_execute(script_method * self, method* parent, frame * fr, enviroment* env) {
	#if defined(DEBUG)
	const char* name = string_pool_ref2str(parent->namev);
	//printf("[%s]\n", name);
	#endif
	frame* sub = frame_sub(fr);
	//enviroment_op_dump(self->env, sub->level);
	sub->receiver = parent->parent;
	if (!modifier_is_static(parent->modifier)) {
		vector_push(sub->value_stack, vector_pop(fr->value_stack));
	}
	for (int i = 0; i < parent->parameter_list->length; i++) {
		vector_push(sub->value_stack, object_copy(vector_pop(fr->value_stack)));
	}
	//メソッドに渡された型引数を引き継ぐ
	int typeparams = parent->type_parameter_list->length;
	for(int i=0; i<typeparams; i++) {
		vector_assign(sub->type_args_vec, (typeparams - i) - 1, vector_pop(fr->type_args_vec));
	}
	vm_execute(sub, self->env);
	//戻り値が Void 以外ならスタックトップの値を引き継ぐ
	if(parent->return_gtype != TYPE_VOID->generic_self) {
		object* o = (object*)vector_pop(sub->value_stack);
		vector_push(fr->value_stack, NON_NULL(o));
	}
	frame_delete(sub);
}

void script_method_delete(script_method * self) {
	enviroment_delete(self->env);
	MEM_FREE(self);
}

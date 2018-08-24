#include "script_method.h"
#include <stdlib.h>
#include "../vm/vm.h"
#include "method.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../thread/thread.h"
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
#endif
	frame* sub = frame_sub(fr);
	call_frame* cfr = NULL;
	sub->receiver = parent->parent;
	vector* aArgs = vector_new();
	vector* aTArgs = vector_new();
	if (!modifier_is_static(parent->modifier)) {
		object* receiver_obj = vector_pop(fr->value_stack);
		vector_push(sub->value_stack, receiver_obj);
		cfr = call_context_push(sg_thread_context(), frame_instance_invoke_T);
		cfr->u.instance_invoke.receiver = receiver_obj->gtype;
		cfr->u.instance_invoke.args = aArgs;
		cfr->u.instance_invoke.typeargs = aTArgs;
	} else {
		cfr = call_context_push(sg_thread_context(), frame_static_invoke_T);
		cfr->u.static_invoke.args = aArgs;
		cfr->u.static_invoke.typeargs = aTArgs;
	}
	for (int i = 0; i < parent->parameters->length; i++) {
		object* arg = object_copy(vector_pop(fr->value_stack));
		vector_push(sub->value_stack, arg);
		vector_assign(aArgs, (parent->parameters->length - i), arg);
	}
	//メソッドに渡された型引数を引き継ぐ
	int typeparams = parent->type_parameters->length;
	for(int i=0; i<typeparams; i++) {
		vector_item e = vector_pop(fr->type_args_vec);
		vector_assign(sub->type_args_vec, (typeparams - i) - 1, e);
		vector_assign(aTArgs, (typeparams - i) - 1, e);
	}
	vm_execute(sub, self->env);
	//戻り値が Void 以外ならスタックトップの値を引き継ぐ
	//例外によって終了した場合には戻り値がない
	if(parent->return_gtype != TYPE_VOID->generic_self &&
	   sub->value_stack->length > 0) {
		object* o = (object*)vector_pop(sub->value_stack);
		vector_push(fr->value_stack, NON_NULL(o));
	}
	vector_delete(aArgs, vector_deleter_null);
	vector_delete(aTArgs, vector_deleter_null);
	call_context_pop(sg_thread_context());
	frame_delete(sub);
}

void script_method_delete(script_method * self) {
	enviroment_delete(self->env);
	MEM_FREE(self);
}

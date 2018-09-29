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
	const char* name = Ref2Str(parent->namev);
#endif
	frame* sub = frame_sub(fr);
	call_frame* cfr = NULL;
	sub->receiver = parent->parent;
	Vector* aArgs = NewVector();
	Vector* aTArgs = NewVector();
	if (!IsStaticModifier(parent->modifier)) {
		object* receiver_obj = PopVector(fr->value_stack);
		PushVector(sub->value_stack, receiver_obj);
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
		object* arg = object_copy(PopVector(fr->value_stack));
		PushVector(sub->value_stack, arg);
		AssignVector(aArgs, (parent->parameters->length - i), arg);
	}
	//メソッドに渡された型引数を引き継ぐ
	int typeparams = parent->type_parameters->length;
	for(int i=0; i<typeparams; i++) {
		VectorItem e = PopVector(fr->type_args_vec);
		AssignVector(sub->type_args_vec, (typeparams - i) - 1, e);
		AssignVector(aTArgs, (typeparams - i) - 1, e);
	}
	vm_execute(sub, self->env);
	//戻り値が Void 以外ならスタックトップの値を引き継ぐ
	//例外によって終了した場合には戻り値がない
	if(parent->return_gtype != TYPE_VOID->generic_self &&
	   sub->value_stack->length > 0) {
		object* o = (object*)PopVector(sub->value_stack);
		PushVector(fr->value_stack, NON_NULL(o));
	}
	DeleteVector(aArgs, VectorDeleterOfNull);
	DeleteVector(aTArgs, VectorDeleterOfNull);
	call_context_pop(sg_thread_context());
	frame_delete(sub);
}

void script_method_delete(script_method * self) {
	enviroment_delete(self->env);
	MEM_FREE(self);
}

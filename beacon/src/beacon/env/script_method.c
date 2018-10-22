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

script_method * NewScriptMethod() {
	script_method* ret = (script_method*)MEM_MALLOC(sizeof(script_method));
	ret->env = NULL;
	return ret;
}

void ExecuteScriptMethod(script_method * self, method* parent, frame * fr, Enviroment* env) {
#if defined(DEBUG)
	const char* name = Ref2Str(parent->namev);
#endif
	frame* sub = SubFrame(fr);
	call_frame* cfr = NULL;
	sub->receiver = parent->parent;
	Vector* aArgs = NewVector();
	Vector* aTArgs = NewVector();
	if (!IsStaticModifier(parent->modifier)) {
		object* receiver_obj = PopVector(fr->value_stack);
		PushVector(sub->value_stack, receiver_obj);
		cfr = PushCallContext(GetSGThreadCContext(), FRAME_INSTANCE_INVOKE_T);
		cfr->u.instance_invoke.Receiver = receiver_obj->gtype;
		cfr->u.instance_invoke.Args = aArgs;
		cfr->u.instance_invoke.TypeArgs = aTArgs;
	} else {
		cfr = PushCallContext(GetSGThreadCContext(), FRAME_STATIC_INVOKE_T);
		cfr->u.static_invoke.Args = aArgs;
		cfr->u.static_invoke.TypeArgs = aTArgs;
	}
	for (int i = 0; i < parent->parameters->Length; i++) {
		object* arg = CopyObject(PopVector(fr->value_stack));
		PushVector(sub->value_stack, arg);
		AssignVector(aArgs, (parent->parameters->Length - i), arg);
	}
	//メソッドに渡された型引数を引き継ぐ
	int typeparams = parent->type_parameters->Length;
	for(int i=0; i<typeparams; i++) {
		VectorItem e = PopVector(fr->type_args_vec);
		AssignVector(sub->type_args_vec, (typeparams - i) - 1, e);
		AssignVector(aTArgs, (typeparams - i) - 1, e);
	}
	ExecuteVM(sub, self->env);
	//戻り値が Void 以外ならスタックトップの値を引き継ぐ
	//例外によって終了した場合には戻り値がない
	if(parent->return_gtype != TYPE_VOID->generic_self &&
	   sub->value_stack->Length > 0) {
		object* o = (object*)PopVector(sub->value_stack);
		PushVector(fr->value_stack, NON_NULL(o));
	}
	DeleteVector(aArgs, VectorDeleterOfNull);
	DeleteVector(aTArgs, VectorDeleterOfNull);
	PopCallContext(GetSGThreadCContext());
	DeleteFrame(sub);
}

void DeleteScriptMethod(script_method * self) {
	DeleteEnviroment(self->env);
	MEM_FREE(self);
}

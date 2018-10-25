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

void ExecuteScriptMethod(script_method * self, Method* parent, Frame* fr, Enviroment* env) {
#if defined(DEBUG)
	const char* name = Ref2Str(parent->namev);
#endif
	Frame* sub = SubFrame(fr);
	CallFrame* cfr = NULL;
	sub->Receiver = parent->parent;
	Vector* aArgs = NewVector();
	Vector* aTArgs = NewVector();
	if (!IsStaticModifier(parent->modifier)) {
		object* receiver_obj = PopVector(fr->ValueStack);
		PushVector(sub->ValueStack, receiver_obj);
		cfr = PushCallContext(GetSGThreadCContext(), FRAME_INSTANCE_INVOKE_T);
		cfr->Kind.InstanceInvoke.Receiver = receiver_obj->gtype;
		cfr->Kind.InstanceInvoke.Args = aArgs;
		cfr->Kind.InstanceInvoke.TypeArgs = aTArgs;
	} else {
		cfr = PushCallContext(GetSGThreadCContext(), FRAME_STATIC_INVOKE_T);
		cfr->Kind.StaticInvoke.Args = aArgs;
		cfr->Kind.StaticInvoke.TypeArgs = aTArgs;
	}
	for (int i = 0; i < parent->parameters->Length; i++) {
		object* arg = CopyObject(PopVector(fr->ValueStack));
		PushVector(sub->ValueStack, arg);
		AssignVector(aArgs, (parent->parameters->Length - i), arg);
	}
	//メソッドに渡された型引数を引き継ぐ
	int typeparams = parent->type_parameters->Length;
	for(int i=0; i<typeparams; i++) {
		VectorItem e = PopVector(fr->TypeArgs);
		AssignVector(sub->TypeArgs, (typeparams - i) - 1, e);
		AssignVector(aTArgs, (typeparams - i) - 1, e);
	}
	ExecuteVM(sub, self->env);
	//戻り値が Void 以外ならスタックトップの値を引き継ぐ
	//例外によって終了した場合には戻り値がない
	if(parent->return_gtype != TYPE_VOID->generic_self &&
	   sub->ValueStack->Length > 0) {
		object* o = (object*)PopVector(sub->ValueStack);
		PushVector(fr->ValueStack, NON_NULL(o));
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

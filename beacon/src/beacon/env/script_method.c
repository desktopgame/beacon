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

bc_ScriptMethod * bc_NewScriptMethod() {
	bc_ScriptMethod* ret = (bc_ScriptMethod*)MEM_MALLOC(sizeof(bc_ScriptMethod));
	ret->Env = NULL;
	return ret;
}

void bc_ExecuteScriptMethod(bc_ScriptMethod * self, bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
#if defined(DEBUG)
	const char* name = bc_Ref2Str(parent->Name);
#endif
	bc_Frame* sub = bc_SubFrame(fr);
	CallFrame* cfr = NULL;
	sub->Receiver = parent->Parent;
	bc_Vector* aArgs = bc_NewVector();
	bc_Vector* aTArgs = bc_NewVector();
	if (!bc_IsStaticModifier(parent->Modifier)) {
		bc_Object* receiver_obj = bc_PopVector(fr->ValueStack);
		bc_PushVector(sub->ValueStack, receiver_obj);
		cfr = PushCallContext(bc_GetScriptThreadContext(), FRAME_INSTANCE_INVOKE_T);
		cfr->Kind.InstanceInvoke.Receiver = receiver_obj->GType;
		cfr->Kind.InstanceInvoke.Args = aArgs;
		cfr->Kind.InstanceInvoke.TypeArgs = aTArgs;
	} else {
		cfr = PushCallContext(bc_GetScriptThreadContext(), FRAME_STATIC_INVOKE_T);
		cfr->Kind.StaticInvoke.Args = aArgs;
		cfr->Kind.StaticInvoke.TypeArgs = aTArgs;
	}
	for (int i = 0; i < parent->Parameters->Length; i++) {
		bc_Object* arg = bc_CopyObject(bc_PopVector(fr->ValueStack));
		bc_PushVector(sub->ValueStack, arg);
		bc_AssignVector(aArgs, (parent->Parameters->Length - i), arg);
	}
	//メソッドに渡された型引数を引き継ぐ
	int typeparams = parent->TypeParameters->Length;
	for(int i=0; i<typeparams; i++) {
		bc_VectorItem e = bc_PopVector(fr->TypeArgs);
		bc_AssignVector(sub->TypeArgs, (typeparams - i) - 1, e);
		bc_AssignVector(aTArgs, (typeparams - i) - 1, e);
	}
	bc_ExecuteVM(sub, self->Env);
	//戻り値が Void 以外ならスタックトップの値を引き継ぐ
	//例外によって終了した場合には戻り値がない
	if(parent->ReturnGType != BC_TYPE_VOID->GenericSelf &&
	   sub->ValueStack->Length > 0) {
		bc_Object* o = (bc_Object*)bc_PopVector(sub->ValueStack);
		bc_PushVector(fr->ValueStack, NON_NULL(o));
	}
	bc_DeleteVector(aArgs, bc_VectorDeleterOfNull);
	bc_DeleteVector(aTArgs, bc_VectorDeleterOfNull);
	PopCallContext(bc_GetScriptThreadContext());
	bc_DeleteFrame(sub);
}

void bc_DeleteScriptMethod(bc_ScriptMethod * self) {
	bc_DeleteEnviroment(self->Env);
	MEM_FREE(self);
}

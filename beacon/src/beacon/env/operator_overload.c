#include "operator_overload.h"
#include "../util/mem.h"
#include "../vm/frame.h"
#include "../vm/enviroment.h"
#include "../vm/vm.h"
#include "method.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "type_interface.h"
//#include "virtual_type.h"
#include "namespace.h"
#include "object.h"
#include "generic_type.h"
#include "parameter.h"

static void delete_parameter(VectorItem item);

bc_OperatorOverload* bc_NewOperatorOverload(bc_OperatorType type) {
	bc_OperatorOverload* ret = (bc_OperatorOverload*)MEM_MALLOC(sizeof(bc_OperatorOverload));
	ret->Parent = NULL;
	ret->Parameters = NewVector();
	ret->Type = type;
	ret->Env = NULL;
	ret->ReturnGType = NULL;
	return ret;
}

void bc_ExecuteOperatorOverload(bc_OperatorOverload* self, Frame* fr, Enviroment* env) {
	Frame* sub = SubFrame(fr);
	sub->Receiver = fr->Receiver;
	PushVector(sub->ValueStack, PopVector(fr->ValueStack));
	for (int i = 0; i < self->Parameters->Length; i++) {
		PushVector(sub->ValueStack, bc_CopyObject(PopVector(fr->ValueStack)));
	}
	ExecuteVM(sub, self->Env);
	//戻り値が Void 以外ならスタックトップの値を引き継ぐ
	//例外によって終了した場合には戻り値がない
	if(self->ReturnGType != BC_TYPE_VOID->GenericSelf &&
	   sub->ValueStack->Length > 0) {
		bc_Object* o = (bc_Object*)PopVector(sub->ValueStack);
		PushVector(fr->ValueStack, o);
	}
	DeleteFrame(sub);
}

void bc_DeleteOperatorOverload(bc_OperatorOverload* self) {
	DeleteEnviroment(self->Env);
	DeleteVector(self->Parameters, delete_parameter);
	MEM_FREE(self);
}
//private
static void delete_parameter(VectorItem item) {
	bc_Parameter* e = (bc_Parameter*)item;
	bc_DeleteParameter(e);
}
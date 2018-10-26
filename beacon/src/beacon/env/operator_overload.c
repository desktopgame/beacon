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

static void DeleteOperatorOverload_param(VectorItem item);

OperatorOverload* NewOperatorOverload(OperatorType type) {
	OperatorOverload* ret = (OperatorOverload*)MEM_MALLOC(sizeof(OperatorOverload));
	ret->Parent = NULL;
	ret->Parameters = NewVector();
	ret->Type = type;
	ret->Env = NULL;
	ret->ReturnGType = NULL;
	return ret;
}

void ExecuteOperatorOverload(OperatorOverload* self, Frame* fr, Enviroment* env) {
	Frame* sub = SubFrame(fr);
	sub->Receiver = fr->Receiver;
	PushVector(sub->ValueStack, PopVector(fr->ValueStack));
	for (int i = 0; i < self->Parameters->Length; i++) {
		PushVector(sub->ValueStack, CopyObject(PopVector(fr->ValueStack)));
	}
	ExecuteVM(sub, self->Env);
	//戻り値が Void 以外ならスタックトップの値を引き継ぐ
	//例外によって終了した場合には戻り値がない
	if(self->ReturnGType != TYPE_VOID->generic_self &&
	   sub->ValueStack->Length > 0) {
		object* o = (object*)PopVector(sub->ValueStack);
		PushVector(fr->ValueStack, o);
	}
	DeleteFrame(sub);
}

void DeleteOperatorOverload(OperatorOverload* self) {
	DeleteEnviroment(self->Env);
	DeleteVector(self->Parameters, DeleteOperatorOverload_param);
	MEM_FREE(self);
}
//private
static void DeleteOperatorOverload_param(VectorItem item) {
	Parameter* e = (Parameter*)item;
	DeleteParameter(e);
}
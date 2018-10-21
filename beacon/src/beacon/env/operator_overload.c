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

operator_overload* NewOperatorOverload(OperatorType type) {
	operator_overload* ret = (operator_overload*)MEM_MALLOC(sizeof(operator_overload));
	ret->parent = NULL;
	ret->parameter_list = NewVector();
	ret->type = type;
	ret->env = NULL;
	ret->return_gtype = NULL;
	return ret;
}

void ExecuteOperatorOverload(operator_overload* self, frame* fr, Enviroment* env) {
	frame* sub = SubFrame(fr);
	sub->receiver = fr->receiver;
	PushVector(sub->value_stack, PopVector(fr->value_stack));
	for (int i = 0; i < self->parameter_list->Length; i++) {
		PushVector(sub->value_stack, CopyObject(PopVector(fr->value_stack)));
	}
	ExecuteVM(sub, self->env);
	//戻り値が Void 以外ならスタックトップの値を引き継ぐ
	//例外によって終了した場合には戻り値がない
	if(self->return_gtype != TYPE_VOID->generic_self &&
	   sub->value_stack->Length > 0) {
		object* o = (object*)PopVector(sub->value_stack);
		PushVector(fr->value_stack, o);
	}
	DeleteFrame(sub);
}

void DeleteOperatorOverload(operator_overload* self) {
	DeleteEnviroment(self->env);
	DeleteVector(self->parameter_list, DeleteOperatorOverload_param);
	MEM_FREE(self);
}
//private
static void DeleteOperatorOverload_param(VectorItem item) {
	parameter* e = (parameter*)item;
	DeleteParameter(e);
}
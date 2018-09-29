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

static void operator_overload_delete_param(VectorItem item);

operator_overload* operator_overload_new(operator_type type) {
	operator_overload* ret = (operator_overload*)MEM_MALLOC(sizeof(operator_overload));
	ret->parent = NULL;
	ret->parameter_list = NewVector();
	ret->type = type;
	ret->env = NULL;
	ret->return_gtype = NULL;
	return ret;
}

void operator_overload_execute(operator_overload* self, frame* fr, enviroment* env) {
	frame* sub = SubFrame(fr);
	sub->receiver = fr->receiver;
	PushVector(sub->value_stack, PopVector(fr->value_stack));
	for (int i = 0; i < self->parameter_list->length; i++) {
		PushVector(sub->value_stack, object_copy(PopVector(fr->value_stack)));
	}
	vm_execute(sub, self->env);
	//戻り値が Void 以外ならスタックトップの値を引き継ぐ
	//例外によって終了した場合には戻り値がない
	if(self->return_gtype != TYPE_VOID->generic_self &&
	   sub->value_stack->length > 0) {
		object* o = (object*)PopVector(sub->value_stack);
		PushVector(fr->value_stack, o);
	}
	DeleteFrame(sub);
}

void operator_overload_delete(operator_overload* self) {
	DeleteEnviroment(self->env);
	DeleteVector(self->parameter_list, operator_overload_delete_param);
	MEM_FREE(self);
}
//private
static void operator_overload_delete_param(VectorItem item) {
	parameter* e = (parameter*)item;
	parameter_delete(e);
}
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

static void operator_overload_delete_param(vector_item item);

operator_overload* operator_overload_new(operator_type type) {
	operator_overload* ret = (operator_overload*)MEM_MALLOC(sizeof(operator_overload));
	ret->parent = NULL;
	ret->parameter_list = vector_new();
	ret->type = type;
	ret->env = NULL;
	ret->return_gtype = NULL;
	return ret;
}

void operator_overload_execute(operator_overload* self, frame* fr, enviroment* env) {
	frame* sub = frame_sub(fr);
	sub->receiver = fr->receiver;
	vector_push(sub->value_stack, vector_pop(fr->value_stack));
	for (int i = 0; i < self->parameter_list->length; i++) {
		vector_push(sub->value_stack, object_copy(vector_pop(fr->value_stack)));
	}
	text_putindent(sub->level);
	//text_printfln("[ %s#%s ]", type_name(parent->parent), parent->name);
	//enviroment_op_dump(self->env, sub->level);
	//opcode_buf_dump(self->env->buf, sub->level);
	vm_execute(sub, self->env);
	//戻り値が Void 以外ならスタックトップの値を引き継ぐ
	if(self->return_gtype != TYPE_VOID->generic_self) {
		object* o = (object*)vector_pop(sub->value_stack);
		vector_push(fr->value_stack, o);
	}
	frame_delete(sub);
}

void operator_overload_delete(operator_overload* self) {
	enviroment_delete(self->env);
	vector_delete(self->parameter_list, operator_overload_delete_param);
	MEM_FREE(self);
}
//private
static void operator_overload_delete_param(vector_item item) {
	parameter* e = (parameter*)item;
	parameter_delete(e);
}
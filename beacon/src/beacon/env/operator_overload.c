#include "operator_overload.h"
#include "../util/mem.h"
#include "../vm/enviroment.h"
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
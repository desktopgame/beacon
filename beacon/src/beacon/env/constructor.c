#include "constructor.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../vm/enviroment.h"
#include "../vm/vm.h"
#include "../vm/frame.h"
#include "parameter.h"
#include "type_interface.h"
#include "object.h"
#include "generic_type.h"

//proto
static void constructor_parameter_delete(VectorItem item);

constructor * constructor_new() {
	constructor* ret = (constructor*)MEM_MALLOC(sizeof(constructor));
	ret->parent = NULL;
	ret->env = NULL;
	ret->parameter_list = NewVector();
	ret->access = access_public_T;
	return ret;
}

object * constructor_new_instance(constructor * self, Vector * args, frame * parent) {
	frame* sub = frame_sub(parent);
	for (int i = 0; i < args->length; i++) {
		PushVector(sub->value_stack, AtVector(args, i));
	}
	vm_execute(sub, self->env);
	object* ret = PopVector(sub->value_stack);
	frame_delete(sub);
	return ret;
}

void constructor_delete(constructor * self) {
	enviroment_delete(self->env);
	DeleteVector(self->parameter_list, constructor_parameter_delete);
	MEM_FREE(self);
}

//private
static void constructor_parameter_delete(VectorItem item) {
	parameter* e = (parameter*)item;
	parameter_delete(e);
}
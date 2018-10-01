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
static void constructor_DeleteParameter(VectorItem item);

constructor * NewConstructor() {
	constructor* ret = (constructor*)MEM_MALLOC(sizeof(constructor));
	ret->parent = NULL;
	ret->env = NULL;
	ret->parameter_list = NewVector();
	ret->access = ACCESS_PUBLIC_T;
	return ret;
}

object * NewInstanceConstructor(constructor * self, Vector * args, frame * parent) {
	frame* sub = SubFrame(parent);
	for (int i = 0; i < args->length; i++) {
		PushVector(sub->value_stack, AtVector(args, i));
	}
	ExecuteVM(sub, self->env);
	object* ret = PopVector(sub->value_stack);
	DeleteFrame(sub);
	return ret;
}

void DeleteConstructor(constructor * self) {
	DeleteEnviroment(self->env);
	DeleteVector(self->parameter_list, constructor_DeleteParameter);
	MEM_FREE(self);
}

//private
static void constructor_DeleteParameter(VectorItem item) {
	parameter* e = (parameter*)item;
	DeleteParameter(e);
}
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
static void delete_parameter(VectorItem item);

bc_Constructor * bc_NewConstructor() {
	bc_Constructor* ret = (bc_Constructor*)MEM_MALLOC(sizeof(bc_Constructor));
	ret->Parent = NULL;
	ret->Env = NULL;
	ret->Parameters = NewVector();
	ret->Access = ACCESS_PUBLIC_T;
	return ret;
}

bc_Object * bc_NewInstanceConstructor(bc_Constructor * self, Vector * args, Frame* parent) {
	Frame* sub = SubFrame(parent);
	for (int i = 0; i < args->Length; i++) {
		PushVector(sub->ValueStack, AtVector(args, i));
	}
	ExecuteVM(sub, self->Env);
	bc_Object* ret = PopVector(sub->ValueStack);
	DeleteFrame(sub);
	return ret;
}

void bc_DeleteConstructor(bc_Constructor * self) {
	DeleteEnviroment(self->Env);
	DeleteVector(self->Parameters, delete_parameter);
	MEM_FREE(self);
}

//private
static void delete_parameter(VectorItem item) {
	bc_Parameter* e = (bc_Parameter*)item;
	bc_DeleteParameter(e);
}
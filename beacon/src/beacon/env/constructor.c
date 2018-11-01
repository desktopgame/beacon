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

Constructor * NewConstructor() {
	Constructor* ret = (Constructor*)MEM_MALLOC(sizeof(Constructor));
	ret->Parent = NULL;
	ret->Env = NULL;
	ret->Parameters = NewVector();
	ret->Access = ACCESS_PUBLIC_T;
	return ret;
}

Object * NewInstanceConstructor(Constructor * self, Vector * args, Frame* parent) {
	Frame* sub = SubFrame(parent);
	for (int i = 0; i < args->Length; i++) {
		PushVector(sub->ValueStack, AtVector(args, i));
	}
	ExecuteVM(sub, self->Env);
	Object* ret = PopVector(sub->ValueStack);
	DeleteFrame(sub);
	return ret;
}

void DeleteConstructor(Constructor * self) {
	DeleteEnviroment(self->Env);
	DeleteVector(self->Parameters, delete_parameter);
	MEM_FREE(self);
}

//private
static void delete_parameter(VectorItem item) {
	Parameter* e = (Parameter*)item;
	DeleteParameter(e);
}
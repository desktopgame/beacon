#include "operator_vt.h"
#include "../util/mem.h"
#include "../env/TYPE_IMPL.h"
#include "../env/operator_overload.h"
#include "../env/parameter.h"
#include "../env/generic_type.h"

operator_vt* NewOperatorVt() {
	operator_vt* ret = (operator_vt*)MEM_MALLOC(sizeof(operator_vt));
	ret->vec = NewVector();
	return ret;
}

void ReplaceOperatorVt(operator_vt* self, operator_overload* opov) {
	for(int i=0; i<self->vec->length; i++) {
		operator_overload* e = AtVector(self->vec, i);
		if(e->type != opov->type) {
			continue;
		}
		if(operator_arg1(e->type)) {
			AssignVector(self->vec, i, opov);
			return;
		} else if(operator_arg2(e->type)) {
			parameter* param_a = AtVector(e->parameter_list, 0);
			parameter* param_b = AtVector(opov->parameter_list, 0);
			if(DistanceGenericType(param_a->gtype, param_b->gtype, NULL) == 0) {
				AssignVector(self->vec, i, opov);
				return;
			}
		} else {
			assert(false);
		}
	}
	PushVector(self->vec, opov);
}

void DeleteOperatorVt(operator_vt* self) {
	if(self == NULL) {
		return;
	}
	DeleteVector(self->vec, VectorDeleterOfNull);
	MEM_FREE(self);
}
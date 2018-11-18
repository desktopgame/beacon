#include "operator_vt.h"
#include "../util/mem.h"
#include "../env/TYPE_IMPL.h"
#include "../env/operator_overload.h"
#include "../env/parameter.h"
#include "../env/generic_type.h"

OperatorVT* NewOperatorVt() {
	OperatorVT* ret = (OperatorVT*)MEM_MALLOC(sizeof(OperatorVT));
	ret->Operators = NewVector();
	return ret;
}

void ReplaceOperatorVt(OperatorVT* self, OperatorOverload* opov) {
	for(int i=0; i<self->Operators->Length; i++) {
		OperatorOverload* e = AtVector(self->Operators, i);
		if(e->Type != opov->Type) {
			continue;
		}
		if(bc_Is1ArgOperator(e->Type)) {
			AssignVector(self->Operators, i, opov);
			return;
		} else if(bc_Is2ArgOperator(e->Type)) {
			Parameter* param_a = AtVector(e->Parameters, 0);
			Parameter* param_b = AtVector(opov->Parameters, 0);
			if(DistanceGenericType(param_a->GType, param_b->GType, NULL) == 0) {
				AssignVector(self->Operators, i, opov);
				return;
			}
		} else {
			assert(false);
		}
	}
	PushVector(self->Operators, opov);
}

void DeleteOperatorVt(OperatorVT* self) {
	if(self == NULL) {
		return;
	}
	DeleteVector(self->Operators, VectorDeleterOfNull);
	MEM_FREE(self);
}
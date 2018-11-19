#include "operator_vt.h"
#include "../util/mem.h"
#include "../env/TYPE_IMPL.h"
#include "../env/operator_overload.h"
#include "../env/parameter.h"
#include "../env/generic_type.h"

bc_OperatorVT* bc_NewOperatorVt() {
	bc_OperatorVT* ret = (bc_OperatorVT*)MEM_MALLOC(sizeof(bc_OperatorVT));
	ret->Operators = NewVector();
	return ret;
}

void bc_ReplaceOperatorVt(bc_OperatorVT* self, bc_OperatorOverload* opov) {
	for(int i=0; i<self->Operators->Length; i++) {
		bc_OperatorOverload* e = AtVector(self->Operators, i);
		if(e->Type != opov->Type) {
			continue;
		}
		if(bc_Is1ArgOperator(e->Type)) {
			AssignVector(self->Operators, i, opov);
			return;
		} else if(bc_Is2ArgOperator(e->Type)) {
			bc_Parameter* param_a = AtVector(e->Parameters, 0);
			bc_Parameter* param_b = AtVector(opov->Parameters, 0);
			if(bc_DistanceGenericType(param_a->GType, param_b->GType, NULL) == 0) {
				AssignVector(self->Operators, i, opov);
				return;
			}
		} else {
			assert(false);
		}
	}
	PushVector(self->Operators, opov);
}

void bc_DeleteOperatorVt(bc_OperatorVT* self) {
	if(self == NULL) {
		return;
	}
	DeleteVector(self->Operators, VectorDeleterOfNull);
	MEM_FREE(self);
}
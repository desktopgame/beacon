#include "operator_vt.h"
#include "../util/mem.h"
#include "../env/TYPE_IMPL.h"
#include "../env/operator_overload.h"
#include "../env/parameter.h"
#include "../env/generic_type.h"

bc_OperatorVT* bc_NewOperatorVt() {
	bc_OperatorVT* ret = (bc_OperatorVT*)MEM_MALLOC(sizeof(bc_OperatorVT));
	ret->Operators = bc_NewVector();
	return ret;
}

void bc_ReplaceOperatorVt(bc_OperatorVT* self, bc_OperatorOverload* opov) {
	for(int i=0; i<self->Operators->Length; i++) {
		bc_OperatorOverload* e = bc_AtVector(self->Operators, i);
		if(e->Type != opov->Type) {
			continue;
		}
		if(bc_Is1ArgOperator(e->Type)) {
			bc_AssignVector(self->Operators, i, opov);
			return;
		} else if(bc_Is2ArgOperator(e->Type)) {
			bc_Parameter* param_a = bc_AtVector(e->Parameters, 0);
			bc_Parameter* param_b = bc_AtVector(opov->Parameters, 0);
			if(bc_DistanceGenericType(param_a->GType, param_b->GType, NULL) == 0) {
				bc_AssignVector(self->Operators, i, opov);
				return;
			}
		} else {
			assert(false);
		}
	}
	bc_PushVector(self->Operators, opov);
}

void bc_DeleteOperatorVt(bc_OperatorVT* self) {
	if(self == NULL) {
		return;
	}
	bc_DeleteVector(self->Operators, bc_VectorDeleterOfNull);
	MEM_FREE(self);
}
#include "operator_vt.h"
#include "../util/mem.h"
#include "../env/type_impl.h"
#include "../env/operator_overload.h"
#include "../env/parameter.h"
#include "../env/generic_type.h"

operator_vt* operator_vt_new() {
	operator_vt* ret = (operator_vt*)MEM_MALLOC(sizeof(operator_vt));
	ret->vec = vector_new();
	return ret;
}

void operator_vt_replace(operator_vt* self, operator_overload* opov) {
	for(int i=0; i<self->vec->length; i++) {
		operator_overload* e = vector_at(self->vec, i);
		if(e->type != opov->type) {
			continue;
		}
		if(operator_arg1(e->type)) {
			vector_assign(self->vec, i, opov);
			return;
		} else if(operator_arg2(e->type)) {
			parameter* param_a = vector_at(e->parameter_list, 0);
			parameter* param_b = vector_at(opov->parameter_list, 0);
			if(generic_type_distance(param_a->gtype, param_b->gtype, NULL) == 0) {
				vector_assign(self->vec, i, opov);
				return;
			}
		} else {
			assert(false);
		}
	}
	vector_push(self->vec, opov);
}

void operator_vt_delete(operator_vt* self) {
	if(self == NULL) {
		return;
	}
	vector_delete(self->vec, vector_deleter_null);
	MEM_FREE(self);
}
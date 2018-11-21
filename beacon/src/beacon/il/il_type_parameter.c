#include "il_type_parameter.h"
#include "../util/mem.h"
#include "../util/text.h"

//proto
static void ILTypeParameter_rule_list_delete(bc_VectorItem item);

bc_ILTypeParameter * bc_NewILTypeParameter(bc_StringView name) {
	bc_ILTypeParameter* ret = (bc_ILTypeParameter*)MEM_MALLOC(sizeof(bc_ILTypeParameter));
	ret->Tag = IL_TYPE_PARAMETER_KIND_DEFAULT_T;
	ret->Name = name;
	return ret;
}

void bc_PrintILTypeParameterList(bc_Vector * v) {
	if (v->Length <= 0) {
		return;
	}
	printf("<");
	for (int i = 0; i < v->Length; i++) {
		bc_ILTypeParameter* e = (bc_ILTypeParameter*)bc_AtVector(v, i);
		if (e->Tag == IL_TYPE_PARAMETER_KIND_IN_T) {
			printf("in ");
		} else if (e->Tag == IL_TYPE_PARAMETER_KIND_OUT_T) {
			printf("out ");
		}
		printf("%s", bc_Ref2Str(e->Name));
		if (i != v->Length - 1) {
			printf(", ");
		}
	}
	printf(">");
}

void bc_DeleteILTypeParameter(bc_ILTypeParameter * self) {
	MEM_FREE(self);
}
//private
static void ILTypeParameter_rule_list_delete(bc_VectorItem item) {
}
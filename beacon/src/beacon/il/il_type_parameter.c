#include "il_type_parameter.h"
#include "../util/mem.h"
#include "../util/text.h"

//proto
static void ILTypeParameter_rule_list_delete(VectorItem item);

ILTypeParameter * NewILTypeParameter(StringView namev) {
	ILTypeParameter* ret = (ILTypeParameter*)MEM_MALLOC(sizeof(ILTypeParameter));
	ret->kind = IL_TYPE_PARAMETER_KIND_DEFAULT_T;
	ret->namev = namev;
	return ret;
}

void PrintILTypeParameterList(Vector * v) {
	if (v->Length <= 0) {
		return;
	}
	printf("<");
	for (int i = 0; i < v->Length; i++) {
		ILTypeParameter* e = (ILTypeParameter*)AtVector(v, i);
		if (e->kind == IL_TYPE_PARAMETER_KIND_IN_T) {
			printf("in ");
		} else if (e->kind == IL_TYPE_PARAMETER_KIND_OUT_T) {
			printf("out ");
		}
		printf("%s", Ref2Str(e->namev));
		if (i != v->Length - 1) {
			printf(", ");
		}
	}
	printf(">");
}

void DeleteILTypeParameter(ILTypeParameter * self) {
	MEM_FREE(self);
}
//private
static void ILTypeParameter_rule_list_delete(VectorItem item) {
}
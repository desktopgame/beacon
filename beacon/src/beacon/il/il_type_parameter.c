#include "il_type_parameter.h"
#include "../util/mem.h"
#include "../util/text.h"

//proto
static void il_type_parameter_rule_list_delete(VectorItem item);

il_type_parameter * NewILTypeParameter(StringView namev) {
	il_type_parameter* ret = (il_type_parameter*)MEM_MALLOC(sizeof(il_type_parameter));
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
		il_type_parameter* e = (il_type_parameter*)AtVector(v, i);
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

void DeleteILTypeParameter(il_type_parameter * self) {
	MEM_FREE(self);
}
//private
static void il_type_parameter_rule_list_delete(VectorItem item) {
}
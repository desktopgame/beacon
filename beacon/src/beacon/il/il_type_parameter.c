#include "il_type_parameter.h"
#include "../util/mem.h"
#include "../util/text.h"

//proto
static void ILTypeParameter_rule_list_delete(VectorItem item);

ILTypeParameter * NewILTypeParameter(StringView name) {
	ILTypeParameter* ret = (ILTypeParameter*)MEM_MALLOC(sizeof(ILTypeParameter));
	ret->Tag = IL_TYPE_PARAMETER_KIND_DEFAULT_T;
	ret->Name = name;
	return ret;
}

void PrintILTypeParameterList(Vector * v) {
	if (v->Length <= 0) {
		return;
	}
	printf("<");
	for (int i = 0; i < v->Length; i++) {
		ILTypeParameter* e = (ILTypeParameter*)AtVector(v, i);
		if (e->Tag == IL_TYPE_PARAMETER_KIND_IN_T) {
			printf("in ");
		} else if (e->Tag == IL_TYPE_PARAMETER_KIND_OUT_T) {
			printf("out ");
		}
		printf("%s", Ref2Str(e->Name));
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
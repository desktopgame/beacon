#include "type_parameter.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../util/vector.h"
#include "../il/il_type_parameter.h"
#include <assert.h>

//proto
static void TypeParameter_rule_list_delete(VectorItem item);

TypeParameter * NewTypeParameter(StringView namev) {
	TypeParameter* ret = (TypeParameter*)MEM_MALLOC(sizeof(TypeParameter));
	ret->Name = namev;
	ret->Kind = TYPE_PARAMETER_KIND_DEFAULT_T;
	return ret;
}

TypeParameter * DupTypeParameter(il_type_parameter * src) {
	TypeParameter* ret = NewTypeParameter(src->namev);
	switch (src->kind) {
		case IL_TYPE_PARAMETER_KIND_DEFAULT_T:
			ret->Kind = TYPE_PARAMETER_KIND_DEFAULT_T;
			break;
		case IL_TYPE_PARAMETER_KIND_IN_T:
			ret->Kind = TYPE_PARAMETER_KIND_IN_T;
			break;
		case IL_TYPE_PARAMETER_KIND_OUT_T:
			ret->Kind = TYPE_PARAMETER_KIND_OUT_T;
			break;
		default:
			break;
	}
//	TypeParameter_rule_list_dup(src->rule_vec, ret->rule_vec, cache);
	return ret;
}

void DupTypeParameterList(Vector* ilSource, Vector* sgDest) {
	assert(ilSource != NULL);
	//これはILレベルの<K, V>の並びを
	//SGレベルの<K, V> へ変換します。
	//<K(IComparable<K>), V>のような宣言をするとき、
	//Kは仮想型としてIComparableで正しく認識されます。
	//そのためには、TypeParameterをとりえず登録しておいて、
	//あとからルール一覧を対応づける必要があります。
	//DupTypeParameterからルールの複製を削除したのもそのためです。
	for (int i = 0; i < ilSource->Length; i++) {
		il_type_parameter* e = (il_type_parameter*)AtVector(ilSource, i);
		TypeParameter* newTP = DupTypeParameter(e);
		PushVector(sgDest, newTP);
		//TypeParameter_rule_list_dup(e->rule_vec, newTP->rule_vec, cache);
	}
}

void PrintTypeParameter(Vector* v) {
	//FIXME:il_TypeParameterからのコピペ
	if (v->Length <= 0) {
		return;
	}
	printf("<");
	for (int i = 0; i < v->Length; i++) {
		TypeParameter* e = (TypeParameter*)AtVector(v, i);
		if (e->Kind == TYPE_PARAMETER_KIND_IN_T) {
			printf("in ");
		} else if (e->Kind == TYPE_PARAMETER_KIND_OUT_T) {
			printf("out ");
		}
		printf("%s", Ref2Str(e->Name));
		if (i != v->Length - 1) {
			printf(", ");
		}
	}
	printf(">");
}

void DeleteTypeParameter(TypeParameter * self) {
	MEM_FREE(self);
}

bool IsOverwrappedTypeParameterName(Vector* tparameters, StringView* namev) {
	if(tparameters->Length <= 1) {
		return false;
	}
	for(int i=0; i<tparameters->Length; i++) {
		TypeParameter* e = (TypeParameter*)AtVector(tparameters, i);
		for(int j=0; j<tparameters->Length; j++) {
			if(i == j) { continue; }
			TypeParameter* e2 = (TypeParameter*)AtVector(tparameters, j);
			if(e->Name == e2->Name) {
				(*namev) = e->Name;
				return true;
			}
		}
	}
	return false;
}

//private
static void TypeParameter_rule_list_delete(VectorItem item) {
//	TypeParameter_rule* e = (TypeParameter_rule*)item;
//	TypeParameter_rule_delete(e);
}


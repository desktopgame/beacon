#include "type_parameter.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../util/vector.h"
#include "../il/il_type_parameter.h"
#include <assert.h>

//proto
static void type_parameter_rule_list_delete(VectorItem item);

type_parameter * NewTypeParameter(StringView namev) {
	type_parameter* ret = (type_parameter*)MEM_MALLOC(sizeof(type_parameter));
	ret->namev = namev;
	ret->kind = TYPE_PARAMETER_KIND_DEFAULT_T;
	return ret;
}

type_parameter * DupTypeParameter(il_type_parameter * src) {
	type_parameter* ret = NewTypeParameter(src->namev);
	switch (src->kind) {
		case il_TYPE_PARAMETER_KIND_DEFAULT_T:
			ret->kind = TYPE_PARAMETER_KIND_DEFAULT_T;
			break;
		case il_TYPE_PARAMETER_KIND_IN_T:
			ret->kind = TYPE_PARAMETER_KIND_IN_T;
			break;
		case il_TYPE_PARAMETER_KIND_OUT_T:
			ret->kind = TYPE_PARAMETER_KIND_OUT_T;
			break;
		default:
			break;
	}
//	type_parameter_rule_list_dup(src->rule_vec, ret->rule_vec, cache);
	return ret;
}

void DupTypeParameterList(Vector* ilSource, Vector* sgDest) {
	assert(ilSource != NULL);
	//これはILレベルの<K, V>の並びを
	//SGレベルの<K, V> へ変換します。
	//<K(IComparable<K>), V>のような宣言をするとき、
	//Kは仮想型としてIComparableで正しく認識されます。
	//そのためには、type_parameterをとりえず登録しておいて、
	//あとからルール一覧を対応づける必要があります。
	//DupTypeParameterからルールの複製を削除したのもそのためです。
	for (int i = 0; i < ilSource->Length; i++) {
		il_type_parameter* e = (il_type_parameter*)AtVector(ilSource, i);
		type_parameter* newTP = DupTypeParameter(e);
		PushVector(sgDest, newTP);
		//type_parameter_rule_list_dup(e->rule_vec, newTP->rule_vec, cache);
	}
}

void PrintTypeParameter(Vector* v) {
	//FIXME:il_type_parameterからのコピペ
	if (v->Length <= 0) {
		return;
	}
	printf("<");
	for (int i = 0; i < v->Length; i++) {
		type_parameter* e = (type_parameter*)AtVector(v, i);
		if (e->kind == TYPE_PARAMETER_KIND_IN_T) {
			printf("in ");
		} else if (e->kind == TYPE_PARAMETER_KIND_OUT_T) {
			printf("out ");
		}
		printf("%s", Ref2Str(e->namev));
		if (i != v->Length - 1) {
			printf(", ");
		}
	}
	printf(">");
}

void DeleteTypeParameter(type_parameter * self) {
	MEM_FREE(self);
}

bool IsOverwrappedTypeParameterName(Vector* tparameters, StringView* namev) {
	if(tparameters->Length <= 1) {
		return false;
	}
	for(int i=0; i<tparameters->Length; i++) {
		type_parameter* e = (type_parameter*)AtVector(tparameters, i);
		for(int j=0; j<tparameters->Length; j++) {
			if(i == j) { continue; }
			type_parameter* e2 = (type_parameter*)AtVector(tparameters, j);
			if(e->namev == e2->namev) {
				(*namev) = e->namev;
				return true;
			}
		}
	}
	return false;
}

//private
static void type_parameter_rule_list_delete(VectorItem item) {
//	type_parameter_rule* e = (type_parameter_rule*)item;
//	type_parameter_rule_delete(e);
}


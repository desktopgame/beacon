#include "type_parameter.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../util/vector.h"
#include "../il/il_type_parameter.h"
#include <assert.h>

//proto
static void type_parameter_rule_list_delete(vector_item item);

type_parameter * type_parameter_new(string_view namev) {
	type_parameter* ret = (type_parameter*)MEM_MALLOC(sizeof(type_parameter));
	ret->namev = namev;
	ret->kind = type_parameter_kind_default;
	return ret;
}

type_parameter * type_parameter_dup(il_type_parameter * src) {
	type_parameter* ret = type_parameter_new(src->namev);
	switch (src->kind) {
		case il_type_parameter_kind_default:
			ret->kind = type_parameter_kind_default;
			break;
		case il_type_parameter_kind_in:
			ret->kind = type_parameter_kind_in;
			break;
		case il_type_parameter_kind_out:
			ret->kind = type_parameter_kind_out;
			break;
		default:
			break;
	}
//	type_parameter_rule_list_dup(src->rule_vec, ret->rule_vec, cache);
	return ret;
}

void type_parameter_list_dup(vector* ilSource, vector* sgDest) {
	assert(ilSource != NULL);
	//これはILレベルの<K, V>の並びを
	//SGレベルの<K, V> へ変換します。
	//<K(IComparable<K>), V>のような宣言をするとき、
	//Kは仮想型としてIComparableで正しく認識されます。
	//そのためには、type_parameterをとりえず登録しておいて、
	//あとからルール一覧を対応づける必要があります。
	//type_parameter_dupからルールの複製を削除したのもそのためです。
	for (int i = 0; i < ilSource->length; i++) {
		il_type_parameter* e = (il_type_parameter*)vector_at(ilSource, i);
		type_parameter* newTP = type_parameter_dup(e);
		vector_push(sgDest, newTP);
		//type_parameter_rule_list_dup(e->rule_vec, newTP->rule_vec, cache);
	}
}

void type_parameter_print(vector* v) {
	//FIXME:il_type_parameterからのコピペ
	if (v->length <= 0) {
		return;
	}
	text_printf("<");
	for (int i = 0; i < v->length; i++) {
		type_parameter* e = (type_parameter*)vector_at(v, i);
		if (e->kind == type_parameter_kind_in) {
			text_printf("in ");
		} else if (e->kind == type_parameter_kind_out) {
			text_printf("out ");
		}
		text_printf("%s", string_pool_ref2str(e->namev));
		if (i != v->length - 1) {
			text_printf(", ");
		}
	}
	text_printf(">");
}

void type_parameter_delete(type_parameter * self) {
	MEM_FREE(self);
}
//private
static void type_parameter_rule_list_delete(vector_item item) {
//	type_parameter_rule* e = (type_parameter_rule*)item;
//	type_parameter_rule_delete(e);
}


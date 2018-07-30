#include "meta_impl.h"
#include "../../il/il_argument.h"
#include "../../il/il_argument.h"
#include "../../il/il_error.h"
#include "../parameter.h"
#include "../type_parameter.h"
#include "../type_interface.h"
#include "../namespace.h"
#include "class_impl.h"
#include "../constructor.h"
#include "../object.h"
#include "../method.h"
#include "../../util/text.h"
#include <string.h>

int meta_ilcalc_score(vector* params, vector* ilargs, enviroment* env, call_context* cctx) {
	assert(params->length == ilargs->length);
	int score = 0;
	bool illegal = false;
	//assert(ilctx->type_args_vec->length != 0);
	//vector* type_args = vector_top(ilctx->type_args_vec);
	for (int i = 0; i < params->length; i++) {
		vector_item varg = vector_at(ilargs, i);
		vector_item vparam = vector_at(params, i);
		il_argument* arg = (il_argument*)varg;
		parameter* param = (parameter*)vparam;
		//実引数が NULL なら常に許容する
		int dist = 0;
		generic_type* argType = il_factor_eval(arg->factor, env, cctx);
		if(il_error_panic()) {
			return -1;
		}
		if(param->gtype->core_type != NULL) {
			text_printf(": %s\n", string_pool_ref2str(type_name(param->gtype->core_type)));
		}
		if(generic_type_compare(param->gtype, "GenericA")) {
			int a = 0;
		}
		if (argType->core_type != TYPE_NULL) {
			generic_type* a = generic_type_apply(param->gtype, cctx);
			//generic_type_print2(param->gtype, a);
			dist = generic_type_distance(
				a,
			//	generic_type_apply(argType, ilctx),
			//	param->gtype,
				argType
			//	ilctx
			);
		}
		score += dist;
		//継承関係のないパラメータ
		if (dist == -1) {
			illegal = true;
			return -1;
		}
	}
	return score;
}

int meta_gcalc_score(vector* params, vector* gargs) {
	assert(params->length == gargs->length);
	//meta_ilcalc_scoreからのコピペ
	int score = 0;
	bool illegal = false;
	//assert(ilctx->type_args_vec->length != 0);
	//vector* type_args = vector_top(ilctx->type_args_vec);
	for (int i = 0; i < params->length; i++) {
		vector_item varg = vector_at(gargs, i);
		vector_item vparam = vector_at(params, i);
		//il_argument* arg = (il_argument*)varg;
		parameter* param = (parameter*)vparam;
		//実引数が NULL なら常に許容する
		int dist = 0;
		generic_type* argType = (generic_type*)varg;
		if(il_error_panic()) {
			return -1;
		}
		if (argType->core_type != TYPE_NULL) {
			generic_type* a = generic_type_apply(param->gtype, NULL);
			dist = generic_type_distance(
				a,
			//	generic_type_apply(argType, ilctx),
			//	param->gtype,
				argType
			//	ilctx
			);
		}
		score += dist;
		//継承関係のないパラメータ
		if (dist == -1) {
			illegal = true;
			return -1;
		}
	}
	return score;
}

int meta_rcalc_score(vector* params, vector* args, vector* typeargs, frame* fr) {
	assert(params->length == args->length);
	int score = 0;
	bool illegal = false;
	for (int i = 0; i < params->length; i++) {
		vector_item varg = vector_at(args, i);
		vector_item vparam = vector_at(params, i);
		object* arg = (object*)varg;
		parameter* param = (parameter*)vparam;
		//実引数が NULL なら常に許容する
		int dist = 0;
		//generic_type* argType = il_factor_eval(arg->factor, env, ilctx);
		generic_type* argType = arg->gtype;
		if (argType->core_type != TYPE_NULL) {
			generic_type* a = generic_type_rapply(param->gtype, NULL,fr);
			dist = generic_type_rdistance(a, argType, fr);
		}
		score += dist;
		//継承関係のないパラメータ
		if (dist == -1) {
			illegal = true;
			break;
		}
	}
	return score;
}

method * meta_ilfind_method(vector * method_vec, string_view namev, vector * ilargs, enviroment * env, call_context* cctx, int * outIndex) {
	return meta_scoped_ilfind_method(NULL, method_vec, namev, ilargs, env, cctx, outIndex);
}

method* meta_gfind_method(vector* method_vec, string_view namev, vector * gargs, int* outIndex) {
	return meta_scoped_gfind_method(NULL, method_vec, namev, gargs, outIndex);
}

method* meta_scoped_ilfind_method(class_* context, vector* method_vec, string_view namev, vector * ilargs, enviroment * env, call_context* cctx, int * outIndex) {
	(*outIndex) = -1;
	//class_create_vtable(self);
	method* ret = NULL;
	int min = 1024;
	//全てのメソッドへ
	for (int i = 0; i < method_vec->length; i++) {
		vector_item ve = vector_at(method_vec, i);
		method* m = (method*)ve;
		if(!meta_access_valid(context, m)) {
			continue;
		}
		//名前か引数の個数が違うので無視
		if (m->namev != namev ||
			m->parameter_list->length != ilargs->length
			) {
			continue;
		}
		//引数がひとつもないので、
		//型のチェックを行わない
		if (ilargs->length == 0) {
			(*outIndex) = i;
			return m;
		}
		int score = meta_ilcalc_score(m->parameter_list, ilargs, env, cctx);
		if(score == -1) {
			continue;
		}
		if (score < min) {
			min = score;
			ret = m;
			(*outIndex) = i;
		}
	}
	return ret;
}

method* meta_scoped_gfind_method(class_* context, vector* method_vec, string_view namev, vector * gargs, int * outIndex) {
	(*outIndex) = -1;
	//class_create_vtable(self);
	method* ret = NULL;
	int min = 1024;
	//全てのメソッドへ
	for (int i = 0; i < method_vec->length; i++) {
		vector_item ve = vector_at(method_vec, i);
		method* m = (method*)ve;
		if(!meta_access_valid(context, m)) {
			continue;
		}
		//名前か引数の個数が違うので無視
		if (m->namev != namev ||
			m->parameter_list->length != gargs->length
			) {
			continue;
		}
		//引数がひとつもないので、
		//型のチェックを行わない
		if (gargs->length == 0) {
			(*outIndex) = i;
			return m;
		}
		int score = meta_gcalc_score(m->parameter_list, gargs);
		if(score == -1) {
			continue;
		}
		if (score < min) {
			min = score;
			ret = m;
			(*outIndex) = i;
		}
	}
	return ret;
}

constructor* meta_ilfind_ctor(vector* ctor_vec, vector* ilargs, enviroment* env, call_context* cctx, int* outIndex) {
	return meta_scoped_ilfind_ctor(NULL, ctor_vec, ilargs, env, cctx, outIndex);
}

constructor* meta_rfind_ctor(vector* ctor_vec, vector* args, vector* typeargs, frame* fr, int* outIndex) {
	return meta_scoped_rfind_ctor(NULL, ctor_vec, args, typeargs, fr, outIndex);
}

constructor* meta_scoped_ilfind_ctor(class_* context, vector* ctor_vec, vector* ilargs, enviroment* env, call_context* cctx, int* outIndex) {
	//見つかった中からもっとも一致するコンストラクタを選択する
	int min = 1024;
	constructor* ret = NULL;
	for (int i = 0; i < ctor_vec->length; i++) {
		vector_item ve = vector_at(ctor_vec, i);
		constructor* ctor = (constructor*)ve;
		if(!meta_access_validc(context, ctor)) {
			continue;
		}
		//引数の個数が違うので無視
		if (ctor->parameter_list->length != ilargs->length) {
			continue;
		}
		//引数がひとつもないので、
		//型のチェックを行わない
		if (ilargs->length == 0) {
			(*outIndex) = i;
			return ctor;
		}
		//もっともスコアの高いメソッドを選択する
		int score = meta_ilcalc_score(ctor->parameter_list, ilargs, env, cctx);
		if(score == -1) {
			continue;
		}
		if (score < min) {
			min = score;
			ret = ctor;
			(*outIndex) = i;
		}
	}
	return ret;
}

constructor* meta_scoped_rfind_ctor(class_* context, vector* ctor_vec, vector* gargs, vector* typeargs, frame* fr, int* outIndex) {
	//見つかった中からもっとも一致するコンストラクタを選択する
	int min = 1024;
	constructor* ret = NULL;
	for (int i = 0; i < ctor_vec->length; i++) {
		vector_item ve = vector_at(ctor_vec, i);
		constructor* ctor = (constructor*)ve;
		class_* cls = TYPE2CLASS(ctor->parent);
		if(!meta_access_validc(context, ctor)) {
			continue;
		}
		//引数の個数が違うので無視
		if (ctor->parameter_list->length != gargs->length) {
			continue;
		}
		int score = meta_rcalc_score(ctor->parameter_list, gargs, typeargs, fr);
		if (score < min) {
			min = score;
			ret = ctor;
			(*outIndex) = i;
		}
	}
	return ret;
}

operator_overload* meta_gfind_operator(vector* opov_vec, operator_type type, vector* gargs, int* outIndex) {
	(*outIndex) = -1;
	int min = 1024;
	operator_overload* ret = NULL;
	for(int i=0; i<opov_vec->length; i++) {
		operator_overload* opov = vector_at(opov_vec, i);
		//オペレータの種類が違うので無視
		if(opov->type != type) {
			continue;
		}
		//引数の数が違うので無視
		if(opov->parameter_list->length != gargs->length) {
			continue;
		}
		int score = meta_gcalc_score(opov->parameter_list, gargs);
		if(min == -1) {
			continue;
		}
		if(score < min) {
			min = score;
			(*outIndex) = i;
			ret = opov;
		}
	}
	return ret;
}

operator_overload* meta_gfind_operator_default_eq(vector* opov_vec, int* outIndex) {
	vector* gargs = vector_new();
	vector_push(gargs, TYPE_OBJECT->generic_self);
	operator_overload* ret = meta_gfind_operator(opov_vec, operator_eq, gargs, outIndex);
	vector_delete(gargs, vector_deleter_null);
	return ret;
}

operator_overload* meta_gfind_operator_default_noteq(vector* opov_vec, int* outIndex) {
	vector* gargs = vector_new();
	vector_push(gargs, TYPE_OBJECT->generic_self);
	operator_overload* ret = meta_gfind_operator(opov_vec, operator_noteq, gargs, outIndex);
	vector_delete(gargs, vector_deleter_null);
	return ret;
}

bool meta_access_valid(class_* context, method* m) {
/*
	//privateメソッドなのに現在のコンテキストではない
	if(context != NULL &&
		m->access == access_private &&
		TYPE2CLASS(m->parent) != context) {
		return false;
	}
	//protectedメソッドなのにそのサブクラスではない
	if(context != NULL &&
		m->access == access_protected &&
		class_distance(TYPE2CLASS(m->parent), context) < 0) {
		return false;
	}
*/
	return true;
}

bool meta_access_validc(class_* context, constructor* ctor) {
/*
	//privateメソッドなのに現在のコンテキストではない
	if(context != NULL &&
		ctor->access == access_private &&
		TYPE2CLASS(ctor->parent) != context) {
		return false;
	}
	//protectedメソッドなのにそのサブクラスではない
	if(context != NULL &&
		ctor->access == access_protected &&
		class_distance(TYPE2CLASS(ctor->parent), context) < 0) {
		return false;
	}
*/
	return true;
}
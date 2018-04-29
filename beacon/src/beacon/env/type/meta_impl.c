#include "meta_impl.h"
#include "../../il/il_argument.h"
#include "../../il/il_argument.h"
#include "../../il/il_error.h"
#include "../parameter.h"
#include "../type_interface.h"
#include "../namespace.h"
#include "class_impl.h"
#include "../constructor.h"
#include "../object.h"
#include "../method.h"
#include "../../util/xassert.h"
#include "../../debug.h"
#include <string.h>

int meta_calc_score(vector* params, vector* ilargs, enviroment* env, il_context* ilctx) {
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
		generic_type* argType = il_factor_eval(arg->factor, env, ilctx);
		//virtual_type parvType = param->vtype;
		//parvType.gtype
		//のタグが　none
		//インデックスが-1
		if(il_error_panic()) {
			return -1;
		}
		if (argType->core_type != CL_NULL) {
			dist = generic_type_distance(param->gtype, argType, ilctx);
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

int meta_rcalc_score(vector* params, vector* args) {
	assert(params->length == args->length);
	il_context* ilctx = il_context_new();
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
		if (argType->core_type != CL_NULL) {
			dist = generic_type_distance(param->gtype, argType, ilctx);
		}
		score += dist;
		//継承関係のないパラメータ
		if (dist == -1) {
			illegal = true;
			break;
		}
	}
	il_context_delete(ilctx);
	return score;
}

method * meta_find_method(vector * method_vec, const char * name, vector * ilargs, enviroment * env, il_context* ilctx, int * outIndex) {
	(*outIndex) = -1;
	//class_create_vtable(self);
	method* ret = NULL;
	int min = 1024;
	//全てのメソッドへ
	for (int i = 0; i < method_vec->length; i++) {
		vector_item ve = vector_at(method_vec, i);
		method* m = (method*)ve;
		//名前か引数の個数が違うので無視
		if (strcmp(m->name, name) ||
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
		//XBREAK(!strcmp(m->name, "copy") && debug_get_gen_top());
		//XSTREQ(m->name, "copy");
		//XSTREQ(m->name, "nativeCopy");
		//もっともスコアの高いメソッドを選択する
		vector_push(ilctx->method_vec, m);
		int score = meta_calc_score(m->parameter_list, ilargs, env, ilctx);
		vector_pop(ilctx->method_vec);
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

constructor* meta_find_ctor(vector* ctor_vec, vector* ilargs, struct enviroment* env, il_context* ilctx, int* outIndex) {
	//見つかった中からもっとも一致するコンストラクタを選択する
	int min = 1024;
	constructor* ret = NULL;
	for (int i = 0; i < ctor_vec->length; i++) {
		vector_item ve = vector_at(ctor_vec, i);
		constructor* ctor = (constructor*)ve;
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
		vector_push(ilctx->eval_ctor_vec, ctor);
		int score = meta_calc_score(ctor->parameter_list, ilargs, env, ilctx);
		vector_pop(ilctx->eval_ctor_vec);
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

constructor* meta_find_rctor(vector* ctor_vec, vector* args, int* outIndex) {
	//見つかった中からもっとも一致するコンストラクタを選択する
	int min = 1024;
	constructor* ret = NULL;
	for (int i = 0; i < ctor_vec->length; i++) {
		vector_item ve = vector_at(ctor_vec, i);
		constructor* ctor = (constructor*)ve;
		int score = meta_rcalc_score(ctor->parameter_list, args);
		if (score < min) {
			min = score;
			ret = ctor;
			(*outIndex) = i;
		}
	}
	return ret;
}
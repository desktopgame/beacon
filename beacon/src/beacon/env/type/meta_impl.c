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
#include "../../util/xassert.h"
#include "../../util/text.h"
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
		if(il_error_panic()) {
			return -1;
		}
		if (argType->core_type != CL_NULL) {
			generic_type* a = generic_type_apply(param->gtype, ilctx);
			dist = generic_type_distance(
				a,
			//	generic_type_apply(argType, ilctx),
			//	param->gtype,
				argType,
				ilctx
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

int meta_rcalc_score(vector* params, vector* args) {
	assert(params->length == args->length);
	il_context* ilctx = il_context_new(NULL);
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
		//与えられた型引数の妥当性を検証する
		if(!meta_rule_valid(m->type_parameter_list, ILCTX_TYPE_ARGS(ilctx), ilctx)) {
			continue;
		}
		//引数がひとつもないので、
		//型のチェックを行わない
		if (ilargs->length == 0) {
			(*outIndex) = i;
			return m;
		}
		//もっともスコアの高いメソッドを選択する
		if(modifier_is_static(m->modifier)) {
			ilctx->find_static++;
			vector_push(ilctx->method_vec, m);
		} else {
			ilctx->find_instance++;
		}
		int score = meta_calc_score(m->parameter_list, ilargs, env, ilctx);
		
		if(modifier_is_static(m->modifier)) {
			ilctx->find_static--;
		vector_pop(ilctx->method_vec);
		} else {
			ilctx->find_instance--;
		}
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
		//与えられた型引数の妥当性を検証する
		if(ilctx != NULL && !meta_rule_valid(ctor->parent->u.class_->type_parameter_list, ILCTX_TYPE_ARGS(ilctx), ilctx)) {
			continue;
		}
		//引数がひとつもないので、
		//型のチェックを行わない
		if (ilargs->length == 0) {
			(*outIndex) = i;
			return ctor;
		}
		//もっともスコアの高いメソッドを選択する
		ilctx->find_static++;
		ILCTX_PUSH_CTOR(ilctx, ctor);
		int score = meta_calc_score(ctor->parameter_list, ilargs, env, ilctx);
		ILCTX_POP_CTOR(ilctx);
		ilctx->find_static--;
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

bool meta_rule_valid(vector* type_params, vector* type_args, il_context* ilctx) {
	assert(type_params->length == type_args->length);
	//全ての型引数に
	bool valid = true;
	for(int i=0; i<type_args->length; i++) {
		type_parameter* par = (type_parameter*)vector_at(type_params, i);
		generic_type* arg = (generic_type*)vector_at(type_args, i);
		//ルールを検証
		bool validr = true;
		for(int j=0; j<par->rule_vec->length; j++) {
			type_parameter_rule* rule = vector_at(par->rule_vec, j);
			if(rule->tag == type_parameter_rule_tag_neweable) {
				assert(false);
			} else if(rule->tag == type_parameter_rule_tag_polymorphic) {
				generic_type* base = rule->u.gtype_;
				if(generic_type_distance(base, arg, ilctx) == -1) {
					validr = false;
					break;
				}
			}
		}
		if(!validr) {
			valid = false;
			break;
		}
	}
	return valid;
}
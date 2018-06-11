#include "meta_impl.h"
#include "../../il/il_argument.h"
#include "../../il/il_argument.h"
#include "../../il/il_error.h"
#include "../parameter.h"
#include "../type_parameter.h"
#include "../type_interface.h"
#include "../compile_context.h"
#include "../namespace.h"
#include "class_impl.h"
#include "../constructor.h"
#include "../object.h"
#include "../method.h"
#include "../../util/xassert.h"
#include "../../util/text.h"
#include <string.h>

int meta_ilcalc_score(vector* params, vector* ilargs, enviroment* env) {
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
		generic_type* argType = il_factor_eval(arg->factor, env);
		if(il_error_panic()) {
			return -1;
		}
		if (argType->core_type != TYPE_NULL) {
			generic_type* a = generic_type_apply(param->gtype);
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
			generic_type* a = generic_type_apply(param->gtype);
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
			generic_type* a = generic_type_rapply(param->gtype, fr);
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

method * meta_ilfind_method(vector * method_vec, const char * name, vector * ilargs, enviroment * env, int * outIndex) {
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
		//もっともスコアの高いメソッドを選択する
		if(modifier_is_static(m->modifier)) {
			ccpush_method(m);
		}
		int score = meta_ilcalc_score(m->parameter_list, ilargs, env);
		
		if(modifier_is_static(m->modifier)) {
			ccpop_method();
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

method* meta_gfind_method(vector* method_vec, const char * name, vector * gargs, int* outIndex) {
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
		//もっともスコアの高いメソッドを選択する
		if(modifier_is_static(m->modifier)) {
			ccpush_method(m);
		}
		int score = meta_gcalc_score(m->parameter_list, gargs);
		if(modifier_is_static(m->modifier)) {
			ccpop_method();
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

constructor* meta_ilfind_ctor(vector* ctor_vec, vector* ilargs, struct enviroment* env, int* outIndex) {
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
		ccpush_ctor(ctor);
		int score = meta_ilcalc_score(ctor->parameter_list, ilargs, env);
		ccpop_ctor();
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

constructor* meta_rfind_ctor(vector* ctor_vec, vector* args, vector* typeargs, frame* fr, int* outIndex) {
	//見つかった中からもっとも一致するコンストラクタを選択する
	int min = 1024;
	constructor* ret = NULL;
	for (int i = 0; i < ctor_vec->length; i++) {
		vector_item ve = vector_at(ctor_vec, i);
		constructor* ctor = (constructor*)ve;
		class_* cls = TYPE2CLASS(ctor->parent);
		//引数の個数が違うので無視
		if (ctor->parameter_list->length != args->length) {
			continue;
		}
		int score = meta_rcalc_score(ctor->parameter_list, args, typeargs, fr);
		if (score < min) {
			min = score;
			ret = ctor;
			(*outIndex) = i;
		}
	}
	return ret;
}
#include "meta_impl.h"
#include "../../il/il_argument.h"
#include "../../il/il_argument.h"
#include "../../error.h"
#include "../parameter.h"
#include "../type_parameter.h"
#include "../type_interface.h"
#include "../namespace.h"
#include "../../thread/thread.h"
#include "class_impl.h"
#include "../constructor.h"
#include "../object.h"
#include "../method.h"
#include "../../util/text.h"
#include <string.h>

int MetaILCalcScore(Vector* params, Vector* ilargs, enviroment* env, call_context* cctx) {
	assert(params->length == ilargs->length);
	int score = 0;
	bool illegal = false;
	//assert(ilctx->type_args_vec->length != 0);
	//Vector* type_args = TopVector(ilctx->type_args_vec);
	for (int i = 0; i < params->length; i++) {
		VectorItem varg = AtVector(ilargs, i);
		VectorItem vparam = AtVector(params, i);
		il_argument* arg = (il_argument*)varg;
		parameter* param = (parameter*)vparam;
		//実引数が NULL なら常に許容する
		int dist = 0;
		generic_type* argType = EvalILFactor(arg->factor, env, cctx);
		if(GetLastBCError()) {
			return -1;
		}
		if (argType->core_type != TYPE_NULL) {
			generic_type* a = ApplyGenericType(param->gtype, cctx);
			//PrintGenericType2(param->gtype, a);
			dist = DistanceGenericType(
				a,
			//	ApplyGenericType(argType, ilctx),
			//	param->gtype,
				argType, cctx
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

int MetaGCalcScore(Vector* params, Vector* gargs) {
	assert(params->length == gargs->length);
	//MetaILCalcScoreからのコピペ
	int score = 0;
	bool illegal = false;
	//assert(ilctx->type_args_vec->length != 0);
	//Vector* type_args = TopVector(ilctx->type_args_vec);
	for (int i = 0; i < params->length; i++) {
		VectorItem varg = AtVector(gargs, i);
		VectorItem vparam = AtVector(params, i);
		//il_argument* arg = (il_argument*)varg;
		parameter* param = (parameter*)vparam;
		//実引数が NULL なら常に許容する
		int dist = 0;
		generic_type* argType = (generic_type*)varg;
		if(GetLastBCError()) {
			return -1;
		}
		if (argType->core_type != TYPE_NULL) {
			generic_type* a = ApplyGenericType(param->gtype, NULL);
			dist = DistanceGenericType(
				a,
			//	ApplyGenericType(argType, ilctx),
			//	param->gtype,
				argType,
				GetSGThreadCContext()
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

int MetaRCalcScore(Vector* params, Vector* args, Vector* typeargs, frame* fr) {
	assert(params->length == args->length);
	int score = 0;
	bool illegal = false;
	for (int i = 0; i < params->length; i++) {
		VectorItem varg = AtVector(args, i);
		VectorItem vparam = AtVector(params, i);
		object* arg = (object*)varg;
		parameter* param = (parameter*)vparam;
		//実引数が NULL なら常に許容する
		int dist = 0;
		//generic_type* argType = EvalILFactor(arg->factor, env, ilctx);
		generic_type* argType = arg->gtype;
		if (argType->core_type != TYPE_NULL) {
			generic_type* a = RApplyGenericType(param->gtype, NULL,fr);
			dist = RDistanceGenericType(a, argType, fr);
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

method * MetaILFindMethod(Vector * method_vec, string_view namev, Vector * ilargs, enviroment * env, call_context* cctx, int * outIndex) {
	return MetaScopedILFindMethod(NULL, method_vec, namev, ilargs, env, cctx, outIndex);
}

method* MetaGFindMethod(Vector* method_vec, string_view namev, Vector * gargs, int* outIndex) {
	return MetaScopedGFindMethod(NULL, method_vec, namev, gargs, outIndex);
}

method* MetaScopedILFindMethod(class_* context, Vector* method_vec, string_view namev, Vector * ilargs, enviroment * env, call_context* cctx, int * outIndex) {
	(*outIndex) = -1;
	//CreateVTableClass(self);
	method* ret = NULL;
	int min = 1024;
	//全てのメソッドへ
	for (int i = 0; i < method_vec->length; i++) {
		VectorItem ve = AtVector(method_vec, i);
		method* m = (method*)ve;
		if(!IsMetaMethodAccessValid(m, cctx)) {
			continue;
		}
		//名前か引数の個数が違うので無視
		if (m->namev != namev ||
			m->parameters->length != ilargs->length
			) {
			continue;
		}
		//引数がひとつもないので、
		//型のチェックを行わない
		if (ilargs->length == 0) {
			(*outIndex) = i;
			return m;
		}
		int score = MetaILCalcScore(m->parameters, ilargs, env, cctx);
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

method* MetaScopedGFindMethod(class_* context, Vector* method_vec, string_view namev, Vector * gargs, int * outIndex) {
	(*outIndex) = -1;
	//CreateVTableClass(self);
	method* ret = NULL;
	int min = 1024;
	//全てのメソッドへ
	for (int i = 0; i < method_vec->length; i++) {
		VectorItem ve = AtVector(method_vec, i);
		method* m = (method*)ve;
		//名前か引数の個数が違うので無視
		if (m->namev != namev ||
			m->parameters->length != gargs->length
			) {
			continue;
		}
		//引数がひとつもないので、
		//型のチェックを行わない
		if (gargs->length == 0) {
			(*outIndex) = i;
			return m;
		}
		int score = MetaGCalcScore(m->parameters, gargs);
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

constructor* MetaILFindConstructor(Vector* ctor_vec, Vector* ilargs, enviroment* env, call_context* cctx, int* outIndex) {
	return MetaScopedILFindConstructor(NULL, ctor_vec, ilargs, env, cctx, outIndex);
}

constructor* MetaRFindConstructor(Vector* ctor_vec, Vector* args, Vector* typeargs, frame* fr, int* outIndex) {
	return MetaScopedRFindConstructor(NULL, ctor_vec, args, typeargs, fr, outIndex);
}

constructor* MetaScopedILFindConstructor(class_* context, Vector* ctor_vec, Vector* ilargs, enviroment* env, call_context* cctx, int* outIndex) {
	//見つかった中からもっとも一致するコンストラクタを選択する
	int min = 1024;
	constructor* ret = NULL;
	for (int i = 0; i < ctor_vec->length; i++) {
		VectorItem ve = AtVector(ctor_vec, i);
		constructor* ctor = (constructor*)ve;
		if(!IsMetaConstructorAccessValid(ctor, cctx)) {
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
		int score = MetaILCalcScore(ctor->parameter_list, ilargs, env, cctx);
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

constructor* MetaScopedRFindConstructor(class_* context, Vector* ctor_vec, Vector* gargs, Vector* typeargs, frame* fr, int* outIndex) {
	//見つかった中からもっとも一致するコンストラクタを選択する
	int min = 1024;
	constructor* ret = NULL;
	for (int i = 0; i < ctor_vec->length; i++) {
		VectorItem ve = AtVector(ctor_vec, i);
		constructor* ctor = (constructor*)ve;
		class_* cls = TYPE2CLASS(ctor->parent);
		//引数の個数が違うので無視
		if (ctor->parameter_list->length != gargs->length) {
			continue;
		}
		int score = MetaRCalcScore(ctor->parameter_list, gargs, typeargs, fr);
		if (score < min) {
			min = score;
			ret = ctor;
			(*outIndex) = i;
		}
	}
	return ret;
}

operator_overload* MetaGFindOperator(Vector* opov_vec, operator_type type, Vector* gargs, int* outIndex) {
	(*outIndex) = -1;
	int min = 1024;
	operator_overload* ret = NULL;
	for(int i=0; i<opov_vec->length; i++) {
		operator_overload* opov = AtVector(opov_vec, i);
		//オペレータの種類が違うので無視
		if(opov->type != type) {
			continue;
		}
		//引数の数が違うので無視
		if(opov->parameter_list->length != gargs->length) {
			continue;
		}
		int score = MetaGCalcScore(opov->parameter_list, gargs);
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

bool IsMetaMethodAccessValid(method* m, call_context* cctx) {
	class_* context = GetClassCContext(cctx);
	//privateメソッドなのに現在のコンテキストではない
	if(context != NULL &&
		m->access == ACCESS_PRIVATE_T &&
		TYPE2CLASS(m->parent) != context) {
		return false;
	}
	//protectedメソッドなのにそのサブクラスではない
	if(context != NULL &&
		m->access == ACCESS_PROTECTED_T &&
		DistanceClass(TYPE2CLASS(m->parent), context) < 0) {
		return false;
	}
	return true;
}

bool IsMetaConstructorAccessValid(constructor* ctor, call_context* cctx) {
	class_* context = GetClassCContext(cctx);
	//privateメソッドなのに現在のコンテキストではない
	if(context != NULL &&
		ctor->access == ACCESS_PRIVATE_T &&
		TYPE2CLASS(ctor->parent) != context) {
		return false;
	}
	//protectedメソッドなのにそのサブクラスではない
	if(context != NULL &&
		ctor->access == ACCESS_PROTECTED_T &&
		DistanceClass(TYPE2CLASS(ctor->parent), context) < 0) {
		return false;
	}
	return true;
}
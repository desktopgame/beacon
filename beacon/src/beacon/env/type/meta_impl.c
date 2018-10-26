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

int MetaILCalcScore(Vector* params, Vector* ilargs, Enviroment* env, CallContext* cctx) {
	assert(params->Length == ilargs->Length);
	int score = 0;
	bool illegal = false;
	//assert(ilctx->type_args_vec->Length != 0);
	//Vector* type_args = TopVector(ilctx->type_args_vec);
	for (int i = 0; i < params->Length; i++) {
		VectorItem varg = AtVector(ilargs, i);
		VectorItem vparam = AtVector(params, i);
		ILArgument* arg = (ILArgument*)varg;
		Parameter* param = (Parameter*)vparam;
		//実引数が NULL なら常に許容する
		int dist = 0;
		generic_type* argType = EvalILFactor(arg->Factor, env, cctx);
		if(GetLastBCError()) {
			return -1;
		}
		if (argType->core_type != TYPE_NULL) {
			generic_type* a = ApplyGenericType(param->GType, cctx);
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
	assert(params->Length == gargs->Length);
	//MetaILCalcScoreからのコピペ
	int score = 0;
	bool illegal = false;
	//assert(ilctx->type_args_vec->Length != 0);
	//Vector* type_args = TopVector(ilctx->type_args_vec);
	for (int i = 0; i < params->Length; i++) {
		VectorItem varg = AtVector(gargs, i);
		VectorItem vparam = AtVector(params, i);
		//il_argument* arg = (il_argument*)varg;
		Parameter* param = (Parameter*)vparam;
		//実引数が NULL なら常に許容する
		int dist = 0;
		generic_type* argType = (generic_type*)varg;
		if(GetLastBCError()) {
			return -1;
		}
		if (argType->core_type != TYPE_NULL) {
			generic_type* a = ApplyGenericType(param->GType, NULL);
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

int MetaRCalcScore(Vector* params, Vector* args, Vector* typeargs, Frame* fr) {
	assert(params->Length == args->Length);
	int score = 0;
	bool illegal = false;
	for (int i = 0; i < params->Length; i++) {
		VectorItem varg = AtVector(args, i);
		VectorItem vparam = AtVector(params, i);
		Object* arg = (Object*)varg;
		Parameter* param = (Parameter*)vparam;
		//実引数が NULL なら常に許容する
		int dist = 0;
		//generic_type* argType = EvalILFactor(arg->factor, env, ilctx);
		generic_type* argType = arg->gtype;
		if (argType->core_type != TYPE_NULL) {
			generic_type* a = RApplyGenericType(param->GType, NULL,fr);
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

Method * MetaILFindMethod(Vector * method_vec, StringView namev, Vector * ilargs, Enviroment * env, CallContext* cctx, int * outIndex) {
	return MetaScopedILFindMethod(NULL, method_vec, namev, ilargs, env, cctx, outIndex);
}

Method* MetaGFindMethod(Vector* method_vec, StringView namev, Vector * gargs, int* outIndex) {
	return MetaScopedGFindMethod(NULL, method_vec, namev, gargs, outIndex);
}

Method* MetaScopedILFindMethod(class_* context, Vector* method_vec, StringView namev, Vector * ilargs, Enviroment * env, CallContext* cctx, int * outIndex) {
	(*outIndex) = -1;
	//CreateVTableClass(self);
	Method* ret = NULL;
	int min = 1024;
	//全てのメソッドへ
	for (int i = 0; i < method_vec->Length; i++) {
		VectorItem ve = AtVector(method_vec, i);
		Method* m = (Method*)ve;
		if(!IsMetaMethodAccessValid(m, cctx)) {
			continue;
		}
		//名前か引数の個数が違うので無視
		if (m->Name != namev ||
			m->Parameters->Length != ilargs->Length
			) {
			continue;
		}
		//引数がひとつもないので、
		//型のチェックを行わない
		if (ilargs->Length == 0) {
			(*outIndex) = i;
			return m;
		}
		int score = MetaILCalcScore(m->Parameters, ilargs, env, cctx);
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

Method* MetaScopedGFindMethod(class_* context, Vector* method_vec, StringView namev, Vector * gargs, int * outIndex) {
	(*outIndex) = -1;
	//CreateVTableClass(self);
	Method* ret = NULL;
	int min = 1024;
	//全てのメソッドへ
	for (int i = 0; i < method_vec->Length; i++) {
		VectorItem ve = AtVector(method_vec, i);
		Method* m = (Method*)ve;
		//名前か引数の個数が違うので無視
		if (m->Name != namev ||
			m->Parameters->Length != gargs->Length
			) {
			continue;
		}
		//引数がひとつもないので、
		//型のチェックを行わない
		if (gargs->Length == 0) {
			(*outIndex) = i;
			return m;
		}
		int score = MetaGCalcScore(m->Parameters, gargs);
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

Constructor* MetaILFindConstructor(Vector* ctor_vec, Vector* ilargs, Enviroment* env, CallContext* cctx, int* outIndex) {
	return MetaScopedILFindConstructor(NULL, ctor_vec, ilargs, env, cctx, outIndex);
}

Constructor* MetaRFindConstructor(Vector* ctor_vec, Vector* args, Vector* typeargs, Frame* fr, int* outIndex) {
	return MetaScopedRFindConstructor(NULL, ctor_vec, args, typeargs, fr, outIndex);
}

Constructor* MetaScopedILFindConstructor(class_* context, Vector* ctor_vec, Vector* ilargs, Enviroment* env, CallContext* cctx, int* outIndex) {
	//見つかった中からもっとも一致するコンストラクタを選択する
	int min = 1024;
	Constructor* ret = NULL;
	for (int i = 0; i < ctor_vec->Length; i++) {
		VectorItem ve = AtVector(ctor_vec, i);
		Constructor* ctor = (Constructor*)ve;
		if(!IsMetaConstructorAccessValid(ctor, cctx)) {
			continue;
		}
		//引数の個数が違うので無視
		if (ctor->Parameters->Length != ilargs->Length) {
			continue;
		}
		//引数がひとつもないので、
		//型のチェックを行わない
		if (ilargs->Length == 0) {
			(*outIndex) = i;
			return ctor;
		}
		//もっともスコアの高いメソッドを選択する
		int score = MetaILCalcScore(ctor->Parameters, ilargs, env, cctx);
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

Constructor* MetaScopedRFindConstructor(class_* context, Vector* ctor_vec, Vector* gargs, Vector* typeargs, Frame* fr, int* outIndex) {
	//見つかった中からもっとも一致するコンストラクタを選択する
	int min = 1024;
	Constructor* ret = NULL;
	for (int i = 0; i < ctor_vec->Length; i++) {
		VectorItem ve = AtVector(ctor_vec, i);
		Constructor* ctor = (Constructor*)ve;
		class_* cls = TYPE2CLASS(ctor->Parent);
		//引数の個数が違うので無視
		if (ctor->Parameters->Length != gargs->Length) {
			continue;
		}
		int score = MetaRCalcScore(ctor->Parameters, gargs, typeargs, fr);
		if (score < min) {
			min = score;
			ret = ctor;
			(*outIndex) = i;
		}
	}
	return ret;
}

OperatorOverload* MetaGFindOperator(Vector* opov_vec, OperatorType type, Vector* gargs, int* outIndex) {
	(*outIndex) = -1;
	int min = 1024;
	OperatorOverload* ret = NULL;
	for(int i=0; i<opov_vec->Length; i++) {
		OperatorOverload* opov = AtVector(opov_vec, i);
		//オペレータの種類が違うので無視
		if(opov->Type != type) {
			continue;
		}
		//引数の数が違うので無視
		if(opov->Parameters->Length != gargs->Length) {
			continue;
		}
		int score = MetaGCalcScore(opov->Parameters, gargs);
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

bool IsMetaMethodAccessValid(Method* m, CallContext* cctx) {
	class_* context = GetClassCContext(cctx);
	//privateメソッドなのに現在のコンテキストではない
	if(context != NULL &&
		m->Access == ACCESS_PRIVATE_T &&
		TYPE2CLASS(m->Parent) != context) {
		return false;
	}
	//protectedメソッドなのにそのサブクラスではない
	if(context != NULL &&
		m->Access == ACCESS_PROTECTED_T &&
		DistanceClass(TYPE2CLASS(m->Parent), context) < 0) {
		return false;
	}
	return true;
}

bool IsMetaConstructorAccessValid(Constructor* ctor, CallContext* cctx) {
	class_* context = GetClassCContext(cctx);
	//privateメソッドなのに現在のコンテキストではない
	if(context != NULL &&
		ctor->Access == ACCESS_PRIVATE_T &&
		TYPE2CLASS(ctor->Parent) != context) {
		return false;
	}
	//protectedメソッドなのにそのサブクラスではない
	if(context != NULL &&
		ctor->Access == ACCESS_PROTECTED_T &&
		DistanceClass(TYPE2CLASS(ctor->Parent), context) < 0) {
		return false;
	}
	return true;
}
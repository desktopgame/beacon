#include "meta_impl.h"
#include <string.h>
#include "../../error.h"
#include "../../il/il_argument.h"
#include "../../thread/thread.h"
#include "../../util/text.h"
#include "../constructor.h"
#include "../method.h"
#include "../namespace.h"
#include "../object.h"
#include "../parameter.h"
#include "../type_interface.h"
#include "../type_parameter.h"
#include "class_impl.h"

int bc_MetaILCalcScore(bc_Vector* params, bc_Vector* ilargs, bc_Enviroment* env,
                       bc_CallContext* cctx) {
        assert(params->Length == ilargs->Length);
        int score = 0;
        bool illegal = false;
        // assert(ilctx->type_args_vec->Length != 0);
        // Vector* type_args = TopVector(ilctx->type_args_vec);
        for (int i = 0; i < params->Length; i++) {
                bc_VectorItem varg = bc_AtVector(ilargs, i);
                bc_VectorItem vparam = bc_AtVector(params, i);
                bc_ILArgument* arg = (bc_ILArgument*)varg;
                bc_Parameter* param = (bc_Parameter*)vparam;
                //実引数が NULL なら常に許容する
                int dist = 0;
                bc_GenericType* argType =
                    bc_EvalILFactor(arg->Factor, env, cctx);
                if (bc_GetLastPanic()) {
                        return -1;
                }
                if (argType->CoreType != BC_TYPE_NULL) {
                        bc_GenericType* a =
                            bc_ApplyGenericType(param->GType, cctx);
                        // PrintGenericType2(param->gtype, a);
                        dist = bc_DistanceGenericType(
                            a,
                            //	ApplyGenericType(argType,
                            // ilctx), 	param->gtype,
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

int bc_MetaGCalcScore(bc_Vector* params, bc_Vector* gargs) {
        assert(params->Length == gargs->Length);
        // MetaILCalcScoreからのコピペ
        int score = 0;
        bool illegal = false;
        // assert(ilctx->type_args_vec->Length != 0);
        // Vector* type_args = TopVector(ilctx->type_args_vec);
        for (int i = 0; i < params->Length; i++) {
                bc_VectorItem varg = bc_AtVector(gargs, i);
                bc_VectorItem vparam = bc_AtVector(params, i);
                // il_argument* arg = (il_argument*)varg;
                bc_Parameter* param = (bc_Parameter*)vparam;
                //実引数が NULL なら常に許容する
                int dist = 0;
                bc_GenericType* argType = (bc_GenericType*)varg;
                if (bc_GetLastPanic()) {
                        return -1;
                }
                if (argType->CoreType != BC_TYPE_NULL) {
                        bc_GenericType* a =
                            bc_ApplyGenericType(param->GType, NULL);
                        dist = bc_DistanceGenericType(
                            a,
                            //	ApplyGenericType(argType, ilctx),
                            //	param->gtype,
                            argType, bc_GetScriptThreadContext()
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

int bc_MetaRCalcScore(bc_Vector* params, bc_Vector* args, bc_Vector* typeargs,
                      bc_Frame* fr) {
        assert(params->Length == args->Length);
        int score = 0;
        bool illegal = false;
        for (int i = 0; i < params->Length; i++) {
                bc_VectorItem varg = bc_AtVector(args, i);
                bc_VectorItem vparam = bc_AtVector(params, i);
                bc_Object* arg = (bc_Object*)varg;
                bc_Parameter* param = (bc_Parameter*)vparam;
                //実引数が NULL なら常に許容する
                int dist = 0;
                // GenericType* argType = EvalILFactor(arg->factor, env, ilctx);
                bc_GenericType* argType = arg->GType;
                if (argType->CoreType != BC_TYPE_NULL) {
                        bc_GenericType* a =
                            bc_RApplyGenericType(param->GType, fr);
                        dist = bc_RDistanceGenericType(a, argType, fr);
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

bc_Method* bc_MetaILFindMethod(bc_Vector* method_vec, bc_StringView namev,
                               bc_Vector* ilargs, bc_Enviroment* env,
                               bc_CallContext* cctx, int* outIndex) {
        return bc_MetaScopedILFindMethod(NULL, method_vec, namev, ilargs, env,
                                         cctx, outIndex);
}

bc_Method* bc_MetaGFindMethod(bc_Vector* method_vec, bc_StringView namev,
                              bc_Vector* gargs, int* outIndex) {
        return bc_MetaScopedGFindMethod(NULL, method_vec, namev, gargs,
                                        outIndex);
}

bc_Method* bc_MetaScopedILFindMethod(bc_Class* context, bc_Vector* method_vec,
                                     bc_StringView namev, bc_Vector* ilargs,
                                     bc_Enviroment* env, bc_CallContext* cctx,
                                     int* outIndex) {
        (*outIndex) = -1;
        // CreateVTableClass(self);
        bc_Method* ret = NULL;
        int min = 1024;
        //全てのメソッドへ
        for (int i = 0; i < method_vec->Length; i++) {
                bc_VectorItem ve = bc_AtVector(method_vec, i);
                bc_Method* m = (bc_Method*)ve;
                if (!bc_IsMetaMethodAccessValid(m, cctx)) {
                        continue;
                }
                //名前か引数の個数が違うので無視
                if (m->Name != namev ||
                    m->Parameters->Length != ilargs->Length) {
                        continue;
                }
                //引数がひとつもないので、
                //型のチェックを行わない
                if (ilargs->Length == 0) {
                        (*outIndex) = i;
                        return m;
                }
                int score =
                    bc_MetaILCalcScore(m->Parameters, ilargs, env, cctx);
                if (score == -1) {
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

bc_Method* bc_MetaScopedGFindMethod(bc_Class* context, bc_Vector* method_vec,
                                    bc_StringView namev, bc_Vector* gargs,
                                    int* outIndex) {
        (*outIndex) = -1;
        // CreateVTableClass(self);
        bc_Method* ret = NULL;
        int min = 1024;
        //全てのメソッドへ
        for (int i = 0; i < method_vec->Length; i++) {
                bc_VectorItem ve = bc_AtVector(method_vec, i);
                bc_Method* m = (bc_Method*)ve;
                //名前か引数の個数が違うので無視
                if (m->Name != namev ||
                    m->Parameters->Length != gargs->Length) {
                        continue;
                }
                //引数がひとつもないので、
                //型のチェックを行わない
                if (gargs->Length == 0) {
                        (*outIndex) = i;
                        return m;
                }
                int score = bc_MetaGCalcScore(m->Parameters, gargs);
                if (score == -1) {
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

bc_Constructor* bc_MetaILFindConstructor(bc_Vector* ctor_vec, bc_Vector* ilargs,
                                         bc_Enviroment* env,
                                         bc_CallContext* cctx, int* outIndex) {
        return bc_MetaScopedILFindConstructor(NULL, ctor_vec, ilargs, env, cctx,
                                              outIndex);
}

bc_Constructor* bc_MetaRFindConstructor(bc_Vector* ctor_vec, bc_Vector* args,
                                        bc_Vector* typeargs, bc_Frame* fr,
                                        int* outIndex) {
        return bc_MetaScopedRFindConstructor(NULL, ctor_vec, args, typeargs, fr,
                                             outIndex);
}

bc_Constructor* bc_MetaScopedILFindConstructor(
    bc_Class* context, bc_Vector* ctor_vec, bc_Vector* ilargs,
    bc_Enviroment* env, bc_CallContext* cctx, int* outIndex) {
        //見つかった中からもっとも一致するコンストラクタを選択する
        int min = 1024;
        bc_Constructor* ret = NULL;
        for (int i = 0; i < ctor_vec->Length; i++) {
                bc_VectorItem ve = bc_AtVector(ctor_vec, i);
                bc_Constructor* ctor = (bc_Constructor*)ve;
                if (!bc_IsMetaConstructorAccessValid(ctor, cctx)) {
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
                int score =
                    bc_MetaILCalcScore(ctor->Parameters, ilargs, env, cctx);
                if (score == -1) {
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

bc_Constructor* bc_MetaScopedRFindConstructor(bc_Class* context,
                                              bc_Vector* ctor_vec,
                                              bc_Vector* gargs,
                                              bc_Vector* typeargs, bc_Frame* fr,
                                              int* outIndex) {
        //見つかった中からもっとも一致するコンストラクタを選択する
        int min = 1024;
        bc_Constructor* ret = NULL;
        for (int i = 0; i < ctor_vec->Length; i++) {
                bc_VectorItem ve = bc_AtVector(ctor_vec, i);
                bc_Constructor* ctor = (bc_Constructor*)ve;
                bc_Class* cls = BC_TYPE2CLASS(BC_MEMBER_TYPE(ctor));
                //引数の個数が違うので無視
                if (ctor->Parameters->Length != gargs->Length) {
                        continue;
                }
                int score =
                    bc_MetaRCalcScore(ctor->Parameters, gargs, typeargs, fr);
                if (score < min) {
                        min = score;
                        ret = ctor;
                        (*outIndex) = i;
                }
        }
        return ret;
}

bc_OperatorOverload* bc_MetaGFindOperator(bc_Vector* opov_vec,
                                          bc_OperatorType type,
                                          bc_Vector* gargs, int* outIndex) {
        (*outIndex) = -1;
        int min = 1024;
        bc_OperatorOverload* ret = NULL;
        for (int i = 0; i < opov_vec->Length; i++) {
                bc_OperatorOverload* opov = bc_AtVector(opov_vec, i);
                //オペレータの種類が違うので無視
                if (opov->Type != type) {
                        continue;
                }
                //引数の数が違うので無視
                if (opov->Parameters->Length != gargs->Length) {
                        continue;
                }
                int score = bc_MetaGCalcScore(opov->Parameters, gargs);
                if (min == -1) {
                        continue;
                }
                if (score < min) {
                        min = score;
                        (*outIndex) = i;
                        ret = opov;
                }
        }
        return ret;
}

bool bc_IsMetaMethodAccessValid(bc_Method* m, bc_CallContext* cctx) {
        bc_Class* context = bc_GetClassCContext(cctx);
        // privateメソッドなのに現在のコンテキストではない
        if (context != NULL && BC_MEMBER_ACCESS(m) == ACCESS_PRIVATE_T &&
            BC_TYPE2CLASS(BC_MEMBER_TYPE(m)) != context) {
                return false;
        }
        // protectedメソッドなのにそのサブクラスではない
        if (context != NULL && BC_MEMBER_ACCESS(m) == ACCESS_PROTECTED_T &&
            bc_DistanceClass(BC_TYPE2CLASS(BC_MEMBER_TYPE(m)), context) < 0) {
                return false;
        }
        return true;
}

bool bc_IsMetaConstructorAccessValid(bc_Constructor* ctor,
                                     bc_CallContext* cctx) {
        bc_Class* context = bc_GetClassCContext(cctx);
        // privateメソッドなのに現在のコンテキストではない
        if (context != NULL && BC_MEMBER_ACCESS(ctor) == ACCESS_PRIVATE_T &&
            BC_TYPE2CLASS(BC_MEMBER_TYPE(ctor)) != context) {
                return false;
        }
        // protectedメソッドなのにそのサブクラスではない
        if (context != NULL && BC_MEMBER_ACCESS(ctor) == ACCESS_PROTECTED_T &&
            bc_DistanceClass(BC_TYPE2CLASS(BC_MEMBER_TYPE(ctor)), context) <
                0) {
                return false;
        }
        return true;
}
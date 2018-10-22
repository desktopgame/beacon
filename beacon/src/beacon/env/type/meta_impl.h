#pragma once
#ifndef BEACON_ENV_META_H
#define BEACON_ENV_META_H
//クラス自体の実装に関わるメタ関数
#include "../method.h"
#include "../constructor.h"
#include "../operator_overload.h"
#include "../../il/call_context.h"
#include "../../util/vector.h"
#include "../../util/string_pool.h"
#include "../../vm/enviroment.h"
struct type;
struct class_;
struct constructor;
/**
 * 仮引数と実引数のマッチ率を返します.
 * 一つでも継承関係のないパラメータ/アーギュメントの組みを見つけると -1 を返します.
 * マッチ率が高ければ高いほど 0 に近い値を返します。
 * @param params
 * @param ilargs
 * @param env
 * @param cctx
 * @return
 */
int MetaILCalcScore(Vector* params, Vector* ilargs, Enviroment* env, CallContext* cctx);

/**
 * 仮引数と実引数のマッチ率を返します.
 * こちらは generic_type* を 使用します。
 * @param params
 * @param gargs
 * @return
 */
int MetaGCalcScore(Vector* params, Vector* gargs);

/**
 * 仮引数と実引数のマッチ率を返します.
 * こちらは object* を 使用します。
 * @param params
 * @param args
 * @param typeargs
 * @param fr
 * @return
 */
int MetaRCalcScore(Vector* params, Vector* args, Vector* typeargs, struct Frame* fr);

/**
 * もっとも一致するメソッドを返します.
 * @param method_vec
 * @param namev
 * @param ilargs
 * @param env
 * @param cctx
 * @param outIndex
 * @return
 */
method* MetaILFindMethod(Vector* method_vec, StringView namev, Vector * ilargs, Enviroment * env, CallContext* cctx, int * outIndex);

/**
 * もっとも一致するメソッドを返します.
 * @param method_vec
 * @param namev
 * @param gargs
 * @param outIndex
 * @return
 */
method* MetaGFindMethod(Vector* method_vec, StringView namev, Vector * gargs, int* outIndex);

/**
 * スコープに基づく方法でもっとも一致するメソッドを返します.
 * @param context
 * @param method_vec
 * @param namev
 * @param ilargs
 * @param env
 * @param cctx
 * @param outIndex
 * @return
 */
method* MetaScopedILFindMethod(struct class_* context, Vector* method_vec, StringView namev, Vector * ilargs, Enviroment * env, CallContext* cctx, int * outIndex);
/**
 * スコープに基づく方法でもっとも一致するメソッドを返します.
 * @param context
 * @param method_vec
 * @param namev
 * @param gargs
 * @param outIndex
 * @return
 */
method* MetaScopedGFindMethod(struct class_* context, Vector* method_vec, StringView namev, Vector * gargs, int * outIndex);

/**
 * もっとも一致するコンストラクタを返します.
 * @param method_vec
 * @param name
 * @param ilargs
 * @param env
 * @param cctx
 * @param outIndex
 * @return
 */
constructor* MetaILFindConstructor(Vector* ctor_vec, Vector* ilargs, Enviroment* env, CallContext* cctx, int* outIndex);

/**
 * もっとも一致するコンストラクタを返します.
 * @param ctor_vec
 * @param args
 * @param type_args
 * @param fr
 * @param outIndex
 * @return
 */
constructor* MetaRFindConstructor(Vector* ctor_vec, Vector* args, Vector* typeargs, struct Frame* fr, int* outIndex);
/**
 * スコープに基づく方法でもっとも一致するコンストラクタを返します.
 * @param context
 * @param ctor_vec
 * @param name
 * @param ilargs
 * @param env
 * @param outIndex
 * @return
 */
constructor* MetaScopedILFindConstructor(struct class_* context, Vector* ctor_vec, Vector* ilargs, Enviroment* env, CallContext* cctx, int* outIndex);
/**
 * スコープに基づく方法でもっとも一致するコンストラクタを返します.
 * @param context
 * @param ctor_vec
 * @param name
 * @param ilargs
 * @param env
 * @param outIndex
 * @return
 */
constructor* MetaScopedRFindConstructor(struct class_* context, Vector* ctor_vec, Vector* gargs, Vector* typeargs, struct Frame* fr, int* outIndex);

/**
 * 演算子オーバーロードを検索します.
 * @param opov_vec
 * @param type
 * @param gargs
 * @param outIndex
 * @return
 */
operator_overload* MetaGFindOperator(Vector* opov_vec, OperatorType type, Vector* gargs, int* outIndex);

/**
 * 指定のメソッドが現在のコンテキストで有効なら true.
 * @param m
 * @param cctx
 * @return
 */
bool IsMetaMethodAccessValid(struct method* m, CallContext* cctx);
/**
 * 指定のメソッドが現在のコンテキストで有効なら true.
 * @param m
 * @param cctx
 * @return
 */
bool IsMetaConstructorAccessValid(struct constructor* ctor, CallContext* cctx);
#endif // !SIGNAL_ENV_META_H

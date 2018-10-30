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
struct Type;
struct class_;
struct Constructor;
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
 * こちらは GenericType* を 使用します。
 * @param params
 * @param gargs
 * @return
 */
int MetaGCalcScore(Vector* params, Vector* gargs);

/**
 * 仮引数と実引数のマッチ率を返します.
 * こちらは Object* を 使用します。
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
Method* MetaILFindMethod(Vector* method_vec, StringView namev, Vector * ilargs, Enviroment * env, CallContext* cctx, int * outIndex);

/**
 * もっとも一致するメソッドを返します.
 * @param method_vec
 * @param namev
 * @param gargs
 * @param outIndex
 * @return
 */
Method* MetaGFindMethod(Vector* method_vec, StringView namev, Vector * gargs, int* outIndex);

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
Method* MetaScopedILFindMethod(struct class_* context, Vector* method_vec, StringView namev, Vector * ilargs, Enviroment * env, CallContext* cctx, int * outIndex);
/**
 * スコープに基づく方法でもっとも一致するメソッドを返します.
 * @param context
 * @param method_vec
 * @param namev
 * @param gargs
 * @param outIndex
 * @return
 */
Method* MetaScopedGFindMethod(struct class_* context, Vector* method_vec, StringView namev, Vector * gargs, int * outIndex);

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
Constructor* MetaILFindConstructor(Vector* ctor_vec, Vector* ilargs, Enviroment* env, CallContext* cctx, int* outIndex);

/**
 * もっとも一致するコンストラクタを返します.
 * @param ctor_vec
 * @param args
 * @param type_args
 * @param fr
 * @param outIndex
 * @return
 */
Constructor* MetaRFindConstructor(Vector* ctor_vec, Vector* args, Vector* typeargs, struct Frame* fr, int* outIndex);
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
Constructor* MetaScopedILFindConstructor(struct class_* context, Vector* ctor_vec, Vector* ilargs, Enviroment* env, CallContext* cctx, int* outIndex);
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
Constructor* MetaScopedRFindConstructor(struct class_* context, Vector* ctor_vec, Vector* gargs, Vector* typeargs, struct Frame* fr, int* outIndex);

/**
 * 演算子オーバーロードを検索します.
 * @param opov_vec
 * @param type
 * @param gargs
 * @param outIndex
 * @return
 */
OperatorOverload* MetaGFindOperator(Vector* opov_vec, OperatorType type, Vector* gargs, int* outIndex);

/**
 * 指定のメソッドが現在のコンテキストで有効なら true.
 * @param m
 * @param cctx
 * @return
 */
bool IsMetaMethodAccessValid(struct Method* m, CallContext* cctx);
/**
 * 指定のメソッドが現在のコンテキストで有効なら true.
 * @param m
 * @param cctx
 * @return
 */
bool IsMetaConstructorAccessValid(struct Constructor* ctor, CallContext* cctx);
#endif // !SIGNAL_ENV_META_H

#pragma once
#ifndef BEACON_ENV_META_H
#define BEACON_ENV_META_H
//クラス自体の実装に関わるメタ関数
#include "../method.h"
#include "../constructor.h"
#include "../operator_overload.h"
#include "../../util/vector.h"
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
 * @param ilctx
 * @return
 */
int meta_ilcalc_score(vector* params, vector* ilargs, struct enviroment* env);

/**
 * 仮引数と実引数のマッチ率を返します.
 * こちらは generic_type* を 使用します。
 * @param params
 * @param gargs
 * @return
 */
int meta_gcalc_score(vector* params, vector* gargs);

/**
 * 仮引数と実引数のマッチ率を返します.
 * こちらは object* を 使用します。
 * @param params
 * @param args
 * @param typeargs
 * @param fr
 * @return
 */
int meta_rcalc_score(vector* params, vector* args, vector* typeargs, struct frame* fr);

/**
 * もっとも一致するメソッドを返します.
 * @param method_vec
 * @param name
 * @param ilargs
 * @param env
 * @param outIndex
 * @return
 */
method* meta_ilfind_method(vector* method_vec, const char * name, vector * ilargs, enviroment * env, int * outIndex);

/**
 * もっとも一致するメソッドを返します.
 * @param method_vec
 * @param name
 * @param gargs
 * @param outIndex
 * @return
 */
method* meta_gfind_method(vector* method_vec, const char * name, vector * gargs, int* outIndex);

/**
 * スコープに基づく方法でもっとも一致するメソッドを返します.
 * @param context
 * @param method_vec
 * @param name
 * @param ilargs
 * @param env
 * @param outIndex
 * @return
 */
method* meta_scoped_ilfind_method(struct class_* context, vector* method_vec, const char * name, vector * ilargs, struct enviroment * env, int * outIndex);
/**
 * スコープに基づく方法でもっとも一致するメソッドを返します.
 * @param context
 * @param method_vec
 * @param name
 * @param gargs
 * @param outIndex
 * @return
 */
method* meta_scoped_gfind_method(struct class_* context, vector* method_vec, const char * name, vector * gargs, int * outIndex);

/**
 * もっとも一致するコンストラクタを返します.
 * @param method_vec
 * @param name
 * @param ilargs
 * @param env
 * @param outIndex
 * @return
 */
constructor* meta_ilfind_ctor(vector* ctor_vec, vector* ilargs, struct enviroment* env, int* outIndex);

/**
 * もっとも一致するコンストラクタを返します.
 * @param ctor_vec
 * @param args
 * @param type_args
 * @param fr
 * @param outIndex
 * @return
 */
constructor* meta_rfind_ctor(vector* ctor_vec, vector* args, vector* typeargs, struct frame* fr, int* outIndex);
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
constructor* meta_scoped_ilfind_ctor(struct class_* context, vector* ctor_vec, vector* ilargs, struct enviroment* env, int* outIndex);
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
constructor* meta_scoped_rfind_ctor(struct class_* context, vector* ctor_vec, vector* gargs, vector* typeargs, struct frame* fr, int* outIndex);

/**
 * 演算子オーバーロードを検索します.
 * @param opov_vec
 * @param type
 * @param gargs
 * @param outIndex
 * @return
 */
operator_overload* meta_gfind_operator(vector* opov_vec, operator_type type, vector* gargs, int* outIndex);

/**
 * @param opov_vec
 * @param gargs
 * @param outIndex
 * @return
 */
operator_overload* meta_gfind_operator_default_eq(vector* opov_vec, int* outIndex);

/**
 * @param opov_vec
 * @param outIndex
 * @return
 */
operator_overload* meta_gfind_operator_default_noteq(vector* opov_vec, int* outIndex);

/**
 * 指定のメソッドが現在のコンテキストで有効なら true.
 * @param context
 * @param m
 * @return
 */
bool meta_access_valid(struct class_* context, struct method* m);
/**
 * 指定のメソッドが現在のコンテキストで有効なら true.
 * @param context
 * @param m
 * @return
 */
bool meta_access_validc(struct class_* context, struct constructor* ctor);
#endif // !SIGNAL_ENV_META_H

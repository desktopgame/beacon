#pragma once
#ifndef BEACON_ENV_META_H
#define BEACON_ENV_META_H
//クラス自体の実装に関わるメタ関数
#include "../method.h"
#include "../constructor.h"
#include "../../util/vector.h"
#include "../../vm/enviroment.h"
struct class_;

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
int meta_calc_score(vector* params, vector* ilargs, struct enviroment* env);
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
 * @param cache
 * @param outIndex
 * @return
 */
method* meta_find_method(vector* method_vec, const char * name, vector * ilargs, enviroment * env, int * outIndex);
/**
 * もっとも一致するコンストラクタを返します.
 * @param method_vec
 * @param name
 * @param ilargs
 * @param env
 * @param cache
 * @param outIndex
 * @return
 */
constructor* meta_find_ctor(vector* ctor_vec, vector* ilargs, struct enviroment* env, int* outIndex);


constructor* meta_find_rctor(vector* ctor_vec, vector* args, vector* typeargs, struct frame* fr, int* outIndex);

#endif // !SIGNAL_ENV_META_H

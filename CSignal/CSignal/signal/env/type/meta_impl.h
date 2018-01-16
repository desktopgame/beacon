#pragma once
#ifndef SIGNAL_ENV_META_H
#define SIGNAL_ENV_META_H
//クラス自体の実装に関わるメタ関数
#include "../method.h"
#include "../../util/vector.h"
#include "../../vm/enviroment.h"

/**
 * もっとも一致するメソッドを返します.
 * @param method_vec
 * @param name
 * @param args
 * @param env
 * @param outIndex
 * @return
 */
method* meta_find_method(vector* method_vec, const char * name, vector * args, enviroment * env, int * outIndex);
#endif // !SIGNAL_ENV_META_H

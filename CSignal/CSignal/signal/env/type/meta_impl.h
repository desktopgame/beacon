#pragma once
#ifndef SIGNAL_ENV_META_H
#define SIGNAL_ENV_META_H
//クラス自体の実装に関わるメタ関数
#include "../method.h"
#include "../../util/vector.h"
#include "../../vm/enviroment.h"
struct class_;

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

/**
 * @param self
 * @param args<il_argument*>
 * @param env
 * @return
 */
vector* meta_find_constructors(struct class_* self, vector* args, enviroment* env);

/**
 * @param self
 * @param args<object*>
 * @return
 */
vector* meta_find_rconstructors(struct class_* self, vector* args);
#endif // !SIGNAL_ENV_META_H

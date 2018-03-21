#pragma once
#ifndef SIGNAL_ENV_CONSTRUCTOR_H
#define SIGNAL_ENV_CONSTRUCTOR_H
#include "../ast/access_level.h"
#include "../util/vector.h"
struct class_;
struct enviroment;
struct object;
struct vm;
/**
 * コンストラクタを表す構造体.
 */
typedef struct constructor {
	struct generic_type* gparent;
	struct enviroment* env;
	vector* parameter_list;
	access_level access;
} constructor;

/**
 * コンストラクタを作成します.
 * @return
 */
constructor* constructor_new();

/**
 * コンストラクタを出力します.
 * @param self
 * @param depth
 */
void constructor_dump(constructor* self, int depth);

/**
 * このコンストラクタを使用してオブジェクトを生成します.
 * @param self
 * @param args
 * @param parent
 * @return
 */
struct object* constructor_new_instance(constructor* self, vector* args, struct vm* parent);

/**
 * コンストラクタを開放します.
 * @param self
 */
void constructor_delete(constructor* self);
#endif // !SIGNAL_ENV_CONSTRUCTOR_H

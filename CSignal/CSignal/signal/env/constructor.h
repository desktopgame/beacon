#pragma once
#ifndef SIGNAL_ENV_CONSTRUCTOR_H
#define SIGNAL_ENV_CONSTRUCTOR_H
#include "../ast/access_level.h"
#include "../util/vector.h"
struct class_;
struct enviroment;
/**
 * コンストラクタを表す構造体.
 */
typedef struct constructor {
	struct class_* parent;
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
 * コンストラクタを開放します.
 * @param self
 */
void constructor_delete(constructor* self);
#endif // !SIGNAL_ENV_CONSTRUCTOR_H

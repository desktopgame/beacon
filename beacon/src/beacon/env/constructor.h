#pragma once
#ifndef BEACON_ENV_CONSTRUCTOR_H
#define BEACON_ENV_CONSTRUCTOR_H
#include "../ast/access_level.h"
#include "../util/vector.h"
struct type;
struct class_;
struct enviroment;
struct object;
struct frame;
/**
 * コンストラクタを表す構造体.
 */
typedef struct constructor {
	struct type* parent;
	struct enviroment* env;
	Vector* parameter_list;
	access_level access;
} constructor;

/**
 * コンストラクタを作成します.
 * @return
 */
constructor* constructor_new();

/**
 * このコンストラクタを使用してオブジェクトを生成します.
 * @param self
 * @param args
 * @param parent
 * @return
 */
struct object* constructor_new_instance(constructor* self, Vector* args, struct frame* parent);

/**
 * コンストラクタを開放します.
 * @param self
 */
void constructor_delete(constructor* self);
#endif // !SIGNAL_ENV_CONSTRUCTOR_H

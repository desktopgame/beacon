#pragma once
#ifndef BEACON_ENV_CONSTRUCTOR_H
#define BEACON_ENV_CONSTRUCTOR_H
#include "../ast/access_level.h"
#include "../util/vector.h"
struct type;
struct class_;
struct Enviroment;
struct object;
struct Frame;
/**
 * コンストラクタを表す構造体.
 */
typedef struct constructor {
	struct type* parent;
	struct Enviroment* env;
	Vector* parameter_list;
	AccessLevel access;
} constructor;

/**
 * コンストラクタを作成します.
 * @return
 */
constructor* NewConstructor();

/**
 * このコンストラクタを使用してオブジェクトを生成します.
 * @param self
 * @param args
 * @param parent
 * @return
 */
struct object* NewInstanceConstructor(constructor* self, Vector* args, struct Frame* parent);

/**
 * コンストラクタを開放します.
 * @param self
 */
void DeleteConstructor(constructor* self);
#endif // !SIGNAL_ENV_CONSTRUCTOR_H

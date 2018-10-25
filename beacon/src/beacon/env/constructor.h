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
typedef struct Constructor {
	struct type* parent;
	struct Enviroment* env;
	Vector* parameter_list;
	AccessLevel access;
} Constructor;

/**
 * コンストラクタを作成します.
 * @return
 */
Constructor* NewConstructor();

/**
 * このコンストラクタを使用してオブジェクトを生成します.
 * @param self
 * @param args
 * @param parent
 * @return
 */
struct object* NewInstanceConstructor(Constructor* self, Vector* args, struct Frame* parent);

/**
 * コンストラクタを開放します.
 * @param self
 */
void DeleteConstructor(Constructor* self);
#endif // !SIGNAL_ENV_CONSTRUCTOR_H

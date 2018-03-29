#pragma once
#ifndef BEACON_ENV_SCRIPT_METHOD_H
#define BEACON_ENV_SCRIPT_METHOD_H
#include "../util/vector.h"
#include "../vm/enviroment.h"
struct vm;
struct method;
struct enviroment;

/**
 * スクリプトで実装されたメソッド.
 */
typedef struct script_method {
//	vector* source;
	enviroment* env;
} script_method;

/**
 * スクリプトで実装されたメソッドを作成します.
 * @return
 */
script_method* script_method_new();

/**
 * メソッドを実行します.
 * @param self
 * @param parent
 * @param vmachine
 * @param env
 */
void script_method_execute(script_method* self, struct method* parent, struct vm* vmachine, struct enviroment* env);

/**
 * メソッドを開放します.
 * @param self
 */
void script_method_delete(script_method* self);
#endif // !SIGNAL_ENV_SCRIPT_METHOD_H

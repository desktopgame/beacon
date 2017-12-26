#pragma once
#ifndef SIGNAL_ENV_SCRIPT_METHOD_H
#define SIGNAL_ENV_SCRIPT_METHOD_H
#include "../util/vector.h"
struct vm;
struct method;

/**
 * スクリプトで実装されたメソッド.
 */
typedef struct script_method {
	vector* source;
} script_method;

/**
 * スクリプトで実装されたメソッドを作成します.
 * @return
 */
script_method* script_method_new();

/**
 * メソッドを実行します.
 * @param self
 * @param vm
 */
void script_method_execute(script_method* self, struct method* parent, struct vm* vm);

/**
 * メソッドを開放します.
 * @param self
 */
void script_method_delete(script_method* self);
#endif // !SIGNAL_ENV_SCRIPT_METHOD_H

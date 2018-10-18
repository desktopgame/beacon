#pragma once
#ifndef BEACON_ENV_SCRIPT_METHOD_H
#define BEACON_ENV_SCRIPT_METHOD_H
#include "../util/vector.h"
#include "../vm/enviroment.h"
struct frame;
struct method;
struct Enviroment;

/**
 * スクリプトで実装されたメソッド.
 */
typedef struct script_method {
//	Vector* source;
	Enviroment* env;
} script_method;

/**
 * スクリプトで実装されたメソッドを作成します.
 * @return
 */
script_method* NewScriptMethod();

/**
 * メソッドを実行します.
 * @param self
 * @param parent
 * @param fr
 * @param env
 */
void ExecuteScriptMethod(script_method* self, struct method* parent, struct frame* fr, Enviroment* env);

/**
 * メソッドを開放します.
 * @param self
 */
void DeleteScriptMethod(script_method* self);
#endif // !SIGNAL_ENV_SCRIPT_METHOD_H

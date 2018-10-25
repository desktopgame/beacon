#pragma once
#ifndef BEACON_ENV_SCRIPT_METHOD_H
#define BEACON_ENV_SCRIPT_METHOD_H
#include "../util/vector.h"
#include "../vm/enviroment.h"
struct Frame;
struct Method;
struct Enviroment;

/**
 * スクリプトで実装されたメソッド.
 */
typedef struct ScriptMethod {
//	Vector* source;
	Enviroment* env;
} ScriptMethod;

/**
 * スクリプトで実装されたメソッドを作成します.
 * @return
 */
ScriptMethod* NewScriptMethod();

/**
 * メソッドを実行します.
 * @param self
 * @param parent
 * @param fr
 * @param env
 */
void ExecuteScriptMethod(ScriptMethod* self, struct Method* parent, struct Frame* fr, Enviroment* env);

/**
 * メソッドを開放します.
 * @param self
 */
void DeleteScriptMethod(ScriptMethod* self);
#endif // !SIGNAL_ENV_SCRIPT_METHOD_H

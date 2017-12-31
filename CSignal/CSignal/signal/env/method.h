#pragma once
#ifndef SIGNAL_ENV_METHOD_H
#define SIGNAL_ENV_METHOD_H
#include "script_method.h"
#include "native_method.h"
#include "../util/vector.h"
#include "../ast/access_level.h"
#include "../ast/modifier_type.h"
struct class_;
struct vm;
struct enviroment;

/**
 * メソッドの種類を表す列挙.
 */
typedef enum method_type {
	method_type_script,
	method_type_native,
} method_type;

/**
 * メソッドを表す構造体.
 */
typedef struct method {
	char* name;
	method_type type;
	//struct class_* decleared_type;
	struct class_* parent;
	struct class_* return_type;
	vector* parameter_list;
	access_level access;
	modifier_type modifier;
	union {
		script_method* script_method;
		native_method* native_method;
	} u;
} method;

/**
 * メソッドを作成します.
 * @param name
 * @return
 */
method* method_new(const char* name);

/**
 * メソッドを実行します.
 * @param self
 * @param vm
 * @param env
 */
void method_execute(method* self, struct vm* vm, struct enviroment* env);

/**
 * メソッドを出力します.
 * @param self
 * @param depth
 */
void method_dump(method* self, int depth);

/**
 * メソッドを開放します.
 * @param self
 */
void method_delete(method* self);
#endif // !SIGNAL_ENV_METHOD_H

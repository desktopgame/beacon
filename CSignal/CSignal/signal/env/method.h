#pragma once
#ifndef SIGNAL_ENV_METHOD_H
#define SIGNAL_ENV_METHOD_H
#include "script_method.h"
#include "native_method.h"
struct parameter_list;
struct class_;
struct vm;

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
	struct class_* return_type;
	struct parameter_list* parameter_list;
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
 */
void method_execute(method* self, struct vm* vm);

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

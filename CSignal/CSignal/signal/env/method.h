#pragma once
#ifndef SIGNAL_ENV_METHOD_H
#define SIGNAL_ENV_METHOD_H
struct parameter_list;
struct class_;

/**
 * メソッドを表す構造体.
 */
typedef struct method {
	char* name;
	//struct class_* decleared_type;
	struct class_* return_type;
	struct parameter_list* parameter_list;
} method;

/**
 * メソッドを作成します.
 * @param name
 * @return
 */
method* method_new(const char* name);

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

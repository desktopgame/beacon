#pragma once
#ifndef BEACON_ENV_METHOD_H
#define BEACON_ENV_METHOD_H
#include "script_method.h"
#include "native_method.h"
#include "../util/vector.h"
#include "../util/string_pool.h"
#include "../ast/access_level.h"
#include "../ast/modifier_type.h"
#include <stdbool.h>
struct type;
struct frame;
struct enviroment;

/**
 * メソッドの種類を表す列挙.
 */
typedef enum method_type {
	method_type_script,
	method_type_native,
	method_type_abstract,
} method_type;

/**
 * メソッドを表す構造体.
 */
typedef struct method {
	string_view namev;
	method_type type;
	//struct class_* decleared_type;
	struct type* parent;
	struct generic_type* return_gtype;
	vector* parameter_list;
	vector* type_parameter_list;
	access_level access;
	modifier_type modifier;
	union {
		script_method* script_method;
		native_method* native_method;
	} u;
} method;

/**
 * メソッドを作成します.
 * @param namev
 * @param filename
 * @param lineno
 * @return
 */
method* method_malloc(string_view namev, const char* filename, int lineno);
#define method_new(namev) (method_malloc(namev, __FILE__, __LINE__))

/**
 * メソッドを実行します.
 * @param self
 * @param frame
 * @param env
 */
void method_execute(method* self, struct frame* fr, struct enviroment* env);

/**
 * メソッドを出力します.
 * @param self
 * @param depth
 */
void method_dump(method* self, int depth);

/**
 * メソッドa とb が完全に等価である場合に true を返します.
 * もしくは戻り値がサブクラス型でオーバライドされている場合でも true です。
 * @see http://www.ne.jp/asahi/hishidama/home/tech/java/covariant.html
 * @param superM
 * @param subM
 * @return
 */
bool method_override(method* superM, method* subM);

/**
 * @param self
 * @param name
 * @return
 */
int method_for_generic_index(method* self, string_view namev);

/**
 * メソッドを開放します.
 * @param self
 */
void method_delete(method* self);

/**
 * @param abstract
 * @param concrete
 * @return
 */
struct generic_type* method_diff(method* abstract, method* concrete);
#endif // !SIGNAL_ENV_METHOD_H

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
struct interface_;
struct frame;
struct Enviroment;
struct CallContext;
struct class_loader;

/**
 * メソッドの種類を表す列挙.
 */
typedef enum method_type {
	METHOD_TYPE_SCRIPT_T,
	METHOD_TYPE_NATIVE_T,
	METHOD_TYPE_ABSTRACT_T,
} method_type;

/**
 * メソッドを表す構造体.
 */
typedef struct method {
	StringView namev;
	method_type type;
	//struct class_* decleared_type;
	struct type* parent;
	struct generic_type* return_gtype;
	Vector* parameters;
	Vector* type_parameters;
	AccessLevel access;
	ModifierType modifier;
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
method* MallocMethod(StringView namev, const char* filename, int lineno);
#define method_new(namev) (MallocMethod(namev, __FILE__, __LINE__))

/**
 * メソッドを実行します.
 * @param self
 * @param frame
 * @param env
 */
void ExecuteMethod(method* self, struct frame* fr, Enviroment* env);

/**
 * メソッドa とb が完全に等価である場合に true を返します.
 * もしくは戻り値がサブクラス型でオーバライドされている場合でも true です。
 * @see http://www.ne.jp/asahi/hishidama/home/tech/java/covariant.html
 * @param superM
 * @param subM
 * @param cctx
 * @return
 */
bool IsOverridedMethod(method* superM, method* subM, struct CallContext* cctx);

/**
 * @param self
 * @param name
 * @return
 */
int GetGenericIndexForMethod(method* self, StringView namev);

/**
 * メソッドを開放します.
 * @param self
 */
void DeleteMethod(method* self);

/**
 * このメソッドのマングル表現を返します.
 * @param self
 * @return
 */
StringView MangleMethod(method* self);

/**
 * 型の完全名とマングル表現を連結して返します.
 * @param self
 * @return
 */
StringView GetMethodUniqueName(method* self);

/**
 * メソッドがコルーチンとして機能できるなら true.
 * @param self
 * @return
 */
bool IsCoroutineMethod(method* self);

/**
 * メソッドがイールドパターンで実装されているなら true.
 * @param self
 * @param error
 * @return
 */
bool IsYieldMethod(method* self, Vector* stmt_list, bool* error);

/**
 * このメソッドのためのユニークなイテレータ型を作成します.
 * 戻り値が Iterator である必要があります。
 * @param self
 * @param cll
 * @param stmt_list
 * @return
 */
struct type* CreateIteratorTypeFromMethod(method* self, struct class_loader* cll, Vector* stmt_list);

#endif // !SIGNAL_ENV_METHOD_H

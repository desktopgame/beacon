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
struct Frame;
struct Enviroment;
struct CallContext;
struct class_loader;

/**
 * メソッドの種類を表す列挙.
 */
typedef enum MethodType {
	METHOD_TYPE_SCRIPT_T,
	METHOD_TYPE_NATIVE_T,
	METHOD_TYPE_ABSTRACT_T,
} MethodType;

/**
 * メソッドを表す構造体.
 */
typedef struct Method {
	StringView Name;
	MethodType Type;
	//struct class_* decleared_type;
	struct type* Parent;
	struct generic_type* ReturnGType;
	Vector* Parameters;
	Vector* TypeParameters;
	AccessLevel Access;
	ModifierType Modifier;
	union {
		script_method* Script;
		NativeMethod* Native;
	} Kind;
} Method;

/**
 * メソッドを作成します.
 * @param name
 * @param filename
 * @param lineno
 * @return
 */
Method* MallocMethod(StringView name, const char* filename, int lineno);
#define method_new(name) (MallocMethod(name, __FILE__, __LINE__))

/**
 * メソッドを実行します.
 * @param self
 * @param frame
 * @param env
 */
void ExecuteMethod(Method* self, struct Frame* fr, Enviroment* env);

/**
 * メソッドa とb が完全に等価である場合に true を返します.
 * もしくは戻り値がサブクラス型でオーバライドされている場合でも true です。
 * @see http://www.ne.jp/asahi/hishidama/home/tech/java/covariant.html
 * @param superM
 * @param subM
 * @param cctx
 * @return
 */
bool IsOverridedMethod(Method* superM, Method* subM, struct CallContext* cctx);

/**
 * @param self
 * @param name
 * @return
 */
int GetGenericIndexForMethod(Method* self, StringView namev);

/**
 * メソッドを開放します.
 * @param self
 */
void DeleteMethod(Method* self);

/**
 * このメソッドのマングル表現を返します.
 * @param self
 * @return
 */
StringView MangleMethod(Method* self);

/**
 * 型の完全名とマングル表現を連結して返します.
 * @param self
 * @return
 */
StringView GetMethodUniqueName(Method* self);

/**
 * メソッドがコルーチンとして機能できるなら true.
 * @param self
 * @return
 */
bool IsCoroutineMethod(Method* self);

/**
 * メソッドがイールドパターンで実装されているなら true.
 * @param self
 * @param error
 * @return
 */
bool IsYieldMethod(Method* self, Vector* stmt_list, bool* error);

/**
 * このメソッドのためのユニークなイテレータ型を作成します.
 * 戻り値が Iterator である必要があります。
 * @param self
 * @param cll
 * @param stmt_list
 * @return
 */
struct type* CreateIteratorTypeFromMethod(Method* self, struct class_loader* cll, Vector* stmt_list);

#endif // !SIGNAL_ENV_METHOD_H

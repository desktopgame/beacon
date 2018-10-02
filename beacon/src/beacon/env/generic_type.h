#pragma once
#ifndef BEACON_ENV_GENERIC_TYPE_H
#define BEACON_ENV_GENERIC_TYPE_H
#include "../util/vector.h"
//#include "type_parameter_rule.h"
#include <stdbool.h>
#include <assert.h>

#define GENERIC2TYPE(gtype) (GenericTypeToType(gtype))
#define TYPE2GENERIC(type) (type->generic_self)

struct type;
struct method;
struct enviroment;
struct virtual_type;
struct frame;
struct call_context;
/**
 * 型変数つきの型宣言の型引数では generic_type 自身が使われますが、
 * それ自体が型変数の場合、何の型変数を指しているかを示す列挙型です.
 */
typedef enum generic_type_tag {
	GENERIC_TYPE_TAG_NONE_T,
	//クラスの型変数
	GENERIC_TYPE_TAG_CLASS_T,
	//メソッドの型変数
	GENERIC_TYPE_TAG_METHOD_T,
} generic_type_tag;

/**
 * 型変数つきの型宣言.
 */
typedef struct generic_type {
	struct type* core_type;
	Vector* type_args_list;
	//このジェネリックタイプの紐づけたられたコンテナ
	union {
		struct type* type_;
		struct method* method_;
	} u;
	//もしこの型が List<T> の Tを表すなら、
	//外側のクラスの何番目の型変数かを格納する。
	int virtual_type_index;
	generic_type_tag tag;
	bool mark;
	bool is_ctor;
} generic_type;

//#define generic_type_validate(self) assert((self)->core_type != NULL || self->virtual_type_index != -1)

/**
 * 新しい型変数つきの型宣言を作成します.
 * @param ctype
 * @return
 */
#define generic_NewType(ctype) (MallocGenericType(ctype, __FILE__, __LINE__))

/**
 * core_typeがNULL以外なら generic_selfを参照し、
 * NULLなら新規作成します。
 * @param core_type
 * @return
 */
generic_type* RefGenericType(struct type* core_type);

/**
 * 新しい型変数つきの型宣言を作成します.
 * 通常はマクロ版の generic_NewType を使用します。
 * @param ctype
 * @return
 */
generic_type* MallocGenericType(struct type* core_type, const char* filename, int lineno);

/**
 * ジェネリックタイプを複製します.
 * @param self
 * @return
 */
generic_type* CloneGenericType(generic_type* self);

/**
 * 現在のスクリプトコンテキストでどこからも参照されていない
 * generic_type の一覧を解放します。
 */
void CollectGenericType();

/**
 * type#generic_self を解放する時に使います.
 * CollectGenericType より後に呼び出してください。
 * @param a
 */
void LostownershipGenericType(generic_type* a);

/**
 * self の子要素として a を追加します.
 * @param self
 * @param a
 */
void AddArgsGenericType(generic_type* self, generic_type* a);

/**
 * a と b の距離を返します.
 * メソッドを解決する時、もっともマッチするオーバーロードを見つけるために使用されます。
 * @param self
 * @param other
 * @param cctx
 * @return 同じなら 0
 *         異なる継承階層なら -1
 *         サブタイプなら階層の数
 */
int DistanceGenericType(generic_type* self, generic_type* other, struct call_context* cctx);
/**
 * a と b の距離を返します.
 * メソッドを解決する時、もっともマッチするオーバーロードを見つけるために使用されます。
 * @param self
 * @param other
 * @param fr
 * @return 同じなら 0
 *         異なる継承階層なら -1
 *         サブタイプなら階層の数
 */
int RDistanceGenericType(generic_type* self, generic_type* other, struct frame* fr);

/**
 * 型変数と型を出力します.
 * @param self
 */
void PrintGenericType(generic_type* self);

/**
 * ジェネリックタイプをオペコードとして出力します.
 * @param self
 * @param env
 * @param ilctx
 */
void GenerateGenericType(generic_type* self, struct enviroment* env);

/**
 * 現在のコンテキストで self の型変数を解決します.
 * T ではなく T を内包する型(List<T>) などが戻り値になる時に使用されます。
 * @param self
 * @param cctx
 * @return
 */
generic_type* ApplyGenericType(generic_type* self, struct call_context* cctx);
/**
 * 現在のコンテキストで self の型変数を解決します.
 * T ではなく T を内包する型(List<T>) などが戻り値になる時に使用されます。
 * @param self
 * @param fr
 * @return
 */
generic_type* RApplyGenericType(generic_type* self, struct call_context* cctx, struct frame* fr);

/**
 * generic_type を type へ変換します.
 * @param self
 * @return
 */
struct type* GenericTypeToType(generic_type* self);
#endif // !SIGNAL_ENV_GENERIC_TYPE_H

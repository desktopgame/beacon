#pragma once
#ifndef BEACON_ENV_GENERIC_TYPE_H
#define BEACON_ENV_GENERIC_TYPE_H
#include "../util/vector.h"
//#include "type_parameter_rule.h"
#include <stdbool.h>
#include <assert.h>

#define GENERIC2TYPE(gtype) (generic_type_to_type(gtype))
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
	generic_type_tag_none,
	//クラスの型変数
	generic_type_tag_class,
	//メソッドの型変数
	generic_type_tag_method,
} generic_type_tag;

/**
 * 型変数つきの型宣言.
 */
typedef struct generic_type {
	struct type* core_type;
	vector* type_args_list;
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
#define generic_type_new(ctype) (generic_type_malloc(ctype, __FILE__, __LINE__))

/**
 * core_typeがNULL以外なら generic_selfを参照し、
 * NULLなら新規作成します。
 * @param core_type
 * @return
 */
generic_type* generic_type_ref(struct type* core_type);

/**
 * 新しい型変数つきの型宣言を作成します.
 * 通常はマクロ版の generic_type_new を使用します。
 * @param ctype
 * @return
 */
generic_type* generic_type_malloc(struct type* core_type, const char* filename, int lineno);

/**
 * ジェネリックタイプを複製します.
 * @param self
 * @return
 */
generic_type* generic_type_clone(generic_type* self);

/**
 * 現在のスクリプトコンテキストでどこからも参照されていない
 * generic_type の一覧を解放します。
 */
void generic_type_collect();

/**
 * type#generic_self を解放する時に使います.
 * generic_type_collect より後に呼び出してください。
 * @param a
 */
void generic_type_lostownership(generic_type* a);

/**
 * self の子要素として a を追加します.
 * @param self
 * @param a
 */
void generic_type_addargs(generic_type* self, generic_type* a);

/**
 * a と b の距離を返します.
 * メソッドを解決する時、もっともマッチするオーバーロードを見つけるために使用されます。
 * @param self
 * @param other
 * @return 同じなら 0
 *         異なる継承階層なら -1
 *         サブタイプなら階層の数
 */
int generic_type_distance(generic_type* self, generic_type* other);
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
int generic_type_rdistance(generic_type* self, generic_type* other, struct frame* fr);

/**
 * 型変数と型を出力します.
 * @param self
 */
void generic_type_print(generic_type* self);

/**
 * self が int 型なら true.
 * @param self
 * @return
 */
bool generic_type_int(generic_type* self);

/**
 * self が double 型なら true.
 * @param self
 * @return
 */
bool generic_type_double(generic_type* self);

/**
 * self が bool 型なら true.
 * @param self
 * @return
 */
bool generic_type_bool(generic_type* self);

/**
 * ジェネリックタイプをオペコードとして出力します.
 * @param self
 * @param env
 * @param ilctx
 */
void generic_type_generate(generic_type* self, struct enviroment* env);

/**
 * 現在のコンテキストで self の型変数を解決します.
 * T ではなく T を内包する型(List<T>) などが戻り値になる時に使用されます。
 * @param self
 * @param cctx
 * @return
 */
generic_type* generic_type_apply(generic_type* self, struct call_context* cctx);
/**
 * 現在のコンテキストで self の型変数を解決します.
 * T ではなく T を内包する型(List<T>) などが戻り値になる時に使用されます。
 * @param self
 * @param fr
 * @return
 */
generic_type* generic_type_rapply(generic_type* self, struct call_context* cctx, struct frame* fr);

/**
 * generic_type を type へ変換します.
 * @param self
 * @return
 */
struct type* generic_type_to_type(generic_type* self);

/**
 * @param super
 * @param sub
 * @return
 */
bool generic_type_override(generic_type* super, generic_type* sub);

/**
 * @param a
 * @param b
 * @return
 */
bool generic_type_equals(generic_type* a, generic_type* b);

/**
 * @param self
 * @param name
 * @return
 */
bool generic_type_compare(generic_type* self, const char* name);

/**
 * @param a
 * @param b
 */
void generic_type_print2(generic_type* a, generic_type* b);
#endif // !SIGNAL_ENV_GENERIC_TYPE_H

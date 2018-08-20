#pragma once
#ifndef BEACON_ENV_TYPE_INTERFACE_H
#define BEACON_ENV_TYPE_INTERFACE_H
#include <stdbool.h>
#include "../util/vector.h"
#include "../util/string_pool.h"
#include "../il/call_context.h"

#define TYPE2CLASS(type) (type_cast_class(type))
#define TYPE2INTERFACE(type) (type_cast_interface(type))
/**
 * 型の種類を表すタグ.
 */
typedef enum type_tag {
	type_class,
	type_interface,
	type_enum
} type_tag;

struct namespace_;
struct class_;
struct interface_;
struct field;
struct method;
struct property;
struct enviroment;
struct vtable;
struct generic_type;

typedef enum type_state {
	/**
	 * 生成直後.
	 */
	type_none = 1 << 0,
	/**
	 * 言語仕様のためにプリロードされるクラス.
	 * 後で正式に読み込まれるまで "保留" 状態とします。
	 */
	type_pending = 1 << 1,
	/**
	 * 型宣言を発見し、名前空間へ登録されたことを示します.
	 */
	type_register = 1 << 2,
	/**
	 * ある型のメンバ宣言を読み込んだことを示します.
	 */
	type_decl = 1 << 3,
	/**
	 * ある型のメンバ実装を読み込んだことを示します.
	 */
	type_impl = 1 << 4
} type_state;

/**
 * 型を表す構造体.
 */
typedef struct type {
	type_tag tag;
	struct namespace_* location;
	struct generic_type* generic_self;
	int absolute_index;
	type_state state;
	union {
		struct class_* class_;
		struct interface_* interface_;
	} u;
} type;

/**
 * 型を作成します.
 * @return
 */
type* type_new();

struct generic_type* type_init_generic(type* self, int counts);

/**
 * この型の名前を返します.
 * @param self
 * @return
 */
string_view type_name(type* self);

/**
 * この型の完全な名前を返します.
 * @param self
 * @return
 */
string_view type_full_name(type* self);

/**
 * この型にフィールドを追加します.
 * @param self
 * @param f
 */
void type_add_field(type* self, struct field* f);

/**
 * この型にプロパティを追加します.
 * @param self
 * @param p
 */
void type_add_property(type* self, struct property* p);

/**
 * この型にメソッドを追加します.
 * @param self
 * @param m
 */
void type_add_method(type* self, struct method* m);

/**
 * この型からメソッドを検索します.
 * @param self
 * @param namev
 * @param args
 * @param env
 * @param cctx
 * @param outIndex
 * @return
 */
struct method* type_ilfind_method(type* self, string_view namev, vector* args, struct enviroment* env, call_context* cctx, int* outIndex);

/**
 * この型から静的メソッドを検索します.
 * @param self
 * @param namev
 * @param args
 * @param env
 * @param cctx
 * @param outIndex
 * @return
 */
struct method* type_ilfind_smethod(type* self, string_view namev, vector* args, struct enviroment* env, call_context* cctx, int* outIndex);

/**
 * 仮想関数の一覧を返します.
 * @param self
 * @return
 */
struct vtable* type_vtable(type* self);

/**
 * 型の距離を返します.
 * @param super
 * @param sub
 * @return
 */
int type_distance(type* super, type* sub);

/**
 * 型情報を残してメソッドやフィールドなどのみを開放します.
 * @param self
 */
void type_unlink(type* self);

/**
 * 指定の名前の型変数が何番目に表れるかを返します.
 * @param self
 * @param namev
 * @return
 */
int type_for_generic_index(type* self, string_view namev);

/**
 * selfの継承クラスや実装インターフェイスに a が現れるなら型変数付きで返します.
 * 例えば
 *
 * class IntList : List<Int>
 * を表すクラスに List<T> を渡すと List<Int> が返ります。
 * @param self
 * @param a
 * @return
 */
struct generic_type* type_find_impl(type* self, type* a);

/**
 * この型の型引数の一覧を返します.
 * @param self
 * @return
 */
vector* type_parameter_list(type* self);

/**
 * この型の実装インターフェイスの一覧を返します.
 * @param self
 * @return
 */
vector* type_implement_list(type* self);

/**
 * この型がクラス/インターフェイスを表すとき、
 * 指定位置の型変数を返します.
 * @param self
 * @param index
 * @return
 */
struct generic_type* type_type_parameter_at(type* self, int index);

int type_type_parameter_len(type* self);

/**
 * 型を開放します.
 * @param self
 */
void type_delete(type* self);

struct class_* type_cast_class(type* self);
struct interface_* type_cast_interface(type* self);

/**
 * abstractにはクラス/インターフェイスを渡します.
 * concreteの親クラス/実装インターフェイス一覧から abstract を検索し、 generic_type で返します。
 * @param abstract
 * @param concrete
 * @return
 */
struct generic_type* type_baseline(type* abstract, type* concrete);

/**
 * 同じインターフェイスが二回現れるなら NULL 以外.
 * @param self
 * @return
 */
struct interface_* type_interface_valid(type* self);

/**
 * 抽象クラスかインターフェイスなら true.
 * @param self
 * @return
 */
bool type_is_abstract(type* self);

/**
 * targ を型実引数として generic_type を生成します.
 * @param self
 * @param targ
 * @return
 */
struct generic_type* type_instanced(type* self, struct generic_type* targ);

/**
 * 可能なら self を class へ変換します.
 * 失敗したなら NULL
 * @param self
 * @return
 */
struct class_* type_as_class(type* self);
/**
 * 可能なら self を interface へ変換します.
 * 失敗したなら NULL
 * @param self
 * @return
 */
struct interface_* type_as_interface(type* self);
#endif // !SIGNAL_ENV_TYPE_INTERFACE_H

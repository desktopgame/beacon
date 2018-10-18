#pragma once
#ifndef BEACON_ENV_TYPE_INTERFACE_H
#define BEACON_ENV_TYPE_INTERFACE_H
#include <stdbool.h>
#include "../util/vector.h"
#include "../util/string_pool.h"
#include "../il/call_context.h"

#define TYPE2CLASS(type) (CastClassType(type))
#define TYPE2INTERFACE(type) (CastInterfaceType(type))
/**
 * 型の種類を表すタグ.
 */
typedef enum type_tag {
	TYPE_CLASS_T,
	TYPE_INTERFACE_T,
	TYPE_ENUM_T
} type_tag;

struct namespace_;
struct class_;
struct interface_;
struct field;
struct method;
struct property;
struct Enviroment;
struct vtable;
struct generic_type;

typedef enum type_state {
	/**
	 * 生成直後.
	 */
	TYPE_NONE = 1 << 0,
	/**
	 * 言語仕様のためにプリロードされるクラス.
	 * 後で正式に読み込まれるまで "保留" 状態とします。
	 */
	TYPE_PENDING = 1 << 1,
	/**
	 * 型宣言を発見し、名前空間へ登録されたことを示します.
	 */
	TYPE_REGISTER = 1 << 2,
	/**
	 * ある型のメンバ宣言を読み込んだことを示します.
	 */
	TYPE_DECL = 1 << 3,
	/**
	 * ある型のメンバ実装を読み込んだことを示します.
	 */
	TYPE_IMPL = 1 << 4
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
type* NewType();

/**
 * このタイプ自体を表すジェネリック型を初期化します.
 * @param self
 * @param count 型変数の個数
 * @return
 */
struct generic_type* InitGenericSelf(type* self, int counts);

/**
 * この型の名前を返します.
 * @param self
 * @return
 */
StringView GetTypeName(type* self);

/**
 * この型の完全な名前を返します.
 * @param self
 * @return
 */
StringView GetTypeFullName(type* self);

/**
 * この型にフィールドを追加します.
 * @param self
 * @param f
 */
void AddFieldType(type* self, struct field* f);

/**
 * この型にプロパティを追加します.
 * @param self
 * @param p
 */
void AddPropertyType(type* self, struct property* p);

/**
 * この型にメソッドを追加します.
 * @param self
 * @param m
 */
void AddMethodType(type* self, struct method* m);

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
struct method* ILFindMethodType(type* self, StringView namev, Vector* args, struct Enviroment* env, call_context* cctx, int* outIndex);

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
struct method* ILFindSMethodType(type* self, StringView namev, Vector* args, struct Enviroment* env, call_context* cctx, int* outIndex);

/**
 * 仮想関数の一覧を返します.
 * @param self
 * @return
 */
struct vtable* GetVTableType(type* self);

/**
 * 型の距離を返します.
 * @param super
 * @param sub
 * @return
 */
int DistanceType(type* super, type* sub);

/**
 * 型情報を残してメソッドやフィールドなどのみを開放します.
 * @param self
 */
void UnlinkType(type* self);

/**
 * 指定の名前の型変数が何番目に表れるかを返します.
 * @param self
 * @param namev
 * @return
 */
int GetGenericIndexType(type* self, StringView namev);

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
struct generic_type* FindImplementType(type* self, type* a);

/**
 * この型の型引数の一覧を返します.
 * @param self
 * @return
 */
Vector* GetParameterListType(type* self);

/**
 * この型の実装インターフェイスの一覧を返します.
 * @param self
 * @return
 */
Vector* GetImplementList(type* self);

/**
 * この型がクラス/インターフェイスを表すとき、
 * 指定位置の型変数を返します.
 * @param self
 * @param index
 * @return
 */
struct generic_type* TypeParameterAtType(type* self, int index);

/**
 * 型を開放します.
 * @param self
 */
void DeleteType(type* self);

/**
 * このタイプをクラスにキャストします.
 * @param self
 * @return
 */
struct class_* CastClassType(type* self);
/**
 * このタイプをインターフェイスにキャストします.
 * @param self
 * @return
 */
struct interface_* CastInterfaceType(type* self);

/**
 * abstractにはクラス/インターフェイスを渡します.
 * concreteの親クラス/実装インターフェイス一覧から abstract を検索し、 generic_type で返します。
 * @param abstract
 * @param concrete
 * @return
 */
struct generic_type* BaselineType(type* abstract, type* concrete);

/**
 * 同じインターフェイスが二回現れるなら NULL 以外.
 * @param self
 * @return
 */
struct interface_* IsValidInterface(type* self);

/**
 * 抽象クラスかインターフェイスなら true.
 * @param self
 * @return
 */
bool IsAbstractType(type* self);

/**
 * 可能なら self を class へ変換します.
 * 失敗したなら NULL
 * @param self
 * @return
 */
struct class_* TypeToClass(type* self);
/**
 * 可能なら self を interface へ変換します.
 * 失敗したなら NULL
 * @param self
 * @return
 */
struct interface_* TypeToInterface(type* self);
#endif // !SIGNAL_ENV_TYPE_INTERFACE_H

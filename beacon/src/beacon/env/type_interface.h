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
typedef enum TypeTag {
	TYPE_CLASS_T,
	TYPE_INTERFACE_T,
	TYPE_ENUM_T
} TypeTag;

struct Namespace;
struct class_;
struct interface_;
struct Field;
struct Method;
struct Property;
struct Enviroment;
struct VTable;
struct GenericType;

typedef enum TypeState {
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
} TypeState;

/**
 * 型を表す構造体.
 */
typedef struct Type {
	TypeTag Tag;
	struct Namespace* Location;
	struct GenericType* GenericSelf;
	int AbsoluteIndex;
	TypeState State;
	union {
		struct class_* Class;
		struct interface_* Interface;
	} Kind;
} Type;

/**
 * 型を作成します.
 * @return
 */
Type* NewType();

/**
 * このタイプ自体を表すジェネリック型を初期化します.
 * @param self
 * @param count 型変数の個数
 * @return
 */
struct GenericType* InitGenericSelf(Type* self, int counts);

/**
 * この型の名前を返します.
 * @param self
 * @return
 */
StringView GetTypeName(Type* self);

/**
 * この型の完全な名前を返します.
 * @param self
 * @return
 */
StringView GetTypeFullName(Type* self);

/**
 * この型にフィールドを追加します.
 * @param self
 * @param f
 */
void AddFieldType(Type* self, struct Field* f);

/**
 * この型にプロパティを追加します.
 * @param self
 * @param p
 */
void AddPropertyType(Type* self, struct Property* p);

/**
 * この型にメソッドを追加します.
 * @param self
 * @param m
 */
void AddMethodType(Type* self, struct Method* m);

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
struct Method* ILFindMethodType(Type* self, StringView namev, Vector* args, struct Enviroment* env, CallContext* cctx, int* outIndex);

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
struct Method* ILFindSMethodType(Type* self, StringView namev, Vector* args, struct Enviroment* env, CallContext* cctx, int* outIndex);

/**
 * 仮想関数の一覧を返します.
 * @param self
 * @return
 */
struct VTable* GetVTableType(Type* self);

/**
 * 型の距離を返します.
 * @param super
 * @param sub
 * @return
 */
int DistanceType(Type* super, Type* sub);

/**
 * 型情報を残してメソッドやフィールドなどのみを開放します.
 * @param self
 */
void UnlinkType(Type* self);

/**
 * 指定の名前の型変数が何番目に表れるかを返します.
 * @param self
 * @param namev
 * @return
 */
int GetGenericIndexType(Type* self, StringView namev);

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
struct GenericType* FindImplementType(Type* self, Type* a);

/**
 * この型の型引数の一覧を返します.
 * @param self
 * @return
 */
Vector* GetParameterListType(Type* self);

/**
 * この型の実装インターフェイスの一覧を返します.
 * @param self
 * @return
 */
Vector* GetImplementList(Type* self);

/**
 * この型がクラス/インターフェイスを表すとき、
 * 指定位置の型変数を返します.
 * @param self
 * @param index
 * @return
 */
struct GenericType* TypeParameterAtType(Type* self, int index);

/**
 * 型を開放します.
 * @param self
 */
void DeleteType(Type* self);

/**
 * このタイプをクラスにキャストします.
 * @param self
 * @return
 */
struct class_* CastClassType(Type* self);
/**
 * このタイプをインターフェイスにキャストします.
 * @param self
 * @return
 */
struct interface_* CastInterfaceType(Type* self);

/**
 * abstractにはクラス/インターフェイスを渡します.
 * concreteの親クラス/実装インターフェイス一覧から abstract を検索し、 GenericType で返します。
 * @param abstract
 * @param concrete
 * @return
 */
struct GenericType* BaselineType(Type* abstract, Type* concrete);

/**
 * 同じインターフェイスが二回現れるなら NULL 以外.
 * @param self
 * @return
 */
struct interface_* IsValidInterface(Type* self);

/**
 * 抽象クラスかインターフェイスなら true.
 * @param self
 * @return
 */
bool IsAbstractType(Type* self);

/**
 * 可能なら self を class へ変換します.
 * 失敗したなら NULL
 * @param self
 * @return
 */
struct class_* TypeToClass(Type* self);
/**
 * 可能なら self を interface へ変換します.
 * 失敗したなら NULL
 * @param self
 * @return
 */
struct interface_* TypeToInterface(Type* self);
#endif // !SIGNAL_ENV_TYPE_INTERFACE_H

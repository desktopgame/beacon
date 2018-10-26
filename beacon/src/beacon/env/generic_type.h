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
struct Method;
struct Enviroment;
struct virtual_type;
struct Frame;
struct CallContext;
/**
 * 型変数つきの型宣言の型引数では GenericType 自身が使われますが、
 * それ自体が型変数の場合、何の型変数を指しているかを示す列挙型です.
 */
typedef enum GenericTypeTag {
	GENERIC_TYPE_TAG_NONE_T,
	//クラスの型変数
	GENERIC_TYPE_TAG_CLASS_T,
	//メソッドの型変数
	GENERIC_TYPE_TAG_METHOD_T,
} GenericTypeTag;

/**
 * 型変数つきの型宣言.
 */
typedef struct GenericType {
	struct type* CoreType;
	Vector* TypeArgs;
	//このジェネリックタイプの紐づけたられたコンテナ
	union {
		struct type* type_;
		struct Method* method_;
	} u;
	//もしこの型が List<T> の Tを表すなら、
	//外側のクラスの何番目の型変数かを格納する。
	int VirtualTypeIndex;
	GenericTypeTag Tag;
	bool IsMark;
	bool IsCtor;
} GenericType;

//#define GenericType_validate(self) assert((self)->CoreType != NULL || self->VirtualTypeIndex != -1)

/**
 * 新しい型変数つきの型宣言を作成します.
 * @param ctype
 * @return
 */
#define generic_NewType(ctype) (MallocGenericType(ctype, __FILE__, __LINE__))

/**
 * CoreTypeがNULL以外なら generic_selfを参照し、
 * NULLなら新規作成します。
 * @param CoreType
 * @return
 */
GenericType* RefGenericType(struct type* CoreType);

/**
 * 新しい型変数つきの型宣言を作成します.
 * 通常はマクロ版の generic_NewType を使用します。
 * @param ctype
 * @return
 */
GenericType* MallocGenericType(struct type* CoreType, const char* filename, int lineno);

/**
 * ジェネリックタイプを複製します.
 * @param self
 * @return
 */
GenericType* CloneGenericType(GenericType* self);

/**
 * 現在のスクリプトコンテキストでどこからも参照されていない
 * GenericType の一覧を解放します。
 */
void CollectGenericType();

/**
 * type#generic_self を解放する時に使います.
 * CollectGenericType より後に呼び出してください。
 * @param a
 */
void LostownershipGenericType(GenericType* a);

/**
 * self の子要素として a を追加します.
 * @param self
 * @param a
 */
void AddArgsGenericType(GenericType* self, GenericType* a);

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
int DistanceGenericType(GenericType* self, GenericType* other, struct CallContext* cctx);
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
int RDistanceGenericType(GenericType* self, GenericType* other, struct Frame* fr);

/**
 * 型変数と型を出力します.
 * @param self
 */
void PrintGenericType(GenericType* self);

/**
 * ジェネリックタイプをオペコードとして出力します.
 * @param self
 * @param env
 * @param ilctx
 */
void GenerateGenericType(GenericType* self, struct Enviroment* env);

/**
 * 現在のコンテキストで self の型変数を解決します.
 * T ではなく T を内包する型(List<T>) などが戻り値になる時に使用されます。
 * @param self
 * @param cctx
 * @return
 */
GenericType* ApplyGenericType(GenericType* self, struct CallContext* cctx);
/**
 * 現在のコンテキストで self の型変数を解決します.
 * T ではなく T を内包する型(List<T>) などが戻り値になる時に使用されます。
 * @param self
 * @param fr
 * @return
 */
GenericType* RApplyGenericType(GenericType* self, struct CallContext* cctx, struct Frame* fr);

/**
 * GenericType を type へ変換します.
 * @param self
 * @return
 */
struct type* GenericTypeToType(GenericType* self);
#endif // !SIGNAL_ENV_GENERIC_TYPE_H

#pragma once
#ifndef BEACON_ENV_TYPE_IINTERFACE_H
#define BEACON_ENV_TYPE_IINTERFACE_H
#include "../type_interface.h"
#include "../namespace.h"
#include "../vtable.h"
#include "../../il/call_context.h"
#include "../../util/vector.h"
#include "../../util/string_pool.h"
#include "interface_validate.h"
struct Method;
struct Property;
struct Enviroment;
struct generic_type;
struct type;
/**
 * インターフェースを表す構造体.
 */
typedef struct interface_ {
	struct type* parent;
	StringView namev;
	Vector* impl_list;
	Vector* prop_list;
	Vector* method_list;
	Namespace* location;
	VTable* vt;
	Vector* GetParameterListType;
} interface_;

/**
 * インターフェイスをスーパーセットにラップします.
 * @param self
 * @return
 */
type* WrapInterface(interface_* self);

/** 
 * インターフェイスを作成します.
 * @param namev
 * @return
 */
interface_* NewInterface(StringView namev);

/**
 * インターフェイスにメソッドを追加します.
 * @param self
 * @param m
 */
void AddMethodInterface(interface_* self, struct Method* m);

/**
 * プロパティを追加します.
 * @param self
 * @param p
 */
void AddPropertyInterface(interface_* self, struct Property* p);

/**
 * インターフェイスからメソッドを検索します.
 * @param self
 * @param namev
 * @param args
 * @param env
 * @param cctx
 * @param outIndex
 * @return
 */
struct Method* ILFindMethodInterface(interface_* self, StringView namev, Vector * args, struct Enviroment * env, CallContext* cctx, int * outIndex);

/**
 * インターフェイスからメソッドを検索します.
 * @param self
 * @param namev
 * @param gargs
 * @param outIndex
 * @return
 */
struct Method* GFindMethodInterface(interface_* self, StringView namev, Vector* gargs, int* outIndex);

/**
 * 全てのインターフェイスに定義されたメソッドをフラットにして返します.
 * @param inter_list
 * @return
 */
Vector* FlattenMethodInterfaceList(Vector* inter_list);

/**
 * あるインターフェイスとそれ自体が実装しているインターフェイスの一覧の
 * メソッドを一つのリストにして返します.
 * @param self
 * @return 呼び出し側で開放してください
 */
Vector* FlattenMethodInterface(interface_* self);

/**
 * メソッドの一覧から VTable を作成します.
 * @param self
 */
void CreateVTableInterface(interface_* self);

/**
 * 型情報を残してメソッドやフィールドなどのみを開放します.
 * @param self
 */
void UnlinkInterface(interface_* self);

/**
 * インターフェイスを開放します.
 * @param self
 */
void DeleteInterface(interface_* self);

/**
 * self に find が含まれるなら NULL 以外の値を返します.
 * @param source
 * @param find
 * @return
 */
struct generic_type* IsContainsTypeInterface(struct generic_type* source, interface_* find);

/**
 * 関数型インターフェイスであるならtrue.
 * @param self
 * @return
 */
bool IsFunctionalInterface(interface_* self);

/**
 * 関数型インターフェイスであるなら一つだけ定義されたメソッドを返します.
 * @param self
 * @return
 */
struct Method* GetFunctionInterface(interface_* self);

/**
 * このインターフェイスを除く継承された全てのインターフェイスを返します.
 * @param self
 * @return
 */
Vector* GetGenericInterfaceTreeInterface(interface_* self);

/**
 * @param self
 * @param tiner
 * @param out_baseline
 * @return
 */
struct generic_type* FindInterfaceInterface(interface_* self, type* tinter);
#endif // !SIGNAL_ENV_TYPE_IINTERFACE_H

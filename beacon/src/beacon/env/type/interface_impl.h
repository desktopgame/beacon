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
struct GenericType;
struct Type;
/**
 * インターフェースを表す構造体.
 */
typedef struct Interface {
	struct Type* Parent;
	StringView Name;
	Vector* Implements;
	Vector* Properties;
	Vector* Methods;
	Namespace* Location;
	VTable* VT;
	Vector* TypeParameters;
} Interface;

/**
 * インターフェイスをスーパーセットにラップします.
 * @param self
 * @return
 */
Type* WrapInterface(Interface* self);

/** 
 * インターフェイスを作成します.
 * @param namev
 * @return
 */
Interface* NewInterface(StringView namev);

/**
 * インターフェイスにメソッドを追加します.
 * @param self
 * @param m
 */
void AddMethodInterface(Interface* self, struct Method* m);

/**
 * プロパティを追加します.
 * @param self
 * @param p
 */
void AddPropertyInterface(Interface* self, struct Property* p);

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
struct Method* ILFindMethodInterface(Interface* self, StringView namev, Vector * args, struct Enviroment * env, CallContext* cctx, int * outIndex);

/**
 * インターフェイスからメソッドを検索します.
 * @param self
 * @param namev
 * @param gargs
 * @param outIndex
 * @return
 */
struct Method* GFindMethodInterface(Interface* self, StringView namev, Vector* gargs, int* outIndex);

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
Vector* FlattenMethodInterface(Interface* self);

/**
 * メソッドの一覧から VTable を作成します.
 * @param self
 */
void CreateVTableInterface(Interface* self);

/**
 * 型情報を残してメソッドやフィールドなどのみを開放します.
 * @param self
 */
void UnlinkInterface(Interface* self);

/**
 * インターフェイスを開放します.
 * @param self
 */
void DeleteInterface(Interface* self);

/**
 * self に find が含まれるなら NULL 以外の値を返します.
 * @param source
 * @param find
 * @return
 */
struct GenericType* IsContainsTypeInterface(struct GenericType* source, Interface* find);

/**
 * 関数型インターフェイスであるならtrue.
 * @param self
 * @return
 */
bool IsFunctionalInterface(Interface* self);

/**
 * 関数型インターフェイスであるなら一つだけ定義されたメソッドを返します.
 * @param self
 * @return
 */
struct Method* GetFunctionInterface(Interface* self);

/**
 * このインターフェイスを除く継承された全てのインターフェイスを返します.
 * @param self
 * @return
 */
Vector* GetGenericInterfaceTreeInterface(Interface* self);

/**
 * @param self
 * @param tiner
 * @param out_baseline
 * @return
 */
struct GenericType* FindInterfaceInterface(Interface* self, Type* tinter);
#endif // !SIGNAL_ENV_TYPE_IINTERFACE_H

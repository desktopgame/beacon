//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file interface_impl.h
 * @brief インターフェイスを定義します。
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

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
struct bc_Method;
struct bc_Property;
struct Enviroment;
struct bc_GenericType;
struct bc_Type;
/**
 * インターフェースを表す構造体.
 */
typedef struct bc_Interface {
	struct bc_Type* Parent;
	StringView Name;
	Vector* Implements;
	Vector* Properties;
	Vector* Methods;
	bc_Namespace* Location;
	bc_VTable* VT;
	Vector* TypeParameters;
} bc_Interface;

/**
 * インターフェイスをスーパーセットにラップします.
 * @param self
 * @return
 */
bc_Type* bc_WrapInterface(bc_Interface* self);

/** 
 * インターフェイスを作成します.
 * @param namev
 * @return
 */
bc_Interface* bc_NewInterface(StringView namev);

/**
 * インターフェイスにメソッドを追加します.
 * @param self
 * @param m
 */
void bc_AddMethodInterface(bc_Interface* self, struct bc_Method* m);

/**
 * プロパティを追加します.
 * @param self
 * @param p
 */
void bc_AddPropertyInterface(bc_Interface* self, struct bc_Property* p);

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
struct bc_Method* bc_ILFindMethodInterface(bc_Interface* self, StringView namev, Vector * args, struct Enviroment * env, CallContext* cctx, int * outIndex);

/**
 * インターフェイスからメソッドを検索します.
 * @param self
 * @param namev
 * @param gargs
 * @param outIndex
 * @return
 */
struct bc_Method* bc_GFindMethodInterface(bc_Interface* self, StringView namev, Vector* gargs, int* outIndex);

/**
 * 全てのインターフェイスに定義されたメソッドをフラットにして返します.
 * @param inter_list
 * @return
 */
Vector* bc_FlattenMethodInterfaceList(Vector* inter_list);

/**
 * あるインターフェイスとそれ自体が実装しているインターフェイスの一覧の
 * メソッドを一つのリストにして返します.
 * @param self
 * @return 呼び出し側で開放してください
 */
Vector* bc_FlattenMethodInterface(bc_Interface* self);

/**
 * メソッドの一覧から VTable を作成します.
 * @param self
 */
void bc_CreateVTableInterface(bc_Interface* self);

/**
 * 型情報を残してメソッドやフィールドなどのみを開放します.
 * @param self
 */
void bc_UnlinkInterface(bc_Interface* self);

/**
 * インターフェイスを開放します.
 * @param self
 */
void bc_DeleteInterface(bc_Interface* self);

/**
 * self に find が含まれるなら NULL 以外の値を返します.
 * @param source
 * @param find
 * @return
 */
struct bc_GenericType* bc_IsContainsTypeInterface(struct bc_GenericType* source, bc_Interface* find);

/**
 * 関数型インターフェイスであるならtrue.
 * @param self
 * @return
 */
bool bc_IsFunctionalInterface(bc_Interface* self);

/**
 * 関数型インターフェイスであるなら一つだけ定義されたメソッドを返します.
 * @param self
 * @return
 */
struct bc_Method* bc_GetFunctionInterface(bc_Interface* self);

/**
 * このインターフェイスを除く継承された全てのインターフェイスを返します.
 * @param self
 * @return
 */
Vector* bc_GetGenericInterfaceTreeInterface(bc_Interface* self);

/**
 * @param self
 * @param tiner
 * @param out_baseline
 * @return
 */
struct bc_GenericType* bc_FindInterfaceInterface(bc_Interface* self, bc_Type* tinter);
#endif // !SIGNAL_ENV_TYPE_IINTERFACE_H

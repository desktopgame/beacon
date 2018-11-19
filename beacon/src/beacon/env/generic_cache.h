//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file generic_cache.h
 * @brief 型引数を含む型の完全名を表します。
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_ENV_GENERIC_CACHE_H
#define BEACON_ENV_GENERIC_CACHE_H
#include "fqcn_cache.h"
#include "../util/vector.h"

struct bc_GenericType;
struct bc_Type;
struct bc_Class;
struct bc_Interface;
struct bc_Namespace;

/**
 * 型変数を含む型の宣言.
 */
typedef struct bc_GenericCache {
	bc_FQCNCache* FQCN;
	Vector* TypeArgs;
} bc_GenericCache;

/**
 * 型変数を含む型宣言を作成します.
 * @return
 */
bc_GenericCache* bc_NewGenericCache();

/**
 * 型変数つきの型宣言をインデント無しで出力します.
 * @param self
 */
void bc_PrintGenericCache(bc_GenericCache* self);
/**
 * 型変数つきの型宣言をインデント付きで出力します.
 * @param self
 */
void bc_DumpGenericCache(bc_GenericCache* self, int depth);

/**
 * @param self
 * @return
 */
char* bc_GenericCacheToString(bc_GenericCache* self);

/**
 * 型変数つきの型宣言を解放します.
 * @param self
 */
void bc_DeleteGenericCache(bc_GenericCache* self);

/**
 * @param a
 * @param b
 * @return
 */
bool bc_EqualsGenericCache(bc_GenericCache* a, bc_GenericCache* b);
#endif // !SIGNAL_ENV_GENERIC_CACHE_H

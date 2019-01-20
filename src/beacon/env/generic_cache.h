// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file generic_cache.h
 * @brief 型引数を含む型の完全名を表します。
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_ENV_GENERIC_CACHE_H
#define BEACON_ENV_GENERIC_CACHE_H
#include "../util/vector.h"
#include "fqcn_cache.h"

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
        bc_Vector* TypeArgs;
} bc_GenericCache;

/**
 * 型変数を含む型宣言を作成します.
 * @return
 */
bc_GenericCache* bc_NewGenericCache();

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

#endif  // !SIGNAL_ENV_GENERIC_CACHE_H

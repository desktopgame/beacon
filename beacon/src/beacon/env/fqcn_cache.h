#pragma once
#ifndef BEACON_ENV_FQCN_CACHE_H
#define BEACON_ENV_FQCN_CACHE_H
#include "../util/vector.h"
#include "../util/string_pool.h"
struct namespace_;
struct type;
struct class_;
struct interface_;
//struct enviroment;
/**
 * Full Quality Class Name を表す構造体.
 */
typedef struct fqcn_cache {
	Vector* scope_vec;
	string_view namev;
} fqcn_cache;

/**
 * FQCNキャッシュを作成します.
 * @return
 */
#define fqcn_cache_new() (MallocFQCNCache(__FILE__, __LINE__))

/**
 * FQCNキャッシュを作成します.
 * @return
 */
fqcn_cache* MallocFQCNCache(const char* filename, int lineno);

/**
 * FQCNキャッシュを出力します.
 * @param self
 * @param depth
 */
void DumpFQCNCache(fqcn_cache* self, int depth);

/**
 * FQCNを切り詰めて改行せずに表示します.
 * @param self
 */
void PrintFQCNCache(fqcn_cache* self);

/**
 * FQCNが示す名前空間を返します.
 * X::Y ではなく、 Y の場合は NULL を返します。
 * @param self
 * @param current
 * @return
 */
struct namespace_* GetScopeFQCN(fqcn_cache* self, struct namespace_* current);

/**
 * X::Y の表すタイプを返します.
 * 絶対参照のときは引数 current は無視されます。
 * @param self
 * @param current
 * @return
 */
struct type* GetTypeFQCN(fqcn_cache* self, struct namespace_* current);

/**
 * X::Y の表すタイプを返します.
 * 絶対参照のときは引数 current は無視されます。
 * @param self
 * @param current
 * @return
 */
struct interface_* GetInterfaceFQCN(fqcn_cache* self, struct namespace_* current);

/**
 * X::Y の表すタイプを返します.
 * 絶対参照のときは引数 current は無視されます。
 * @param self
 * @param current
 * @return
 */
struct class_* GetClassFQCN(fqcn_cache* self, struct namespace_* current);

/**
 * 文字列に変換して返します.
 * @param self
 * @return
 */
char* FQCNCacheToString(fqcn_cache* self);

/**
 * FQCNキャッシュを開放します.
 * @param self
 */
void DeleteFQCNCache(fqcn_cache* self);

/**
 * 二つが同じなら true.
 * @param a
 * @param b
 * @return
 */
bool EqualsFQCNCache(fqcn_cache* a, fqcn_cache* b);
#endif // !SIGNAL_ENV_FQCN_CACHE_H

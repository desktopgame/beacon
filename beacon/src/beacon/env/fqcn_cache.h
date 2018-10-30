#pragma once
#ifndef BEACON_ENV_FQCN_CACHE_H
#define BEACON_ENV_FQCN_CACHE_H
#include "../util/vector.h"
#include "../util/string_pool.h"
struct Namespace;
struct Type;
struct Class;
struct Interface;
//struct Enviroment;
/**
 * Full Quality Class Name を表す構造体.
 */
typedef struct FQCNCache {
	Vector* Scope;
	StringView Name;
} FQCNCache;

/**
 * FQCNキャッシュを作成します.
 * @return
 */
#define FQCNCache_new() (MallocFQCNCache(__FILE__, __LINE__))

/**
 * FQCNキャッシュを作成します.
 * @return
 */
FQCNCache* MallocFQCNCache(const char* filename, int lineno);

/**
 * FQCNキャッシュを出力します.
 * @param self
 * @param depth
 */
void DumpFQCNCache(FQCNCache* self, int depth);

/**
 * FQCNを切り詰めて改行せずに表示します.
 * @param self
 */
void PrintFQCNCache(FQCNCache* self);

/**
 * FQCNが示す名前空間を返します.
 * X::Y ではなく、 Y の場合は NULL を返します。
 * @param self
 * @param current
 * @return
 */
struct Namespace* GetScopeFQCN(FQCNCache* self, struct Namespace* current);

/**
 * X::Y の表すタイプを返します.
 * 絶対参照のときは引数 current は無視されます。
 * @param self
 * @param current
 * @return
 */
struct Type* GetTypeFQCN(FQCNCache* self, struct Namespace* current);

/**
 * X::Y の表すタイプを返します.
 * 絶対参照のときは引数 current は無視されます。
 * @param self
 * @param current
 * @return
 */
struct Interface* GetInterfaceFQCN(FQCNCache* self, struct Namespace* current);

/**
 * X::Y の表すタイプを返します.
 * 絶対参照のときは引数 current は無視されます。
 * @param self
 * @param current
 * @return
 */
struct Class* GetClassFQCN(FQCNCache* self, struct Namespace* current);

/**
 * 文字列に変換して返します.
 * @param self
 * @return
 */
char* FQCNCacheToString(FQCNCache* self);

/**
 * FQCNキャッシュを開放します.
 * @param self
 */
void DeleteFQCNCache(FQCNCache* self);

/**
 * 二つが同じなら true.
 * @param a
 * @param b
 * @return
 */
bool EqualsFQCNCache(FQCNCache* a, FQCNCache* b);
#endif // !SIGNAL_ENV_FQCN_CACHE_H

#pragma once
#ifndef BEACON_ENV_TYPE_CACHE_H
#define BEACON_ENV_TYPE_CACHE_H
#include "../il/il_type_interface.h"
#include "type_interface.h"
#include "namespace.h"
struct class_loader;
//#include "class_loader.h"

/**
 * 何を読み込むためのキャッシュかを表す列挙型.
 */
typedef enum cache_kind {
	CACHEKIND_CLASS_DECL_T,
	CACHEKIND_CLASS_IMPL_T,

	CACHEKIND_INTERFACE_DECL_T,
	CACHEKIND_INTERFACE_IMPL_T,

	CACHEKIND_ENUM_DECL_T,
	CACHEKIND_ENUM_IMPL_T,
} cache_kind;

/**
 * クラスロード時に使用される一時的なキャッシュです.
 * signalクラスローダーは循環参照を正しく読み込むために、
 *
 * import先のファイルを解釈するときに
 * そのファイルの宣言情報だけを最初にロード(宣言ロード)して
 * import元のファイルへ戻ります。
 * import元のファイルをロードしたら上述のファイル全てで、
 * その実装情報をロードします。
 * つまり宣言ロード時に予約された実装の読み込みが必要な情報を表すキャッシュです。
 */
typedef struct type_cache {
	struct class_loader* context;
	il_type* iltype;
	type* tp;
	Namespace* scope;
	cache_kind kind;
	bool consume;
} type_cache;

type_cache* NewTypeCache();

type_cache * InitTypeCache(
	type_cache* self,
	struct class_loader* context,
	il_type* iltype,
	type* tp,
	Namespace* scope,
	cache_kind kind
	);

void DeleteTypeCache(type_cache* self);
#endif // !SIGNAL_ENV_TYPE_CACHE_H

#pragma once
#ifndef SIGNAL_ENV_TYPE_CACHE_H
#define SIGNAL_ENV_TYPE_CACHE_H
#include "../il/il_type_interface.h"
#include "type_interface.h"
#include "namespace.h"
#include "class_loader.h"

/**
 * 何を読み込むためのキャッシュかを表す列挙型.
 */
typedef enum cache_kind {
	cachekind_class_method,
	cachekind_interface_method,
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
	class_loader* context;
	il_type* iltype;
	type* tp;
	namespace_* scope;
	cache_kind kind;
} type_cache;

type_cache* type_cache_new();

type_cache * type_cache_init(
	type_cache* self,
	class_loader* context,
	il_type* iltype,
	type* tp,
	namespace_* scope,
	cache_kind kind
	);

void type_cache_delete(type_cache* self);
#endif // !SIGNAL_ENV_TYPE_CACHE_H

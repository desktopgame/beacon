#ifndef BEACON_ENV_LAZY_RESOLVE_H
#define BEACON_ENV_LAZY_RESOLVE_H
#include <stdbool.h>
struct default_eqoperator_resolve;
struct default_noteqoperator_resolve;

/**
 * 何を遅延解決するかを表すタグ.
 */
typedef enum lazy_resolve_tag {
	resolve_default_eqoperator,
	resolve_default_noteqoperator,
} lazy_resolve_tag;

/**
 * "遅延解決" のために一時的にキャッシュされる情報.
 * 例えば == != の演算子オーバーロードはどんなクラスであれ自動生成されますが、
 * これはユーザが定義していない場合に限るので遅延解決される必要があります。
 */
typedef struct lazy_resolve {
	lazy_resolve_tag tag;
	bool active;
	union {
		struct default_eqoperator_resolve* def_eqoperator;
		struct default_noteqoperator_resolve* def_noteqoperator;
//		struct default_operator_resolve* def_operator;
	} u;
} lazy_resolve;

/**
 * 新しい遅延解決キャッシュを生成します.
 * @param tag
 */
lazy_resolve* lazy_resolve_new(lazy_resolve_tag tag);

/**
 * 遅延解決を実行します.
 * @param self
 */
void lazy_resolve_apply(lazy_resolve* self);

/**
 * 遅延解決キャッシュを解放します.
 * @param self
 */
void lazy_resolve_delete(lazy_resolve* self);
#endif
#ifndef BEACON_ENV_LINK_TYPE_H
#define BEACON_ENV_LINK_TYPE_H
/**
 * クラスローダーの現在のリンク状態.
 */
typedef enum link_type {
	link_decl,
	link_impl,
	link_none,
} link_type;
#endif
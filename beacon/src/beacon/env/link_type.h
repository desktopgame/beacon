#ifndef BEACON_ENV_LINK_TYPE_H
#define BEACON_ENV_LINK_TYPE_H
/**
 * クラスローダーの現在のリンク状態.
 */
typedef enum link_type {
	link_decl_T,
	link_impl_T,
	link_none_T,
} link_type;
#endif
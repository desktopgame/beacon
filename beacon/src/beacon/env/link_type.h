#ifndef BEACON_ENV_LINK_TYPE_H
#define BEACON_ENV_LINK_TYPE_H
/**
 * クラスローダーの現在のリンク状態.
 */
typedef enum LinkType {
	LINK_DECL_T,
	LINK_IMPL_T,
	LINK_NONE_T,
} LinkType;
#endif
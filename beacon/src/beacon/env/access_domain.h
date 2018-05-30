#pragma once
#ifndef BEACON_ENV_ACCESS_DOMAIN_H
#define BEACON_ENV_ACCESS_DOMAIN_H
#include <stdbool.h>
#include "../ast/access_level.h"
#include "../ast/modifier_type.h"
/**
 * アクセス領域を表す列挙.
 * クラスからメンバーを検索するとき、どの要素を選択するかを指定するフラグ.
 */
typedef enum access_domain {
	domain_none,
	domain_public,
	domain_private,
	domain_protected
} access_domain;

/**
 * 指定のフラグが public を含むなら true.
 * @param a
 * @return
 */
bool domain_is_public(access_domain a);
/**
 * 指定のフラグが private を含むなら true.
 * @param a
 * @return
 */
bool domain_is_private(access_domain a);

/**
 * 指定のフラグが protected を含むなら true.
 * @param a
 * @return
 */
bool domain_is_protected(access_domain a);

#endif // !SIGNAL_ENV_ACCESS_DOMAIN_H

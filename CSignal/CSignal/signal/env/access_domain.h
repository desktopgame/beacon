#pragma once
#ifndef SIGNAL_ENV_ACCESS_DOMAIN_H
#define SIGNAL_ENV_ACCESS_DOMAIN_H
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
	domain_protected,
	domain_static,
	domain_native,
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

/**
 * 指定のフラグが static を含むなら true.
 * @param a
 * @return
 */
bool domain_is_static(access_domain a);
/**
 * 指定のフラグが native を含むなら true.
 * @param a
 * @return
 */
bool domain_is_native(access_domain a);

/**
 * 指定のドメイン空間で 引数の修飾子&アクセスレベル が許容されるならtrue.
 * @param self
 * @param m
 * @param a
 * @return
 */
bool domain_accept(access_domain self, modifier_type m, access_level a);
#endif // !SIGNAL_ENV_ACCESS_DOMAIN_H

#pragma once
#ifndef SIGNAL_AST_MODIFIER_TYPE_H
#define SIGNAL_AST_MODIFIER_TYPE_H
#include <stdbool.h>
/**
 * アクセス修飾子を表す列挙型.
 */
typedef enum modifier_type {
	modifier_none	= (1 << 0),
	modifier_static	= (1 << 1),
	modifier_native	= (1 << 2)
} modifier_type;
//typedef int modifier_type;
//const int modifier_none = (1 << 0);
//const int modifier_static = (1 << 1);
//const int modifier_native = (1 << 2);

/**
 * static | native を返します.
 * @return
 */
modifier_type modifier_static_native();

/**
 * 指定の修飾子が static を含むなら true.
 * @param type
 * @return
 */
bool modifier_is_static(modifier_type type);

/**
 * 指定の修飾子が native を含むなら true.
 * @param type
 * @return
 */
bool modifier_is_native(modifier_type type);

/**
 * 修飾子を出力します.
 * @param type
 */
void modifier_print(modifier_type type);
#endif // !SIGNAL_AST_MODIFIER_TYPE_H

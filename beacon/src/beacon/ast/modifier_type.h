#pragma once
#ifndef BEACON_AST_MODIFIER_TYPE_H
#define BEACON_AST_MODIFIER_TYPE_H
#include <stdbool.h>
/**
 * アクセス修飾子を表す列挙型.
 */
typedef enum modifier_type {
	modifier_none_T		= (1 << 0),
	modifier_static_T		= (1 << 1),
	modifier_native_T		= (1 << 2),
	modifier_abstract_T	= (1 << 3),
	modifier_override_T	= (1 << 4),
	modifier_final_T		= (1 << 5)
} modifier_type;

/**
 * 指定の修飾子が static を含むなら true.
 * @param type
 * @return
 */
bool IsStaticModifier(modifier_type type);

/**
 * 指定の修飾子が native を含むなら true.
 * @param type
 * @return
 */
bool IsNativeModifier(modifier_type type);

/**
 * 指定の修飾子が abstract を含むなら true.
 * @param type
 * @return
 */
bool IsAbstractModifier(modifier_type type);

/**
 * 指定の修飾子が override を含むなら true.
 * @param type
 * @return
 */
bool IsOverrideModifier(modifier_type type);

/**
 * @param type
 * @return
 */
bool IsFinalModifier(modifier_type type);

/**
 * 修飾子を出力します.
 * @param type
 */
void PrintModifier(modifier_type type);
#endif // !SIGNAL_AST_MODIFIER_TYPE_H

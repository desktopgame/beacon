#pragma once
#ifndef SIGNAL_AST_MODIFIER_TYPE_H
#define SIGNAL_AST_MODIFIER_TYPE_H
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
 * 修飾子を出力します.
 * @param type
 */
void modifier_print(modifier_type type);
#endif // !SIGNAL_AST_MODIFIER_TYPE_H

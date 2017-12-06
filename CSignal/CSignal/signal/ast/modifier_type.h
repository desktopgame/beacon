#pragma once
#ifndef SIGNAL_AST_MODIFIER_TYPE_H
#define SIGNAL_AST_MODIFIER_TYPE_H
/**
 * アクセス修飾子を表す列挙型.
 */
typedef enum modifier_type {
	modifier_type_public,
	modifier_type_private,
	modifier_type_protected,
	modifier_type_static,
	modifier_type_native,
} modifier_type;
#endif // !SIGNAL_AST_MODIFIER_TYPE_H

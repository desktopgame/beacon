#pragma once
#ifndef SIGNAL_AST_CONSTRUCTOR_CHAIN_TYPE_H
#define SIGNAL_AST_CONSTRUCTOR_CHAIN_TYPE_H
/**
 * コンストラクタの連鎖方法.
 */
typedef enum constructor_chain_type {
	chain_type_this,
	chain_type_super,
} constructor_chain_type;
#endif // !SIGNAL_AST_CONSTRUCTOR_CHAIN_TYPE_H

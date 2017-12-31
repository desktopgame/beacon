#pragma once
#ifndef SIGNAL_IL_IL_CONSTRUCTOR_CHAIN_H
#define SIGNAL_IL_IL_CONSTRUCTOR_CHAIN_H
#include "../util/vector.h"
/**
 * コンストラクタの連鎖方法.
 */
typedef enum ilchain_type {
	ilchain_super,
	ilchain_this
} ilchain_type;

/**
 * コンストラクタの連鎖を表す要素.
 */
typedef struct il_constructor_chain {
	ilchain_type type;
	vector* argument_list;
} il_constructor_chain;
/**
 * コンストラクタの連鎖を表す要素を作成します.
 * @return
 */
il_constructor_chain* il_constructor_chain_new();

/**
 * コンストラクタの連鎖を表す要素を開放します.
 * @param self
 */
void il_constructor_chain_delete(il_constructor_chain* self);
#endif // !SIGNAL_IL_IL_CONSTRUCTOR_CHAIN_H

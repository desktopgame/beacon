#pragma once
#ifndef BEACON_IL_IL_CONSTRUCTOR_CHAIN_H
#define BEACON_IL_IL_CONSTRUCTOR_CHAIN_H
#include "../util/vector.h"
#include "../ast/constructor_chain_type.h"
struct constructor;
/**
 * コンストラクタの連鎖を表す要素.
 */
typedef struct il_constructor_chain {
	constructor_chain_type type;
	Vector* argument_list;
	struct constructor* c;
	int constructor_index;
} il_constructor_chain;
/**
 * コンストラクタの連鎖を表す要素を作成します.
 * @return
 */
il_constructor_chain* NewILConstructorChain();

/**
 * コンストラクタの連鎖を表す要素を開放します.
 * @param self
 */
void DeleteILConstructorChain(il_constructor_chain* self);
#endif // !SIGNAL_IL_IL_CONSTRUCTOR_CHAIN_H

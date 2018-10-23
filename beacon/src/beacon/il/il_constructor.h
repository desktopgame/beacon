#pragma once
#ifndef BEACON_IL_IL_CONSTRUCTOR_H
#define BEACON_IL_IL_CONSTRUCTOR_H
#include "../env/fqcn_cache.h"
#include "../util/vector.h"
#include "../ast/access_level.h"
#include "../ast/modifier_type.h"
struct ILConstructorChain;
/**
 * コンストラクタを表す要素.
 */
typedef struct ILConstructor {
	//char* name;
	Vector* parameter_list;
	Vector* statement_list;
	struct ILConstructorChain* chain;
	//il_type* return_type;
	//fqcn_cache* return_fqcn;
	AccessLevel access;
	//ModifierType modifier;
} ILConstructor;

/**
 * コンストラクタを表す要素を作成します.
 * @return
 */
ILConstructor* NewILConstructor();

/**
 * コンストラクタを表す要素を開放します.
 * @param self
 */
void DeleteILConstructor(ILConstructor* self);
#endif // !SIGNAL_IL_IL_CONSTRUCTOR_H

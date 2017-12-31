#pragma once
#ifndef SIGNAL_IL_IL_CONSTRUCTOR_H
#define SIGNAL_IL_IL_CONSTRUCTOR_H
#include "il_type.h"
#include "../env/fqcn_cache.h"
#include "../util/vector.h"
#include "../ast/access_level.h"
#include "../ast/modifier_type.h"
struct il_constructor_chain;
/**
 * コンストラクタを表す要素.
 */
typedef struct il_constructor {
	//char* name;
	vector* parameter_list;
	vector* statement_list;
	struct il_constructor_chain* chain;
	//il_type* return_type;
	//fqcn_cache* return_fqcn;
	access_level access;
	//modifier_type modifier;
} il_constructor;

/**
 * コンストラクタを表す要素を作成します.
 * @return
 */
il_constructor* il_constructor_new();

/**
 * コンストラクタを表す要素を出力します.
 * @param self
 * @param depth;
 */
void il_constructor_dump(il_constructor* self, int depth);

/**
 * コンストラクタを表す要素を開放します.
 * @param self
 */
void il_constructor_delete(il_constructor* self);
#endif // !SIGNAL_IL_IL_CONSTRUCTOR_H

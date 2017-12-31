#pragma once
#ifndef SIGNAL_IL_IL_FIELD_H
#define SIGNAL_IL_IL_FIELD_H
#include "il_type.h"
#include "../ast/access_level.h"
#include "../ast/modifier_type.h"
#include "../env/fqcn_cache.h"
/**
 * フィールドを表す要素.
 */
typedef struct il_field {
	//il_type* type;
	fqcn_cache* fqcn;
	char* name;
	access_level access;
	modifier_type modifier;
} il_field;
/**
 * 新しいフィールドを作成します.
 * @param name
 * @return
 */
il_field* il_field_new(const char* name);

/**
 * フィールドを出力します.
 * @param self
 * @param depth
 */
void il_field_dump(il_field* self, int depth);

/**
 * フィールドを開放します.
 * @param self
 */
void il_field_delete(il_field* self);
#endif // !SIGNAL_IL_IL_FIELD_H

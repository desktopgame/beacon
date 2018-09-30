#pragma once
#ifndef BEACON_IL_IL_FIELD_H
#define BEACON_IL_IL_FIELD_H
#include "../ast/access_level.h"
#include "../ast/modifier_type.h"
#include "../util/string_pool.h"
//#include "../env/fqcn_cache.h"
struct generic_cache;
struct il_factor;
/**
 * フィールドを表す要素.
 */
typedef struct il_field {
	//il_type* type;
	struct generic_cache* fqcn;
	string_view namev;
	access_level access;
	modifier_type modifier;
	struct il_factor* initial_value;
} il_field;
/**
 * 新しいフィールドを作成します.
 * @param namev
 * @return
 */
il_field* NewILField(string_view namev);

/**
 * フィールドを開放します.
 * @param self
 */
void DeleteILField(il_field* self);
#endif // !SIGNAL_IL_IL_FIELD_H

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
typedef struct ILField {
	struct generic_cache* GCache;
	StringView Name;
	AccessLevel Access;
	ModifierType Modifier;
	struct il_factor* InitialValue;
} ILField;
/**
 * 新しいフィールドを作成します.
 * @param name
 * @return
 */
ILField* NewILField(StringView name);

/**
 * フィールドを開放します.
 * @param self
 */
void DeleteILField(ILField* self);
#endif // !SIGNAL_IL_IL_FIELD_H

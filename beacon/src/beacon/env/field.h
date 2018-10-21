#pragma once
#ifndef BEACON_ENV_FIELD_H
#define BEACON_ENV_FIELD_H
#include "../ast/access_level.h"
#include "../ast/modifier_type.h"
#include "../util/string_pool.h"
//#include "virtual_type.h"
struct type;
struct generic_type;
struct object;
struct Enviroment;
struct il_factor;
/**
 * フィールドを表す構造体.
 */
typedef struct field {
	StringView namev;
	struct type* parent;
	struct generic_type* gtype;
	struct object* static_value;
	AccessLevel access;
	modifier_type modifier;
	struct il_factor* initial_value;
	struct Enviroment* initial_value_env;
	bool not_initialized_at_ctor;
} field;

/**
 * 新しいフィールドを作成します.
 * @param namev
 * @return
 */
field* NewField(StringView namev);

/**
 * フィールドを開放します.
 * @param self
 */
void DeleteField(field* self);
#endif // !SIGNAL_ENV_FIELD_H

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
struct enviroment;
struct il_factor;
/**
 * フィールドを表す構造体.
 */
typedef struct field {
	string_view namev;
	struct type* parent;
	struct generic_type* gtype;
	struct object* static_value;
	access_level access;
	modifier_type modifier;
	struct il_factor* initial_value;
	struct enviroment* initial_value_env;
} field;

/**
 * 新しいフィールドを作成します.
 * @param namev
 * @return
 */
field* field_new(string_view namev);

/**
 * フィールドを開放します.
 * @param self
 */
void field_delete(field* self);
#endif // !SIGNAL_ENV_FIELD_H

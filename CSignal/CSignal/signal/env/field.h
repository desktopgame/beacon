#pragma once
#ifndef SIGNAL_ENV_FIELD_H
#define SIGNAL_ENV_FIELD_H
#include "../ast/access_level.h"
#include "../ast/modifier_type.h"
struct class_;
/**
 * フィールドを表す構造体.
 */
typedef struct field {
	char* name;
	struct class_* parent;
	struct class_* type;
	access_level access;
	modifier_type modifier;
} field;

/**
 * 新しいフィールドを作成します.
 * @param name
 * @return
 */
field* field_new(const char* name);

/**
 * フィールドを出力します.
 * @param self
 * @param depth
 */
void field_dump(field* self, int depth);

/**
 * フィールドを開放します.
 * @param self
 */
void field_delete(field* self);
#endif // !SIGNAL_ENV_FIELD_H

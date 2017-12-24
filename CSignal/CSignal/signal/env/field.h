#pragma once
#ifndef SIGNAL_ENV_FIELD_H
#define SIGNAL_ENV_FIELD_H
struct class_;
/**
 * フィールドを表す構造体.
 */
typedef struct field {
	char* name;
	struct class_* type;
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

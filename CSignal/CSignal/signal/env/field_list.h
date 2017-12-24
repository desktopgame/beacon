#pragma once
#ifndef SIGNAL_ENV_FIELD_LIST_H
#define SIGNAL_ENV_FIELD_LIST_H
#include "../util/list.h"

struct field;
/**
 * フィールドの一覧を表す型.
 */
typedef list field_list;

/**
 * フィールドの一覧を作成します.
 * @return
 */
field_list* field_list_new();

/**
 * フィールドを一覧に加えます.
 * @param self
 * @param child
 */
void field_list_push(field_list* self, struct field* child);

/**
 * フィールドの一覧を出力します.
 * @param self
 * @param depth
 */
void field_list_dump(field_list* self, int depth);

/**
 * フィールドの一覧を開放します.
 * @param self
 */
void field_list_delete(field_list* self);
#endif // !SIGNAL_ENV_FIELD_LIST_H

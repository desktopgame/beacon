#pragma once
#ifndef SIGNAL_IL_IL_FIELD_LIST_H
#define SIGNAL_IL_IL_FIELD_LIST_H
#include "il_field.h"
#include "../util/list.h"
/**
 * フィールドの一覧.
 */
typedef list il_field_list;

/**
 * フィールドの一覧を作成します.
 * @return
 */
il_field_list* il_field_list_new();

/**
 * フィールドを一覧に追加します.
 * @param self
 * @param field
 */
void il_field_list_push(il_field_list* self, il_field* field);

/**
 * フィールドの一覧を出力します.
 * @param self
 * @param depth
 */
void il_field_list_dump(il_field_list* self, int depth);

/**
 * フィールドの一覧を開放します.
 * @param self
 */
void il_field_list_delete(il_field_list* self);
#endif // !SIGNAL_IL_IL_FIELD_LIST_H

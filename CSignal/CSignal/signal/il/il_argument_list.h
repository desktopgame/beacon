#pragma once
#ifndef SIGNAL_IL_IL_ARGUMENT_LIST_H
#define SIGNAL_IL_IL_ARGUMENT_LIST_H
#include "il_argument.h"
#include "../util/list.h"
/**
 * 実引数の一覧を表す要素.
 */
typedef list il_argument_list;

/**
 * 実引数の一覧を表す要素を作成します.
 * @return
 */
il_argument_list* il_argument_list_new();

/**
 * 実引数の一覧に加えます.
 * @param self
 * @param child
 */
void il_argument_list_push(il_argument_list* self, il_argument* child);

/**
 * 実引数の一覧を出力します.
 * @param self
 * @param depth
 */
void il_argument_list_dump(il_argument_list* self, int depth);

/**
 * 実引数の一覧を開放します.
 * @param self
 */
void il_argument_list_delete(il_argument_list* self);
#endif // !SIGNAL_IL_IL_ARGUMENT_LIST_H

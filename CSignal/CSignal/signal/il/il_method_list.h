#pragma once
#ifndef SIGNAL_IL_IL_METHOD_LIST_H
#define SIGNAL_IL_IL_METHOD_LIST_H
#include "../util/list.h"
#include "il_method.h"
/**
 * メソッドの一覧を表す要素.
 */
typedef list il_method_list;
/**
 * メソッドの一覧を作成します.
 * @return
 */
il_method_list* il_method_list_new();

/**
 * メソッドの一覧に加えます.
 * @param self
 * @param child
 */
void il_method_list_push(il_method_list* self, il_method* child);

/**
 * メソッドの一覧を出力します.
 * @param self
 * @param depth
 */
void il_method_list_dump(il_method_list* self, int depth);

/**
 * メソッドの一覧を開放します.
 * @param self
 */
void il_method_list_delete(il_method_list* self);
#endif // !SIGNAL_IL_IL_METHOD_LIST_H

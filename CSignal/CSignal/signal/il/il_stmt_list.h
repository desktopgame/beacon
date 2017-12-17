#pragma once
#ifndef SIGNAL_IL_IL_STMT_LIST_H
#define SIGNAL_IL_IL_STMT_LIST_H
#include "../util/list.h"
#include "il_stmt_interface.h"

/**
 * ステートメントの一覧を表す要素.
 */
typedef list il_stmt_list;

/**
 * ステートメントの一覧を作成します.
 * @return
 */
il_stmt_list* il_stmt_list_new();

/** 
 * ステートメントの一覧に加えます.
 * @param self
 * @param child
 */
void il_stmt_list_push(il_stmt_list* self, il_stmt* child);

/**
 * ステートメントの一覧を出力します.
 * @param self
 * @param depth
 */
void il_stmt_list_dump(il_stmt_list* self, int depth);

/**
 * ステートメントの一覧を開放します.
 * @param self
 */
void il_stmt_list_delete(il_stmt_list* self);
#endif // !SIGNAL_IL_IL_STMT_LIST_H

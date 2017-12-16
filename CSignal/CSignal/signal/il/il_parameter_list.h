#pragma once
#ifndef SIGNAL_IL_IL_PARAMETER_LIST_H
#define SIGNAL_IL_IL_PARAMETER_LIST_H
#include "il_parameter.h"
#include "../util/list.h"
/**
 * パラメータの一覧を表す要素.
 */
typedef list il_parameter_list;
/**
 * パラメータの一覧を作成します.
 * @return
 */
il_parameter_list* il_parameter_list_new();

/**
 * パラメータの一覧に加えます.
 * @param self
 * @param param
 */
void il_parameter_list_push(il_parameter_list* self, il_parameter* param);

/**
 * パラメータの一覧を出力します.
 * @param self
 * @param depth
 */
void il_parameter_list_dump(il_parameter_list* self, int depth);

/**
 * パラメータの一覧を開放します.
 * @param self
 */
void il_parameter_list_delete(il_parameter_list* self);
#endif // !SIGNAL_IL_IL_PARAMETER_LIST_H

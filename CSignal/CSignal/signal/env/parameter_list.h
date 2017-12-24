#pragma once
#ifndef SIGNAL_ENV_PARAMETER_LIST_H
#define SIGNAL_ENV_PARAMETER_LIST_H
#include "../util/list.h"
struct parameter;

/**
 * パラメータの一覧を表す型です.
 */
typedef list parameter_list;

/**
 * パラメータの一覧を作成します.
 * @return
 */
parameter_list* parameter_list_new();

/**
 * パラメータを一覧に加えます.
 * @param self
 * @param child
 */
void parameter_list_push(parameter_list* self, struct parameter* child);

/**
 * パラメータの一覧を開放します.
 * @param self
 */
void parameter_list_delete(parameter_list* self);
#endif // !SIGNAL_ENV_PARAMETER_LIST_H

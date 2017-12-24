#pragma once
#ifndef SIGNAL_ENV_METHOD_LIST_H
#define SIGNAL_ENV_METHOD_LIST_H
#include "../util/list.h"

struct method;
/**
 * メソッドの一覧を表す型です.
 */
typedef list method_list;

/**
 * メソッドの一覧を作成します.
 * @return
 */
method_list* method_list_new();

/**
 * メソッドを一覧に加えます.
 * @param self
 * @param child
 */
void method_list_push(method_list* self, struct method* child);

/**
 * メソッドの一覧を出力します.
 * @param self
 * @param depth
 */
void method_list_dump(method_list* self, int depth);

/**
 * メソッドの一覧を開放します.
 * @param self
 */
void method_list_delete(method_list* self);
#endif // !SIGNAL_ENV_METHOD_LIST_H

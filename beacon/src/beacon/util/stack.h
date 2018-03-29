#pragma once
#ifndef BEACON_UTIL_STACK_H
#define BEACON_UTIL_STACK_H
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * スタックに格納出来るデータの型.
 */
typedef void* stack_item;

/**
 * スタックを表す構造体.
 */
typedef struct stack {
	stack_item item;
	struct stack* prev;
	struct stack* next;
} stack;

/**
 * スタックのデリータ関数です.
 * @param item
 */
typedef void(*stack_element_deleter)(stack_item item);

/**
 * 新しいスタックを作成します.
 * @return
 */
stack* stack_new(void);

/**
 * 末尾へ値を追加します.
 * @param self
 * @param item
 */
void stack_push(stack* self, stack_item item);

/**
 * 末尾の値を返しましす.
 * @param self
 * @return
 */
stack_item stack_top(stack* self);

/**
 * 末尾の値を返して削除します.
 * @param self
 * @return
 */
stack_item stack_pop(stack* self);

/**
 * スタックが空なら true.
 * @param self
 * @return
 */
bool stack_empty(stack* self);

/**
 * スタックとその中身を開放します.
 * @param self
 * @param deleter
 */
void stack_delete(stack* self, stack_element_deleter deleter);

/**
 * free によって解放するデリータです.
 * @param item
 */
void stack_deleter_free(stack_item item);

/**
 * 何も行わないデリータです.
 * @param item
 */
void stack_deleter_null(stack_item item);
#ifdef __cplusplus
};
#endif
#endif // !SIGNAL_UTIL_STACK_H

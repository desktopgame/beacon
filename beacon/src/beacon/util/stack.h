#pragma once
#ifndef BEACON_UTIL_STACK_H
#define BEACON_UTIL_STACK_H
#include <stdbool.h>

/**
 * スタックに格納出来るデータの型.
 */
typedef void* StackItem;

/**
 * スタックを表す構造体.
 */
typedef struct Stack_t {
	StackItem item;
	struct Stack_t* prev;
	struct Stack_t* next;
} Stack;

/**
 * スタックのデリータ関数です.
 * @param item
 */
typedef void(*StackElementDeleter)(StackItem item);

/**
 * 新しいスタックを作成します.
 * @return
 */
Stack* NewStack();

/**
 * 末尾へ値を追加します.
 * @param self
 * @param item
 */
void PushStack(Stack* self, StackItem item);

/**
 * 末尾の値を返しましす.
 * @param self
 * @return
 */
StackItem TopStack(Stack* self);

/**
 * 末尾の値を返して削除します.
 * @param self
 * @return
 */
StackItem PopStack(Stack* self);

/**
 * スタックが空なら true.
 * @param self
 * @return
 */
bool IsEmptyStack(Stack* self);

/**
 * スタックとその中身を開放します.
 * @param self
 * @param deleter
 */
void DeleteStack(Stack* self, StackElementDeleter deleter);

/**
 * free によって解放するデリータです.
 * @param item
 */
void StackDeleterByFree(StackItem item);

/**
 * 何も行わないデリータです.
 * @param item
 */
void StackDeleterOfNull(StackItem item);
#endif // !SIGNAL_UTIL_STACK_H

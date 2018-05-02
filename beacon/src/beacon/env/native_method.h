#pragma once
#ifndef BEACON_ENV_NATIVE_METHOD_H
#define BEACON_ENV_NATIVE_METHOD_H
struct native_method_ref;
struct enviroment;
struct method;
struct frame;
/**
 * Cで実装されたメソッド.
 */
typedef struct native_method {
	struct native_method_ref* ref;
} native_method;

/**
 * ネイティブメソッドを作成します.
 * @return
 */
native_method* native_method_new();

/**
 * ネイティブメソッドを実行します.
 * @param self
 * @param fr
 * @param env
 */
void native_method_execute(native_method* self, struct method* parent, struct frame* fr, struct enviroment* env);

/**
 * ネイティブメソッドを開放します.
 * @param self
 */
void native_method_delete(native_method* self);

/**
 * ネイティブメソッドの空実装.
 * @param parent
 * @param fr
 */
void native_method_empty(struct method* parent, struct frame* fr);
#endif // !SIGNAL_ENV_NATIVE_METHOD_H

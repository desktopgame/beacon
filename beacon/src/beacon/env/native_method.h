#pragma once
#ifndef BEACON_ENV_NATIVE_METHOD_H
#define BEACON_ENV_NATIVE_METHOD_H
struct NativeMethodRef;
struct Enviroment;
struct Method;
struct Frame;
/**
 * Cで実装されたメソッド.
 */
typedef struct NativeMethod {
	struct NativeMethodRef* ref;
} NativeMethod;

/**
 * ネイティブメソッドを作成します.
 * @return
 */
NativeMethod* NewNativeMethod();

/**
 * ネイティブメソッドを実行します.
 * @param self
 * @param fr
 * @param env
 */
void ExecuteNativeMethod(NativeMethod* self, struct Method* parent, struct Frame* fr, struct Enviroment* env);

/**
 * ネイティブメソッドを開放します.
 * @param self
 */
void DeleteNativeMethod(NativeMethod* self);

#endif // !SIGNAL_ENV_NATIVE_METHOD_H

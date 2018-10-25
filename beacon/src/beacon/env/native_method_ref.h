#pragma once
#ifndef BEACON_ENV_NATIVE_METHOD_REF_H
#define BEACON_ENV_NATIVE_METHOD_REF_H
#include "method.h"
#include "../vm/vm.h"
#include "../vm/enviroment.h"
#include <stdint.h>
/**
 * ネイティブメソッドの実装.
 */
typedef void(*native_impl)(Method* parent, Frame* vm, Enviroment* env);

/**
 * ネイティブメソッドを表す関数ポインタをラップする構造体.
 */
typedef struct NativeMethodRef {
	native_impl impl;
} NativeMethodRef;

/**
 * ラッパーを作成します.
 * @param impl
 * @return
 */
NativeMethodRef* NewNativeMethodRef(native_impl impl);

/**
 * ラッパーを開放します.
 * @param self
 */
void DeleteNativeMethodRef(NativeMethodRef* self);
#endif // !SIGNAL_ENV_NATIVE_METHOD_REF_H

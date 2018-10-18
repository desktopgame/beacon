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
typedef void(*native_impl)(method* parent, frame* vm, Enviroment* env);

/**
 * ネイティブメソッドを表す関数ポインタをラップする構造体.
 */
typedef struct native_method_ref {
	native_impl impl;
} native_method_ref;

/**
 * ラッパーを作成します.
 * @param impl
 * @return
 */
native_method_ref* NewNativeMethodRef(native_impl impl);

/**
 * ラッパーを開放します.
 * @param self
 */
void DeleteNativeMethodRef(native_method_ref* self);
#endif // !SIGNAL_ENV_NATIVE_METHOD_REF_H

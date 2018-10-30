#pragma once
#ifndef BEACON_LIB_SIGNAL_LANG_BOOL_H
#define BEACON_LIB_SIGNAL_LANG_BOOL_H
struct Type;

/**
 * beacon::lang::Boolクラスを初期化します.
 */
void InitBCBool();

/**
 * beacon::lang::Bool型を返します.
 * @return
 */
struct Type* GetBCBoolType();
#endif // !SIGNAL_LIB_SIGNAL_LANG_BOOL_H

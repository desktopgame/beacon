#pragma once
#ifndef BEACON_LIB_SIGNAL_LANG_H
#define BEACON_LIB_SIGNAL_LANG_H
struct Type;
/**
 * beacon::lang::Objectクラスを初期化します.
 */
void InitBCObject();

/**
 * beacon::lang::Object型を返します.
 */
struct Type* GetBCObjectType();
#endif // !SIGNAL_LIB_SIGNAL_LANG_H

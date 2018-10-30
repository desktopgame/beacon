#pragma once
#ifndef BEACON_LIB_SIGNAL_LANG_NULL_H
#define BEACON_LIB_SIGNAL_LANG_NULL_H
struct Type;
/**
 * beacon::lang::Nullクラスを初期化します.
 */
void InitBCNull();

/**
 * beacon::lang::Null型を返します.
 * @return
 */
struct Type* GetBCNullType();
#endif // !SIGNAL_LIB_SIGNAL_LANG_NULL_H

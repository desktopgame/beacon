#pragma once
#ifndef BEACON_LIB_SIGNAL_LANG_NULL_H
#define BEACON_LIB_SIGNAL_LANG_NULL_H
struct type;
/**
 * beacon::lang::Nullクラスを初期化します.
 */
void InitBCNull();

/**
 * beacon::lang::Null型を返します.
 * @return
 */
struct type* GetBCNullType();
#endif // !SIGNAL_LIB_SIGNAL_LANG_NULL_H

// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file system.h
 * @brief OSに依存する機能のラッパー。
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#ifndef BEACON_LIB_BEACON_BEACON_UNSAFE_BC_SYSTEM_H
#define BEACON_LIB_BEACON_BEACON_UNSAFE_BC_SYSTEM_H
/**
 * created by rbtools/rnative.rb
 * time: 2018-08-17
 */
struct bc_Type;

/**
 * beacon::unsafe::Systemクラスを初期化します。
 */
void bc_InitSystem();

/**
 * beacon::unsafe::Systemクラスを返します。
 * @return
 */
struct bc_Type* bc_GetSystemType();

#endif
#pragma once
#ifndef BEACON_LIB_SIGNAL_LANG_SG_CONSOLE_H
#define BEACON_LIB_SIGNAL_LANG_SG_CONSOLE_H
struct type;
/**
 * beacon::lang::Consoleクラスを初期化します.
 */
void bc_console_init();

/**
 * beacon::lang::Console型を返します.
 * @return
 */
struct type* bc_console_type();
#endif // !SIGNAL_LIB_SIGNAL_LANG_SG_CONSOLE_H

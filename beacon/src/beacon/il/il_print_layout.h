#pragma once
#ifndef BEACON_IL_PRINT_LAYOUT_H
#define BEACON_IL_PRINT_LAYOUT_H
#include <stdbool.h>

/**
 * 指定の行番号を出力する必要がないならtrue.
 * @param lineno
 * @return
 */
bool il_print_layout_lineno(int lineno);

/**
 * 必要に応じて行番号を表示します.
 * @param lineno
 */
void il_print_layout_form(int lineno);

/**
 * 行番号を表示しないならtrue.
 * @param is_hide
 */
void il_print_layout_hide(bool is_hide);
#endif // !SIGNAL_IL_PRINT_LAYOUT_H

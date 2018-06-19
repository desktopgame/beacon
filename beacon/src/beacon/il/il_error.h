#ifndef BEACON_IL_IL_ERROR_H
#define BEACON_IL_IL_ERROR_H
#include <stdarg.h>
#include <stdbool.h>
/**
 * エラー番号.
 */
typedef enum il_error_id {
	ilerror_undefined_class,
	ilerror_undefined_variable,
	ilerror_undefined_field,
	ilerror_undefined_method,
	ilerror_undefined_ctor,
	ilerror_undefined_operator,
	ilerror_end,
} il_error_id;

/**
 * エラーを報告します.
 * void il_error_vreport(il_error_id error_id, va_list ap)  のカバーメソッドです。
 * @param error_id
 * @param ...
 */
void il_error_report(il_error_id error_id, ...);

/**
 * エラーを報告します.
 * この関数を呼び出すとパニックフラグが true になります。
 * @param error_id
 * @param ap
 */
void il_error_vreport(il_error_id error_id, va_list ap);

/**
 * 新しいスコープを開始します.
 */
void il_error_enter();

/**
 * スコープを閉じます.
 */
void il_error_exit();

/**
 * 現在のスコープでパニックフラグをクリアします.
 */
void il_error_clear();

/**
 * 現在のスコープで現在のパニックフラグを返します.
 */
bool il_error_panic();

/**
 * 行番号を記録します.
 */
int il_error_line(int line);

/**
 * ファイル名を記録します.
 * @param filename
 * @return
 */
const char* il_error_file(const char* filename);
#endif
#pragma once
#ifndef SIGNA_IL_IL_EHANDLER_H
#define SIGNA_IL_IL_EHANDLER_H
#include <stdarg.h>
#include "../util/vector.h"


/**
 * クラスローダーがILの妥当性を検証するとき、
 * もし意味的にコンパイル出来ない式や呼び出しをこれに記録します。
 */
typedef struct il_ehandler {
	int errorCount;
	vector* message_vec;
} il_ehandler;

/**
 * エラーハンドラーを作成します.
 * @return
 */
il_ehandler* il_ehandler_new();

/**
 * エラーを記録します.
 * @param self
 * @param src
 * @param ...
 */
void il_ehandler_throw(il_ehandler* self, const char* src, ...);

/**
 * 全てのエラーメッセージを出力します.
 * @param self
 * @param depth
 */
void il_ehandler_disp(il_ehandler* self, int depth);

/**
 * エラーハンドラーを開放します.
 * @param self
 */
void il_ehandler_delete(il_ehandler* self);
#endif // !SIGNA_IL_IL_EHANDLER_H

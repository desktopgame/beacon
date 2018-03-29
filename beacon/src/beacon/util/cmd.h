#pragma once
#ifndef BEACON_UTIL_CMD_H
#define BEACON_UTIL_CMD_H
#include <stdbool.h>
#include <stdarg.h>
/**
 * コマンドラインによって表される一連のトークンを表す構造体.
 */
typedef struct cmd_line {
	int argc;
	int index;
} cmd_line;

/**
 * @param argc
 * @param argv
 * @return
 */
cmd_line* cmd_line_new(int argc);

/**
 * 次の文字列を返します.
 * @param self
 * @param argv
 * @return
 */
char* cmd_nexts(cmd_line* self, char* argv[]);

/**
 * 次の文字列を整数にして返します.
 * @param self
 * @param argv
 * @return
 */
int cmd_nexti(cmd_line* self, char* argv[]);

/**
 * 次の文字列を浮動小数にして返します.
 * @param self
 * @param argv
 * @return
 */
float cmd_nextf(cmd_line* self, char* argv[]);

/**
 * 次の文字列を真偽値にして返します.
 * @param self
 * @param argv
 * @return
 */
bool cmd_nextb(cmd_line* self, char* argv[]);

/**
 * 次の文字列が - から開始するならその部分を取り除いて返します.
 * @param self
 * @param argv
 * @return
 */
char* cmd_nextw(cmd_line* self, char* argv[]);

/**
 * 次の文字列が word と一致するなら true.
 * @param self
 * @param word
 * @return
 */
bool cmd_nexteq(cmd_line* self, char* argv[], char* word);

/**
 * @param self
 * @param argv
 * @param params
 * @param ...
 * @return
 */
bool cmd_nexteqany(cmd_line* self, char* argv[], int params, ...);

/**
 * コマンドを解釈して必要なオプションを設定します.
 * @param argc
 * @param argv
 */
void cmd_signal(int argc, char* argv[]);

/**
 * 実行時引数の一覧を出力します.
 * @param argc
 * @param argv
 */
void cmd_dump(int argc, const char* const argv[]);
#endif // !SIGNAL_UTIL_CMD_H

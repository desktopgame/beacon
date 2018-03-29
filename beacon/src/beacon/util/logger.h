#pragma once
#ifndef BEACON_UTIL_LOGGER_H
#define BEACON_UTIL_LOGGER_H
#include <stdarg.h>
#include <stdbool.h>

/**
 * ログのレベルを表す列挙.
 */
typedef enum log_level {
	log_debug,
	log_info,
	log_warn,
	log_error,
	log_fatal,
} log_level;

/**
 * ロガーの出力先となるファイルをオープンします.
 */
void logger_open();

/**
 * ロガーの出力先となるファイルをクローズします.
 */
void logger_close();

/**
 * ロガーの有効/非有効を設定します.
 * @param b 有効ならtrue.
 */
void logger_set_enabled(bool b);

/**
 * ロガーの有効/非有効を返します.
 * @return
 */
bool logger_is_enabled();

/**
 * 指定のフォーマット指定しと警告レベルで文字を表示します.
 * @param level
 * @param filename
 * @param lineno
 * @param source
 * @param ...
 */
void logger_log(log_level level, const char* filename, int lineno, const char* source, ...);

void logger_debug(const char* filename, int lineno, const char* source, ...);
void logger_info(const char* filename, int lineno, const char* source, ...);
void logger_warn(const char* filename, int lineno, const char* source, ...);
void logger_error(const char* filename, int lineno, const char* source, ...);
void logger_fatal(const char* filename, int lineno, const char* source, ...);

/**
 * 指定の条件を満たすならブレークします.
 * @param cond
 */
void logger_test(bool cond);

#define TEST(cond) logger_test(cond)
#define DEBUG(source) logger_log(log_debug, __FILE__, __LINE__, source)
#define INFO(source) logger_log(log_info, __FILE__, __LINE__, source)
#define WARN(source) logger_log(log_warn, __FILE__, __LINE__, source)
#define ERROR(source) logger_log(log_error, __FILE__, __LINE__, source)
#define FATAL(source) logger_log(log_fatal, __FILE__, __LINE__, source)

#endif // !SIGNAL_UTIL_LOGGER_H

#pragma once
#ifndef SIGNAL_UTIL_LOGGER_H
#define SIGNAL_UTIL_LOGGER_H
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

//マクロ名が被る場合は LOG_OVERRIDE を定義して既存のものを無効にします。
//(割と一般的な名前を使用しているので用意してます。)
#if defined(LOG_OVERRIDE)
#if defined(LOG)
#undef LOG
#endif

#if defined(INFO)
#undef INFO
#endif

#if defined(WARN)
#undef WARN
#endif

#if defined(ERROR)
#undef ERROR
#endif

#if defined(FATAL)
#undef FATAL
#endif
#endif
#define TEST(cond) logger_test(cond)
//ログ出力用マクロを無効にするには
//LOG_DISABLEを定義します。
#if !defined(LOG_DISABLE)
#if defined(__FILE__) && defined(__LINE__)

#define DEBUG(source) logger_log(log_debug, __FILE__, __LINE__, source)
#define INFO(source) logger_log(log_info, __FILE__, __LINE__, source)
#define WARN(source) logger_log(log_warn, __FILE__, __LINE__, source)
#define ERROR(source) logger_log(log_error, __FILE__, __LINE__, source)
#define FATAL(source) logger_log(log_fatal, __FILE__, __LINE__, source)

#else
#define DEBUG(source) sg_log(log_debug, "invalid", -1, source)
#define INFO(source) sg_log(log_info, "invalid", -1, source)
#define WARN(source) sg_log(log_warn, "invalid", -1, source)
#define ERROR(source) sg_log(log_error, "invalid", -1, source)
#define FATAL(source) sg_log(log_fatal, "invalid", -1, source)

#endif
#endif
#endif // !SIGNAL_UTIL_LOGGER_H

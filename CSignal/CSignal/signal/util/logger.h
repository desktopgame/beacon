#pragma once
#ifndef SIGNAL_UTIL_LOGGER_H
#define SIGNAL_UTIL_LOGGER_H
#include <stdarg.h>

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
void sg_lopen();

/**
 * ロガーの出力先となるファイルをクローズします.
 */
void sg_lclose();

/**
 * 指定のフォーマット指定しと警告レベルで文字を表示します.
 * @param level
 * @param filename
 * @param lineno
 * @param source
 * @param ...
 */
void sg_log(log_level level, const char* filename, int lineno, const char* source, ...);

//マクロ名が被る場合は LOG_OVERRIDE を定義して既存のものを無効にします。
//(割と一般的な名前を使用しているので用意してます。)
#if defined(LOG_OVERRIDE)
#if defined(DEBUG)
#undef DEBUG
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

//ログ出力用マクロを無効にするには
//LOG_DISABLEを定義します。
#if !defined(LOG_DISABLE)
#if defined(__FILE__) && defined(__LINE__)

#define DEBUG(source) sg_log(log_debug, __FILE__, __LINE__, source)
#define INFO(source) sg_log(log_info, __FILE__, __LINE__, source)
#define WARN(source) sg_log(log_warn, __FILE__, __LINE__, source)
#define ERROR(source) sg_log(log_error, __FILE__, __LINE__, source)
#define FATAL(source) sg_log(log_fatal, __FILE__, __LINE__, source)

#else
#define DEBUG(source) sg_log(log_debug, "invalid", -1, source)
#define INFO(source) sg_log(log_info, "invalid", -1, source)
#define WARN(source) sg_log(log_warn, "invalid", -1, source)
#define ERROR(source) sg_log(log_error, "invalid", -1, source)
#define FATAL(source) sg_log(log_fatal, "invalid", -1, source)

#endif
#endif
#endif // !SIGNAL_UTIL_LOGGER_H

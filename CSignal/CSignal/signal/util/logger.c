#include "logger.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
//#include <conio.h>
#include "text.h"
#include "io.h"

#if defined(_WIN32)
#include <Windows.h>
#endif

//proto
static char* sg_unique_name();
static void sg_print_loglevel(log_level level);
static void sg_fprint_loglevel(FILE* fp, log_level level);
static void sg_pretty_paint_start(log_level level);
static void sg_pretty_paint_stop();
static bool sg_is_error(log_level level);

static FILE* logger_fp = NULL;

#if defined(_WIN32)
static WORD savedInstance;
//https://stackoverflow.com/questions/9203362/c-color-text-in-terminal-applications-in-windows
//http://vivi.dyndns.org/tech/cpp/setColor.html
#define COL_BLACK 0x00
#define COL_DARK_BLUE 0x01
#define COL_DARK_GREEN 0x02
#define COL_DARK_CYAN 0x03
#define COL_DARK_RED 0x04
#define COL_DARK_VIOLET0x05
#define COL_DARK_YELLOW 0x06
#define COL_GRAY 0x07
#define COL_LIGHT_GRAY 0x08
#define COL_BLUE 0x09
#define COL_GREEN 0x0a
#define COL_CYAN 0x0b
#define COL_RED 0x0c
#define COL_VIOLET 0x0d
#define COL_YELLOW 0x0e
#define COL_WHITE 0x0f
#define COL_INTENSITY 0x08	// 高輝度マスク
#define COL_RED_MASK 0x04	// 赤色ビット
#define COL_GREEN_MASK 0x02	// 緑色ビット
#define COL_BLUE_MASK 0x01	//  青色ビット
#endif

void sg_lopen() {
	if (logger_fp != NULL) {
		return;
	}
	char* name = sg_unique_name();
	if (name == NULL) {
		logger_fp = NULL;
		return NULL;
	}
	if (!io_exists(name)) {
		io_new_file(name);
	}
#if defined(_MSC_VER)
	FILE* fp;
	errno_t e = fopen_s(&fp, name, "w");
	if (e) {
		free(name);
		return NULL;
	}
	free(name);
	logger_fp = fp;
	return e;
#else
	FILE* fp;
	fopen(fp, name, "w");
	free(name);
	logger_fp = fp;
	return fp;
#endif
}

void sg_lclose() {
	if (logger_fp != NULL) {
		fflush(logger_fp);
		fclose(logger_fp);
		logger_fp = NULL;
	}
}

//http://www.serendip.ws/archives/4635
void sg_log(log_level level, const char* filename, int lineno, const char * source, ...) {
#define LEN 100
	va_list ap;
	va_start(ap, source);
#ifdef _MSC_VER
	//ソース文字列をフォーマットする
	char buff[LEN];
	int res = sprintf_s(buff, LEN, source, ap);
#else
	char buff[LEN];
	int res = sprintf(buff, source, ap);
#endif
	//フォーマット失敗
	if (res == -1) {
		printf("internal error: %s %d %s", filename, lineno, source);
		//現在開いているファイルがあるなら書き出す
		if (logger_fp != NULL) {
#ifdef DEBUG
			//rewind(logger_fp);
			fprintf(logger_fp, "internal error: %s %d %s", filename, lineno, source);
			fputs("\n", logger_fp);
			fflush(logger_fp);
#endif
		}
	//フォーマット成功
	} else {
		sg_pretty_paint_start(level);
		sg_print_loglevel(level);
		printf("%s %d ", filename, lineno);
		printf(buff);
		sg_pretty_paint_stop();
		//現在開いているファイルがあるなら書き出す
		if (logger_fp != NULL) {
			//rewind(logger_fp);
#ifdef DEBUG
			sg_fprint_loglevel(logger_fp, level);
			fprintf(logger_fp, "%s %d ", filename, lineno);
			fprintf(logger_fp, buff);
			fputs("\n", logger_fp);
			fflush(logger_fp);
#endif
		}
	}
	va_end(ap);
	text_putline();
#undef LEN
}

//private
static char* sg_unique_name() {
	//http://www.c-tipsref.com/tips/time/time.html
#if defined(_MSC_VER)
	errno = 0;
	time_t timer = time(NULL);
	struct tm local;
	errno_t e = localtime_s(&local, &timer);
	if (e) {
		return NULL;
	}
	char buff[200];
	errno_t e2 = sprintf_s(
		buff, 
		200, 
		"log(%d-%d-%d-%d_%d_%d).txt",
		local.tm_year + 1900,
		local.tm_mon + 1,
		local.tm_mday,
		local.tm_hour,
		local.tm_min,
		local.tm_sec
	);
	if (e2) {
		//return NULL;
	}
	char* name = text_strdup(buff);
	return name;
#else
	return NULL;
#endif
}

static void sg_print_loglevel(log_level level) {
	switch (level) {
		case log_debug:
			printf("debug: ");
			break;
		case log_info:
			printf("info: ");
			break;
		case log_warn:
			printf("warn: ");
			break;
		case log_error:
			printf("error: ");
			break;
		case log_fatal:
			printf("fatal: ");
			break;
		default:
			break;
	}
}

static void sg_fprint_loglevel(FILE* fp, log_level level) {
	switch (level) {
		case log_debug:
			fprintf(fp, "debug: ");
			break;
		case log_info:
			fprintf(fp, "info: ");
			break;
		case log_warn:
			fprintf(fp, "warn: ");
			break;
		case log_error:
			fprintf(fp, "error: ");
			break;
		case log_fatal:
			fprintf(fp, "fatal: ");
			break;
		default:
			break;
	}
}

static void sg_pretty_paint_start(log_level level) {
#if defined(_WIN32)
	HANDLE h;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	//現在の設定をバックアップ
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(h, &csbi);
	savedInstance = csbi.wAttributes;
	//色を付ける
	switch (level) {
		case log_debug:
			SetConsoleTextAttribute(h, COL_WHITE);
			break;
		case log_info:
			SetConsoleTextAttribute(h, COL_GRAY);
			break;
		case log_warn:
			SetConsoleTextAttribute(h, COL_YELLOW);
			break;
		case log_error:
			SetConsoleTextAttribute(h, COL_RED);
			break;
		case log_fatal:
			SetConsoleTextAttribute(h, COL_RED);
			SetConsoleTextAttribute(h, COMMON_LVB_UNDERSCORE);
			break;
		default:
			break;
	}
#else
	switch (level) {
		case log_debug:
			printf("\x1b[37m");
			break;
		case log_info:
			printf("\x1b[37m");
			break;
		case log_warn:
			printf("\x1b[33m");
			break;
		case log_error:
			printf("\x1b[31m");
			break;
		case log_fatal:
			printf("\x1b[31m");
			printf("\x1b[4m");
			break;
		default:
			break;
	}
#endif // defined(_WIN32)
}

static void sg_pretty_paint_stop() {
#if defined(_WIN32)
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, savedInstance);
#else
	printf("\x1b[0m");
#endif
}

static bool sg_is_error(log_level level) {
	return level == log_warn ||
		level == log_error ||
		level == log_fatal;
}
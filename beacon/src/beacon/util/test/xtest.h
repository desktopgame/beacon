#ifndef BEACON_UTIL_TEST_XTEST_H
#define BEACON_UTIL_TEST_XTEST_H
#include "../vector.h"
#include "../string_buffer.h"
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>

#define REQ_TRUE(condition) xtest_expect_true(xtest_get(), condition, true, false, __FILE__, __LINE__, NULL)
#define REQ_FALSE(condition) xtest_expect_true(xtest_get(), !(condition), true, false, __FILE__, __LINE__, NULL)
#define REQ_EQ(a, b) xtest_expect_true(xtest_get(), ((a) == (b)), true, false, __FILE__, __LINE__, NULL)
#define REQ_STREQ(a, b) xtest_expect_true(xtest_get(), !strcmp((a), (b)), true, false, __FILE__, __LINE__, NULL)

#define MUST_TRUE(condition) xtest_expect_true(xtest_get(), condition, true, true, __FILE__, __LINE__, NULL)
#define MUST_FALSE(condition) xtest_expect_true(xtest_get(), !(condition), true, true, __FILE__, __LINE__, NULL)
#define MUST_EQ(a, b) xtest_expect_true(xtest_get(), ((a) == (b)), true, true, __FILE__, __LINE__, NULL)
#define MUST_STREQ(a, b) xtest_expect_true(xtest_get(), !strcmp((a), (b)), true, true, __FILE__, __LINE__, NULL)

/**
 * 実行されるテストの形式を表すポインタ.
 */
typedef void(*xtest_runner)(void);

/**
 * 実行されるテストとその名前のセット.
 */
typedef struct xtest {
	char* name;
	xtest_runner runner;
	vector* log_vec;
	string_buffer* out;
	bool error;
} xtest;

/**
 * テスト中に記録されたログ.
 */
typedef struct xlog {
	const char* filename;
	int lineno;
} xlog;

/**
 * 新しいテストを作成します.
 * @param name
 * @param runner
 * @return
 */
xtest* xtest_new(const char* name, xtest_runner runner);

/**
 * 新しいログを作成します.
 * @param filename
 * @param linenp
 * @return
 */
xlog* xlog_new(const char* filename, int lineno);

/**
 * このテストを実行します.
 * @param self
 * @return このテストをパスしたなら true.
 */
bool xtest_run(xtest* self);

/**
 * 現在のテスト構造体#out に フォーマットした文字列をバッファします.
 * ここでバッファされた文字列はテスト終了後にインデントと共に出力されます。
 * @param fmt
 * @param ...
 */
void xtest_printf(const char* fmt, ...);

/**
 * @see xtest_printf
 * @param fmt
 * @param ap
 */
void xtest_vprintf(const char* fmt, va_list ap);

/**
 * 現在テストを実行しているオブジェクトを返します.
 * @return
 */
xtest* xtest_get();

/**
 * condition が true でないなら記録します.
 * @param self
 * @param condition
 * @param isRecord
 * @param isThrow
 * @param filename
 * @param lineno
 * @param fmt
 * @return
 */
bool xtest_expect_true(xtest* self, bool condition, bool isRecord, bool isThrow, const char* filename, int lineno, const char* fmt, ...);

/**
 * condition が true でないなら記録します.
 * @param self
 * @param condition
 * @param isRecord
 * @param isThrow
 * @param filename
 * @param lineno
 * @param fmt
 * @param ap
 * @return
 */
bool xtest_expect_vtrue(xtest* self, bool condition, bool isRecord, bool isThrow, const char* filename, int lineno, const char* fmt, va_list ap);

/**
 * ファイル位置を記録しない代わりに、フォーマットを出力します.
 * @param condition
 * @param fmt
 * @param ...
 */
void xtest_request_true(bool condition, const char* fmt, ...);
void xtest_request_vtrue(bool condition, const char* fmt, va_list ap);

/**
 * ファイル位置を記録しない代わりに、フォーマットを出力します.
 * @param condition
 * @param fmt
 * @param ...
 */
void xtest_must_true(bool condition, const char* fmt, ...);
void xtest_must_vtrue(bool condition, const char* fmt, va_list ap);

/**
 * ログを解放します.
 * @param self
 */
void xlog_delete(xlog* self);

/**
 * テストを解放します.
 * @param self
 */
void xtest_delete(xtest* self);
#endif

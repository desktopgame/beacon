#ifndef BEACON_UTIL_TEST_XTEST_H
#define BEACON_UTIL_TEST_XTEST_H
#include "../vector.h"
#include <stdbool.h>
#include <string.h>

#define REQ_TRUE(condition) xtest_expect_true(xtest_get(), condition, false, __FILE__, __LINE__)
#define REQ_FALSE(condition) xtest_expect_true(xtest_get(), !(condition), false, __FILE__, __LINE__)
#define REQ_EQ(a, b) xtest_expect_true(xtest_get(), ((a) == (b)), false, __FILE__, __LINE__)
#define REQ_STREQ(a, b) xtest_expect_true(xtest_get(), !strcmp((a), (b)), false, __FILE__, __LINE__)

#define MUST_TRUE(condition) xtest_expect_true(xtest_get(), condition, true, __FILE__, __LINE__)
#define MUST_FALSE(condition) xtest_expect_true(xtest_get(), !(condition), true, __FILE__, __LINE__)
#define MUST_EQ(a, b) xtest_expect_true(xtest_get(), ((a) == (b)), true, __FILE__, __LINE__)
#define MUST_STREQ(a, b) xtest_expect_true(xtest_get(), !strcmp((a), (b)), true, __FILE__, __LINE__)

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
 * 現在テストを実行しているオブジェクトを返します.
 * @return
 */
xtest* xtest_get();

/**
 * condition が true でないなら記録します.
 * @param self
 * @param condition
 * @param isThrow
 * @param filename
 * @param lineno
 * @return
 */
bool xtest_expect_true(xtest* self, bool condition, bool isThrow, const char* filename, int lineno);

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

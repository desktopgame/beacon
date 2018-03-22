#ifndef BEACON_TEST_XTEST_GROUP_H
#define BEACON_TEST_XTEST_GROUP_H
#include "../vector.h"
#include <stdbool.h>
#include "xtest.h"

/**
 * テストの一覧.
 */
typedef struct xtest_group {
	char* name;
	vector* test_vec;
} xtest_group;

/**
 * テストの一覧を作成します.
 * @param name
 * @return
 */
xtest_group* xtest_group_new(char* name);

/**
 * 新しいテストを追加します.
 * @param self
 * @param name
 * @param runner
 */
void xtest_group_add(xtest_group* self, const char* name, xtest_runner runner);

/**
 * 全てのテストを実行します.
 * @param self
 * @return 全てのテストをパスしたなら true.
 */
bool xtest_group_run(xtest_group* self);

/**
 * テストの一覧を解放します.
 * @param self
 */
void xtest_group_delete(xtest_group* self);
#endif

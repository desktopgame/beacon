#ifndef BEACON_UTIL_XASSERT_H
#define BEACON_UTIL_XASSERT_H
#include <assert.h>
#include <stdbool.h>

#define XALWAYS() (xassert_break(true))
#define XBREAK(cond) (xassert_break(cond))
#define XBREAKSTREQ(a, b) (xassert_breakstreq(a, b))
#define XBREAKPTREQ(a, b) (xassert_breakptreq(a, b))

#define XSTREQ(a, b) (xassert_streq(a, b))
#define XMAX(a, b) (a > b ? a : b)
#define XMIN(a, b) (a < b ? a : b)

/**
 * conditionが true の時プログラムをブレークします.
 * @param condition
 * @return
 */
bool xassert_break(bool condition);

/**
 * a と b を文字列として比較して、同じならプログラムをブレークします.
 * @param a
 * @param b
 * @return
 */
bool xassert_breakstreq(const char* a, const char* b);

/**
 * a と b をポインタとして比較して、同じならプログラムをブレークします.
 * @param a
 * @param b
 * @return
 */
bool xassert_breakptreq(const void* a, const void* b);

/**
 * 文字列比較を条件としてアサートを実行します.
 * @param a
 * @param b
 * @return
 */
bool xassert_streq(const char* a, const char* b);
#endif

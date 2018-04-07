#pragma once
#ifndef BEACON_UTIL_BENCH_MARK_H
#define BEACON_UTIL_BENCH_MARK_H
#include <stdbool.h>
#include <time.h>

#if defined(_MSC_VER)
#include <sys/timeb.h>
#endif
/**
 * 時刻を表す構造体.
 */
typedef struct time_ref {
#if defined(_MSC_VER)
	struct timeb time;
#else
	time_t time;
#endif
} time_ref;
/**
 * 時刻の差分を表示するプリンタ関数.
 * @param name
 * @param befor
 * @param after
 */
typedef void(*time_printer)(const char* name, time_ref* befor, time_ref* after);

/**
 * ベンチマークを開始します.
 * 必ず対応する end を呼び出してください。
 * スタック構造を持っているので入れ子にできます。
 */
void bench_start();

/**
 * 最後に呼び出された start との差分を表示します.
 * @param name
 * @param printer
 */
void bench_end(const char* name, time_printer printer);

/**
 * 素朴なプリンタ関数の実装です.
 * ミリ秒単位で出力します。
 * @param name
 * @param befor
 * @param after
 */
void bench_simple(const char* name, time_ref* befor, time_ref* after);

/**
 * 現在時刻を time_ref でラップして返します.
 * @return
 */
time_ref* time_ref_get();

/**
 * time_ref を開放します.
 * @return
 */
void time_ref_delete(time_ref* self);
#endif // !SIGNAL_UTIL_BENCH_MARK_H

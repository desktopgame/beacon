#pragma once
#ifndef BEACON_VM_LINE_RANGE_H
#define BEACON_VM_LINE_RANGE_H
#include <stdint.h>
#include "../util/vector.h"

/**
 * オペコードのどこからどこまでが何行目なのかを表す構造体.
 */
typedef struct line_range {
	uint32_t start_offset;
	uint32_t end_offset;
	uint32_t lineno;
} line_range;
/**
 * 新しい範囲を作成します.
 * @return
 */
line_range* line_range_new();

/**
 * line_rangeの一覧から、指定の pc を含むレンジを返します.
 * @param line_rangeVec
 * @param pc
 * @return 見つからなければ NULL
 */
line_range* line_range_find(vector* line_rangeVec, int pc);

void line_range_delete(line_range* self);
#endif // !SIGNAL_VM_LINE_RANGE_H

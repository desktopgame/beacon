#pragma once
#ifndef SIGNAL_VM_LINE_RANGE_H
#define SIGNAL_VM_LINE_RANGE_H
#include <stdint.h>

/**
 * オペコードのどこからどこまでが何行目なのかを表す構造体.
 */
typedef struct line_range {
	uint32_t start_offset;
	uint32_t endOffset;
	uint32_t lineno;
} line_range;

line_range* line_range_new();

void line_range_delete(line_range* self);
#endif // !SIGNAL_VM_LINE_RANGE_H

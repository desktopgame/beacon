#pragma once
#ifndef BEACON_IL_OPERATOR_FIX_TYPE_H
#define BEACON_IL_OPERATOR_FIX_TYPE_H
/**
 * ++/-- の前置き/後置きを判別する列挙.
 */
typedef enum fix_type {
	fixtype_pre_T,
	fixtype_post_T
} fix_type;
#endif // !SIGNAL_IL_OPERATOR_FIX_TYPE_H

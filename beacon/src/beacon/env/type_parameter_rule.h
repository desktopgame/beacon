#pragma once
#ifndef BEACON_ENV_TYPE_PARAMETER_RULE_H
#define BEACON_ENV_TYPE_PARAMETER_RULE_H
#include "../util/vector.h"
struct generic_type;
struct il_type_parameter_rule;
struct il_context;

/**
 * 型変数に対する制約の種類を表す列挙型.
 */
typedef enum type_parameter_rule_tag {
	type_parameter_rule_tag_polymorphic,
	type_parameter_rule_tag_neweable,
} type_parameter_rule_tag;

/**
 * 型変数に対する制約を表す構造体.
 */
typedef struct type_parameter_rule {
	type_parameter_rule_tag tag;
	union {
		struct generic_type* gtype_;
	} u;
} type_parameter_rule;

/**
 * 新しい制約を作成します.
 * @return
 */
type_parameter_rule* type_parameter_rule_new();

/**
 * srcを複製します.
 * @param src
 * @param ilctx
 * @return
 */
type_parameter_rule* type_parameter_rule_dup(struct il_type_parameter_rule* src, struct il_context* ilctx);

/**
 * 全て複製します.
 * @param ilSource
 * @param sgDest
 * @param ilctx
 */
void type_parameter_rule_list_dup(vector* ilSource, vector* sgDest, struct il_context* ilctx);

/**
 * 全ての制約を出力します.
 * @param v
 */
void type_parameter_rule_list_print(vector* v);

/**
 * 型制約を解放します.
 * @param self
 */
void type_parameter_rule_delete(type_parameter_rule* self);
#endif // !SIGNAL_ENV_TYPE_PARAMETER_RULE_H

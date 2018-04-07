#pragma once
#ifndef BEACON_IL_IL_TYPE_PARAMETER_RULE_H
#define BEACON_IL_IL_TYPE_PARAMETER_RULE_H
#include "../env/generic_cache.h"
struct vector;

/**
 * 型引数に付与される製薬の種類を表す列挙型.
 */
typedef enum il_type_parameter_rule_tag {
	il_type_parameter_rule_polymorphic,
	il_type_parameter_rule_neweable,
} il_type_parameter_rule_tag;

/**
 * 型引数に対する制約を表す構造体.
 */
typedef struct il_type_parameter_rule {
	il_type_parameter_rule_tag tag;
	union {
		generic_cache* fqcn_;
	} u;
} il_type_parameter_rule;

/**
 * 新しい制約を作成します.
 * @return
 */
il_type_parameter_rule* il_type_parameter_rule_new();

/**
 * 制約の一覧を出力します.
 * @param v<il_type_parameter_rule>
 */
void il_type_parameter_rule_list_print(struct vector* v);

/**
 * 制約を解放します.
 * @param self
 */
void il_type_parameter_rule_delete(il_type_parameter_rule* self);
#endif // !SIGNAL_IL_IL_TYPE_PARAMETER_RULE_H

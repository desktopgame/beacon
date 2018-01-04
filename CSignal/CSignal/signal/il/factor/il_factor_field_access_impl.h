#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_FIELD_ACCESS_H
#define SIGNAL_IL_IL_FACTOR_FIELD_ACCESS_H
#include "../il_factor_interface.h"
struct enviroment;
struct class_;
struct field;

/**
 * フィールドアクセスを表す要素.
 */
typedef struct il_factor_field_access {
	il_factor* fact;
	char* name;
	struct field* f;
	int fieldIndex;
} il_factor_field_access;

/**
 * フィールドアクセスをスーパーセットにラップします.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_field_access(il_factor_field_access* self);

/**
 * フィールドアクセスを表す要素を作成します.
 * @param name
 * @return
 */
il_factor_field_access* il_factor_field_access_new(const char* name);

/**
 * フィールドアクセスを表す要素を出力します.
 * @param self
 * @param depth
 */
void il_factor_field_access_dump(il_factor_field_access* self, int depth);

/**
 * フィールドアクセスを表す要素を出力します.
 * @param self
 * @param env
 */
void il_factor_field_access_generate(il_factor_field_access* self, struct enviroment* env);

/**
 * フィールドアクセスを読み込みます.
 * @param self
 * @param env
 * @param eh
 */
void il_factor_field_access_load(il_factor_field_access* self, struct enviroment* env, il_ehandler* eh);

/**
 * フィールドアクセスの結果の型を返します.
 * @param self
 * @param env
 */
struct class_* il_factor_field_access_eval(il_factor_field_access* self, struct enviroment* env);

/**
 * フィールドアクセスを表す要素を開放します.
 * @param self
 */
void il_factor_field_access_delete(il_factor_field_access* self);
#endif // !SIGNAL_IL_IL_FACTOR_FIELD_ACCESS_H

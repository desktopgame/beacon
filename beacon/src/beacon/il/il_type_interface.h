#pragma once
#ifndef BEACON_IL_IL_TYPE_INTERFACE_H
#define BEACON_IL_IL_TYPE_INTERFACE_H
#include "../util/vector.h"
/**
 * 型の種類を判別する列挙.
 */
typedef enum il_type_tag {
	iltype_class,
	iltype_interface,
	iltype_enum,
} il_type_tag;

struct il_class;
struct il_interface;
struct il_enum;
struct il_field;
struct il_method;
struct il_constructor;

/**
 * 名前空間に含めることが出来る型.
 */
typedef struct il_type {
	il_type_tag tag;
	union {
		struct il_class* class_;
		struct il_interface* interface_;
		struct il_enum* enum_;
	} u;
} il_type;

/**
 * 型を作成します.
 * @return
 */
il_type* il_type_new();

/**
 * メソッドの一覧を返します.
 * @param self
 * @return
 */
vector* il_type_method_vec(il_type* self);

/**
 * 静的メソッドの一覧を返します.
 * @param self
 * @return
 */
vector* il_type_smethod_vec(il_type* self);

/**
 * コンストラクタを追加します.
 * @param self
 * @param ctor
 */
void il_type_add_constructor(il_type* self, struct il_constructor* ctor);

/**
 * フィールドを追加します.
 * @param self
 * @param field
 */
void il_type_add_field(il_type* self, struct il_field* field);

/**
 * メソッドを追加します.
 * @param self
 * @param field
 */
void il_type_add_method(il_type* self, struct il_method* method);

/**
 * 型を出力します.
 * @param self
 * @param depth
 */
void il_type_dump(il_type* self, int depth);

/**
 * 型を開放します.
 * @param self
 */
void il_type_delete(il_type* self);

/**
 * 型変数の一覧を返します.
 * @param self
 * @return
 */
vector* il_type_type_parameter_list(il_type* self);
#endif // !SIGNAL_IL_IL_TYPE_INTERFACE_H

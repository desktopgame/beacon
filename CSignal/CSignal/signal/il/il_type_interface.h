#pragma once
#ifndef SIGNAL_IL_IL_TYPE_INTERFACE_H
#define SIGNAL_IL_IL_TYPE_INTERFACE_H
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

/**
 * 名前空間に含めることが出来る型.
 */
typedef struct il_type {
	il_type_tag tag;
	union {
		struct il_class* class_;
		struct il_interface* interface_;
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
#endif // !SIGNAL_IL_IL_TYPE_INTERFACE_H

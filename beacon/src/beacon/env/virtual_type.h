#ifndef BEACON_ENV_VIRTUAL_TYPE_H
#define BEACON_ENV_VIRTUAL_TYPE_H
#include <stdbool.h>
#include "../il/il_context.h"
struct generic_type;
/**
 * 仮想型の種類を判別する列挙型.
 */
typedef enum virtual_type_tag {
	virtualtype_default,
	virtualtype_class_tv,
	virtualtype_method_tv,
} virtual_type_tag;

/**
 * 仮想型です.
 * これはフィールドやメソッドの引数/戻り値を表現するために使用されます。
 * コンパイラでは、非ジェネリックな型とジェネリックな型は区別して扱われますが、
 * それをこの仮想型としてラップします。
 */
typedef struct virtual_type {
	virtual_type_tag tag;
	union {
		struct generic_type* gtype;
		int index;
	} u;
} virtual_type;

void virtual_type_nongeneric_init(virtual_type* self, struct generic_type* gtype);

void virtual_type_class_init(virtual_type* self, int index);

void virtual_type_method_init(virtual_type* self, int index);

void virtual_type_print(const virtual_type* self);

bool virtual_type_eq(const virtual_type* a, const virtual_type* b);

bool virtual_type_void(virtual_type* self);

bool virtual_type_int(virtual_type* self);

bool virtual_type_double(virtual_type* self);

bool virtual_type_bool(virtual_type* self);

bool virtual_type_char(virtual_type* self);

bool virtual_type_null(virtual_type* self);

/**
 * self から現在のコンテキストで有効な generic_type を取得し、
 * generic_type_distanceの値を返します.
 * @param self
 * @param other
 * @param ilctx
 * @return
 */
int virtual_type_distance(virtual_type* self, struct generic_type* other, il_context* ilctx);

/**
 * メソッドの解決のために使用されます.
 * @param self
 * @param other
 * @param ilctx
 * @return
 */
int virtual_type_adistance(virtual_type* self, struct generic_type* other, il_context* ilctx);
#endif
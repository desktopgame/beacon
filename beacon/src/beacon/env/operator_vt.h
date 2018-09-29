#ifndef BEACON_ENV_OPERATOR_VT_H
#define BEACON_ENV_OPERATOR_VT_H
#include "../util/vector.h"
struct operator_overload;

/**
 * オペレータの仮想関数テーブル.
 */
typedef struct operator_vt {
	Vector* vec;
} operator_vt;

operator_vt* operator_vt_new();

void operator_vt_replace(operator_vt* self, struct operator_overload* opov);

void operator_vt_delete(operator_vt* self);
#endif
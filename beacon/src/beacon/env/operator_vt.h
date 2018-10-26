#ifndef BEACON_ENV_OPERATOR_VT_H
#define BEACON_ENV_OPERATOR_VT_H
#include "../util/vector.h"
struct OperatorOverload;

/**
 * オペレータの仮想関数テーブル.
 */
typedef struct operator_vt {
	Vector* vec;
} operator_vt;

operator_vt* NewOperatorVt();

void ReplaceOperatorVt(operator_vt* self, struct OperatorOverload* opov);

void DeleteOperatorVt(operator_vt* self);
#endif
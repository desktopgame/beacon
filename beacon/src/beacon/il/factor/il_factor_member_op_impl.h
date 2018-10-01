#ifndef BEACON_IL_IL_FACTOR_MEMBER_OP_H
#define BEACON_IL_IL_FACTOR_MEMBER_OP_H
#include "../../env/fqcn_cache.h"
#include "../../util/vector.h"
#include "../../util/string_pool.h"
#include "../../env/generic_cache.h"
#include "../il_factor_interface.h"

struct enviroment;
struct field;

/**
 * メンバアクセスを表す要素.
 */
typedef struct il_factor_member_op {
	il_factor* parent;
	il_factor* fact;
	string_view namev;
	Vector* type_args;
	int index;
	struct field* f;
} il_factor_member_op;

il_factor* WrapILMemberOp(il_factor_member_op* self);

il_factor_member_op* NewILMemberOp(string_view namev);

void LoadILMemberOp(il_factor_member_op* self, struct enviroment* env, call_context* cctx);

void GenerateILMemberOp(il_factor_member_op* self, struct enviroment* env, call_context* cctx);

generic_type* EvalILMemberOp(il_factor_member_op* self, struct enviroment* env, call_context* cctx);

char* ILMemberOpToString(il_factor_member_op* self, struct enviroment* env);

void DeleteILMemberOp(il_factor_member_op* self);

#endif
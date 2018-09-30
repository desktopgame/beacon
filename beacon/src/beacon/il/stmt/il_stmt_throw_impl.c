#include "il_stmt_throw_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include <stdio.h>

il_stmt* WrapILThrow(il_stmt_throw* self) {
	il_stmt* ret = il_stmt_new(ILSTMT_THROW_T);
	ret->u.throw_ = self;
	return ret;
}

il_stmt_throw* NewILThrow() {
	il_stmt_throw* ret = (il_stmt_throw*)MEM_MALLOC(sizeof(il_stmt_throw));
	ret->fact = NULL;
	return ret;
}

void il_stmt_throw_generate(il_stmt_throw* self, enviroment* env, call_context* cctx) {
	GenerateILFactor(self->fact, env, cctx);
	AddOpcodeBuf(env->buf, OP_THROW);
}

void LoadILThrow(il_stmt_throw* self, enviroment* env, call_context* cctx) {
	LoadILFactor(self->fact, env, cctx);
	generic_type* tgt = EvalILFactor(self->fact, env, cctx);
	if(generic_type_distance(GENERIC_EXCEPTION, tgt, cctx) < 0) {
		if(tgt->core_type != NULL) {
			ThrowBCError(
				BCERROR_THROWN_NOT_EXCEPTION_TYPE_T,
				Ref2Str(type_name(tgt->core_type))
			);
		}
	}
}

void DeleteILThrow(il_stmt_throw* self) {
	DeleteILFactor(self->fact);
	MEM_FREE(self);
}
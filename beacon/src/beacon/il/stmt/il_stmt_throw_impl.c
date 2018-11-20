#include "il_stmt_throw_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include <stdio.h>

ILStatement* WrapILThrow(ILThrow* self) {
	ILStatement* ret = NewILStatement(ILSTMT_THROW_T);
	ret->Kind.Throw = self;
	return ret;
}

ILThrow* NewILThrow() {
	ILThrow* ret = (ILThrow*)MEM_MALLOC(sizeof(ILThrow));
	ret->Factor = NULL;
	return ret;
}

void GenerateILThrow(ILThrow* self, bc_Enviroment* env, CallContext* cctx) {
	GenerateILFactor(self->Factor, env, cctx);
	bc_AddOpcodeBuf(env->Bytecode, OP_THROW);
}

void LoadILThrow(ILThrow* self, bc_Enviroment* env, CallContext* cctx) {
	LoadILFactor(self->Factor, env, cctx);
	bc_GenericType* tgt = EvalILFactor(self->Factor, env, cctx);
	if(bc_DistanceGenericType(BC_GENERIC_EXCEPTION, tgt, cctx) < 0) {
		if(tgt->CoreType != NULL) {
			bc_Panic(
				BCERROR_THROWN_NOT_EXCEPTION_TYPE_T,
				Ref2Str(bc_GetTypeName(tgt->CoreType))
			);
		}
	}
}

void DeleteILThrow(ILThrow* self) {
	DeleteILFactor(self->Factor);
	MEM_FREE(self);
}
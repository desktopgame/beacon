#include "il_factor_property_impl.h"
#include "../../util/mem.h"
#include "../../vm/enviroment.h"
#include "../../vm/generate.h"
#include "../../env/generic_type.h"
#include "../../env/field.h"
#include "../../env/TYPE_IMPL.h"
#include <assert.h>


il_factor_property* MallocILPropertyAccess(const char* filename, int lineno) {
	il_factor_property* ret = mem_malloc(sizeof(il_factor_property), filename, lineno);
	ret->fact = NULL;
	ret->index = -1;
	ret->namev = ZERO_VIEW;
	ret->p = NULL;
	return ret;
}

void il_factor_property_generate(il_factor_property* self, enviroment* env, call_context* cctx) {
	GenerateILFactor(self->fact, env, cctx);
	GenerateGetProperty(env->buf, self->p, self->index);
}

void LoadILProperty(il_factor_property* self, enviroment* env, call_context* cctx) {
	generic_type* receiver = EvalILFactor(self->fact, env, cctx);
	type* receiverT = GENERIC2TYPE(receiver);
	int temp = -1;
	class_find_property_tree(TYPE2CLASS(receiverT), self->p->namev, &temp);
	self->index = temp;
	if(temp == -1) {
		ThrowBCError(
			BCERROR_UNDEFINED_PROPERTY_T,
			Ref2Str(type_name(receiverT)),
			Ref2Str(self->namev)
		);
	}
}

generic_type* EvalILProperty(il_factor_property* self, enviroment* env, call_context* cctx) {
	return self->p->gtype;
}

char* ILPropertyToString(il_factor_property* self, enviroment* env) {
	string_buffer* sb = NewBuffer();
	char* name = ILFactorToString(self->fact, env);
	AppendsBuffer(sb, name);
	AppendBuffer(sb, '.');
	AppendsBuffer(sb, Ref2Str(self->namev));
	MEM_FREE(name);
	return ReleaseBuffer(sb);
}

void DeleteILPropertyAccess(il_factor_property* self) {
	DeleteILFactor(self->fact);
	MEM_FREE(self);
}
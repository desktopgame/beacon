#include "il_factor_property_impl.h"
#include "../../util/mem.h"
#include "../../vm/enviroment.h"
#include "../../vm/generate.h"
#include "../../env/generic_type.h"
#include "../../env/field.h"
#include "../../env/TYPE_IMPL.h"
#include <assert.h>


ILPropertyAccess* MallocILPropertyAccess(const char* filename, int lineno) {
	ILPropertyAccess* ret = bc_MXMalloc(sizeof(ILPropertyAccess), filename, lineno);
	ret->Source = NULL;
	ret->Index = -1;
	ret->Name = BC_ZERO_VIEW;
	ret->Property = NULL;
	return ret;
}

void GenerateILPropertyAccess(ILPropertyAccess* self, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_GenerateILFactor(self->Source, env, cctx);
	bc_GenerateGetProperty(env->Bytecode, self->Property, self->Index);
}

void LoadILProperty(ILPropertyAccess* self, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_GenericType* receiver = bc_EvalILFactor(self->Source, env, cctx);
	bc_Type* receiverT = bc_GENERIC2TYPE(receiver);
	int temp = -1;
	bc_FindTreePropertyClass(BC_TYPE2CLASS(receiverT), self->Property->Name, &temp);
	self->Index = temp;
	if(temp == -1) {
		bc_Panic(
			BCERROR_UNDEFINED_PROPERTY_T,
			bc_Ref2Str(bc_GetTypeName(receiverT)),
			bc_Ref2Str(self->Name)
		);
	}
}

bc_GenericType* EvalILProperty(ILPropertyAccess* self, bc_Enviroment* env, bc_CallContext* cctx) {
	return self->Property->GType;
}

char* ILPropertyToString(ILPropertyAccess* self, bc_Enviroment* env) {
	bc_Buffer* sb = bc_NewBuffer();
	char* name = bc_ILFactorToString(self->Source, env);
	bc_AppendsBuffer(sb, name);
	bc_AppendBuffer(sb, '.');
	bc_AppendsBuffer(sb, bc_Ref2Str(self->Name));
	MEM_FREE(name);
	return bc_ReleaseBuffer(sb);
}

void DeleteILPropertyAccess(ILPropertyAccess* self) {
	bc_DeleteILFactor(self->Source);
	MEM_FREE(self);
}
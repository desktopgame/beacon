#include "call_context.h"
#include "../util/mem.h"
#include "../env/namespace.h"
#include "../env/method.h"
#include "../env/type_interface.h"
#include "../env/TYPE_IMPL.h"
#include "../env/generic_type.h"
#include "../env/fqcn_cache.h"

CallContext* MallocCContext(CallFrameTag tag, const char* filename, int lineno) {
	CallContext* ret = bc_MXMalloc(sizeof(CallContext), filename, lineno);
#if defined(_MSC_VER)
	ControlStructure cs = { 0 };
#else
	ControlStructure cs = {};
#endif
	ret->CallStack = MallocVector(filename, lineno);
	ret->Scope = NULL;
	ret->Ty = NULL;
	ret->Tag = tag;
	ret->Control = cs;
	AllocControlStructure(&ret->Control);
	return ret;
}

CallFrame* PushImplCallContext(CallContext* self, CallFrameTag tag, const char* filename, int lineno) {
	CallFrame* fr = MallocCallFrame(tag, filename, lineno);
	PushVector(self->CallStack, fr);
	return fr;
}

CallFrame* TopCallContext(CallContext* self) {
	return TopVector(self->CallStack);
}

void PopCallContext(CallContext* self) {
	CallFrame* fr = PopVector(self->CallStack);
	DeleteCallFrame(fr);
}

bc_Namespace* GetNamespaceCContext(CallContext* self) {
	if(self->Scope != NULL) {
		return self->Scope;
	}
	return bc_GetLangNamespace();
}

bc_Method* GetMethodCContext(CallContext* self) {
	if(self->Tag != CALL_METHOD_T) {
		return NULL;
	}
	return self->Kind.Method;
}

bc_Type* GetTypeCContext(CallContext* self) {
	if(self->Tag == CALL_TOP_T) {
		return bc_FindTypeFromNamespace(bc_GetLangNamespace(), InternString("World"));
	}
	return self->Ty;
}

bc_Class* GetClassCContext(CallContext* self) {
	return BC_TYPE2CLASS(GetTypeCContext(self));
}

bc_GenericType* GetReceiverCContext(CallContext* self) {
	CallFrame* cfr = TopVector(self->CallStack);
	if(cfr->Tag == FRAME_INSTANCE_INVOKE_T) {
		return cfr->Kind.InstanceInvoke.Receiver;
	} else if(cfr->Tag == FRAME_SELF_INVOKE_T) {
		return self->Ty->GenericSelf;
	} else if(cfr->Tag == FRAME_RESOLVE_T) {
		return cfr->Kind.Resolve.GType;
	}
	return NULL;
}

bc_Type* GetEvalTypeCContext(CallContext* self, bc_FQCNCache* fqcn) {
	bc_Type* tp = bc_GetTypeFQCN(fqcn, self->Scope);
	if(tp == NULL) {
		tp = bc_GetTypeFQCN(fqcn, bc_GetLangNamespace());
	}
	return tp;
}

Vector* GetTypeArgsCContext(CallContext* self) {
	CallFrame* cfr = TopVector(self->CallStack);
	if(cfr->Tag == FRAME_INSTANCE_INVOKE_T) {
		return cfr->Kind.InstanceInvoke.TypeArgs;
	} else if(cfr->Tag == FRAME_STATIC_INVOKE_T) {
		return cfr->Kind.StaticInvoke.TypeArgs;
	} else if(cfr->Tag == FRAME_SELF_INVOKE_T) {
		return cfr->Kind.SelfInvoke.TypeArgs;
	} else if(cfr->Tag == FRAME_RESOLVE_T) {
		return cfr->Kind.Resolve.TypeArgs;
	}
	return NULL;
}

bool IsStaticCContext(CallContext* self) {
	return self->Tag == CALL_METHOD_T &&
	       bc_IsStaticModifier(self->Kind.Method->Modifier);
}

void DeleteCallContext(CallContext* self) {
	FreeControlStructure(self->Control);
	DeleteVector(self->CallStack, VectorDeleterOfNull);
	MEM_FREE(self);
}
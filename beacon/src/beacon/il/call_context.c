#include "call_context.h"
#include "../util/mem.h"
#include "../env/namespace.h"
#include "../env/method.h"
#include "../env/type_interface.h"
#include "../env/TYPE_IMPL.h"
#include "../env/generic_type.h"
#include "../env/fqcn_cache.h"

call_context* MallocCContext(CallFrameTag tag, const char* filename, int lineno) {
	call_context* ret = mem_malloc(sizeof(call_context), filename, lineno);
#if defined(_MSC_VER)
	ControlStructure cs = { 0 };
#else
	ControlStructure cs = {};
#endif
	ret->call_stack = MallocVector(filename, lineno);
	ret->scope = NULL;
	ret->ty = NULL;
	ret->tag = tag;
	ret->control = cs;
	AllocControlStructure(&ret->control);
	return ret;
}

call_frame* PushImplCallContext(call_context* self, CallFrameTag tag, const char* filename, int lineno) {
	call_frame* fr = MallocCallFrame(tag, filename, lineno);
	PushVector(self->call_stack, fr);
	return fr;
}

call_frame* TopCallContext(call_context* self) {
	return TopVector(self->call_stack);
}

void PopCallContext(call_context* self) {
	call_frame* fr = PopVector(self->call_stack);
	DeleteCallFrame(fr);
}

namespace_* GetNamespaceCContext(call_context* self) {
	if(self->scope != NULL) {
		return self->scope;
	}
	return GetLangNamespace();
}

method* GetMethodCContext(call_context* self) {
	if(self->tag != CALL_METHOD_T) {
		return NULL;
	}
	return self->u.mt;
}

type* GetTypeCContext(call_context* self) {
	if(self->tag == CALL_TOP_T) {
		return FindTypeFromNamespace(GetLangNamespace(), InternString("World"));
	}
	return self->ty;
}

class_* GetClassCContext(call_context* self) {
	return TYPE2CLASS(GetTypeCContext(self));
}

generic_type* GetReceiverCContext(call_context* self) {
	call_frame* cfr = TopVector(self->call_stack);
	if(cfr->tag == FRAME_INSTANCE_INVOKE_T) {
		return cfr->u.instance_invoke.receiver;
	} else if(cfr->tag == FRAME_SELF_INVOKE_T) {
		return self->ty->generic_self;
	} else if(cfr->tag == FRAME_RESOLVE_T) {
		return cfr->u.resolve.GType;
	}
	return NULL;
}

type* GetEvalTypeCContext(call_context* self, fqcn_cache* fqcn) {
	type* tp = GetTypeFQCN(fqcn, self->scope);
	if(tp == NULL) {
		tp = GetTypeFQCN(fqcn, GetLangNamespace());
	}
	return tp;
}

Vector* GetTypeArgsCContext(call_context* self) {
	call_frame* cfr = TopVector(self->call_stack);
	if(cfr->tag == FRAME_INSTANCE_INVOKE_T) {
		return cfr->u.instance_invoke.typeargs;
	} else if(cfr->tag == FRAME_STATIC_INVOKE_T) {
		return cfr->u.static_invoke.typeargs;
	} else if(cfr->tag == FRAME_SELF_INVOKE_T) {
		return cfr->u.self_invoke.TypeArgs;
	} else if(cfr->tag == FRAME_RESOLVE_T) {
		return cfr->u.resolve.TypeArgs;
	}
	return NULL;
}

bool IsStaticCContext(call_context* self) {
	return self->tag == CALL_METHOD_T &&
	       IsStaticModifier(self->u.mt->modifier);
}

void DeleteCallContext(call_context* self) {
	FreeControlStructure(self->control);
	DeleteVector(self->call_stack, VectorDeleterOfNull);
	MEM_FREE(self);
}
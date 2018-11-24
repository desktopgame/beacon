#include "call_context.h"
#include "../env/TYPE_IMPL.h"
#include "../env/fqcn_cache.h"
#include "../env/generic_type.h"
#include "../env/method.h"
#include "../env/namespace.h"
#include "../env/type_interface.h"
#include "../util/mem.h"

bc_CallContext* bc_NewCallContext(bc_CallContextTag tag) {
        bc_CallContext* ret = MEM_MALLOC(sizeof(bc_CallContext));
#if defined(_MSC_VER)
        bc_ControlStructure cs = {0};
#else
        bc_ControlStructure cs = {};
#endif
        ret->CallStack = bc_NewVector();
        ret->Scope = NULL;
        ret->Ty = NULL;
        ret->Tag = tag;
        ret->Control = cs;
        bc_AllocControlStructure(&ret->Control);
        return ret;
}

bc_CallContext* bc_NewTopContext(bc_Type* worldType) {
        bc_CallContext* ret = bc_NewCallContext(CALL_TOP_T);
        ret->Scope = bc_GetLangNamespace();
        ret->Ty = worldType;
        return ret;
}

bc_CallFrame* bc_PushCallContext(bc_CallContext* self, bc_GenericType* receiver,
                                 bc_Vector* args, bc_Vector* type_args) {
        bc_CallFrame* fr = bc_NewCallFrame(receiver, args, type_args);
        bc_PushVector(self->CallStack, fr);
        return fr;
}

bc_CallFrame* bc_TopCallContext(bc_CallContext* self) {
        return bc_TopVector(self->CallStack);
}

void bc_PopCallContext(bc_CallContext* self) {
        bc_CallFrame* fr = bc_PopVector(self->CallStack);
        bc_DeleteCallFrame(fr);
}

bc_Namespace* bc_GetNamespaceCContext(bc_CallContext* self) {
        if (self->Scope != NULL) {
                return self->Scope;
        }
        return bc_GetLangNamespace();
}

bc_Method* bc_GetMethodCContext(bc_CallContext* self) {
        if (self->Tag != CALL_METHOD_T) {
                return NULL;
        }
        return self->Kind.Method;
}

bc_Type* bc_GetTypeCContext(bc_CallContext* self) {
        if (self->Tag == CALL_TOP_T) {
                return bc_FindTypeFromNamespace(bc_GetLangNamespace(),
                                                bc_InternString("World"));
        }
        return self->Ty;
}

bc_Class* bc_GetClassCContext(bc_CallContext* self) {
        return BC_TYPE2CLASS(bc_GetTypeCContext(self));
}

bc_GenericType* bc_GetReceiverCContext(bc_CallContext* self) {
        bc_CallFrame* cfr = bc_TopVector(self->CallStack);
        return cfr->Receiver;
}

bc_Type* bc_GetEvalTypeCContext(bc_CallContext* self, bc_FQCNCache* fqcn) {
        bc_Type* tp = bc_GetTypeFQCN(fqcn, self->Scope);
        if (tp == NULL) {
                tp = bc_GetTypeFQCN(fqcn, bc_GetLangNamespace());
        }
        return tp;
}

bc_Vector* bc_GetTypeArgsCContext(bc_CallContext* self) {
        bc_CallFrame* cfr = bc_TopVector(self->CallStack);
        return cfr->TypeArgs;
}

bool bc_IsStaticCContext(bc_CallContext* self) {
        return self->Tag == CALL_METHOD_T &&
               bc_IsStaticModifier(BC_MEMBER_MODIFIER(self->Kind.Method));
}

void bc_DeleteCallContext(bc_CallContext* self) {
        bc_FreeControlStructure(self->Control);
        bc_DeleteVector(self->CallStack, bc_VectorDeleterOfNull);
        MEM_FREE(self);
}
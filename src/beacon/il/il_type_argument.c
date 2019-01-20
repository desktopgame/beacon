#include "il_type_argument.h"
#include "../env/class_loader.h"
#include "../env/import_manager.h"
#include "../env/namespace.h"
#include "../il/call_context.h"
#include "../util/mem.h"
#include "../util/text.h"

bc_ILTypeArgument* bc_NewILTypeArgument() {
        bc_ILTypeArgument* ret =
            (bc_ILTypeArgument*)MEM_MALLOC(sizeof(bc_ILTypeArgument));
        ret->GCache = bc_NewGenericCache();
        ret->GType = NULL;
        return ret;
}

void bc_ResolveILTypeArgument(bc_Vector* iltype_args, bc_CallContext* cctx) {
        for (int i = 0; i < iltype_args->Length; i++) {
                bc_ILTypeArgument* e =
                    (bc_ILTypeArgument*)bc_AtVector(iltype_args, i);
                if (e->GType == NULL) {
                        //		Namespace* scope = cc_namespace(
                        e->GType = bc_ResolveImportManager(cctx->Scope,
                                                           e->GCache, cctx);
                        // assert(e->gtype->CoreType != NULL ||
                        // e->gtype->VirtualTypeIndex != -1);
                }
        }
}

void bc_DeleteILTypeArgument(bc_ILTypeArgument* self) {
        bc_DeleteGenericCache(self->GCache);
        MEM_FREE(self);
}
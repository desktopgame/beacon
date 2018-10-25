#include "il_type_argument.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../env/namespace.h"
#include "../env/class_loader.h"
#include "../env/import_manager.h"
#include "../il/call_context.h"

ILTypeArgument* NewILTypeArgument() {
	ILTypeArgument* ret = (ILTypeArgument*)MEM_MALLOC(sizeof(ILTypeArgument));
	ret->GCache = NewGenericCache();
	ret->GType = NULL;
	return ret;
}

void PrintILTypeArgument(Vector* iltype_args) {
	if(iltype_args->Length == 0) {
		return;
	}
	printf("<");
	for(int i=0; i<iltype_args->Length; i++) {
		ILTypeArgument* e = (ILTypeArgument*)AtVector(iltype_args, i);
		PrintGenericCache(e->GCache);
		if(i != iltype_args->Length - 1) {
			printf(",");
		}
	}
	printf("<");
}

void ResolveILTypeArgument(Vector* iltype_args, CallContext* cctx) {
	for(int i=0; i<iltype_args->Length; i++) {
		ILTypeArgument* e = (ILTypeArgument*)AtVector(iltype_args, i);
		if(e->GType == NULL) {
	//		Namespace* scope = cc_namespace(
			e->GType = ResolveImportManager(cctx->Scope, e->GCache, cctx);
			//assert(e->gtype->core_type != NULL || e->gtype->virtual_type_index != -1);
		}
	}
}

void DeleteILTypeArgument(ILTypeArgument* self) {
	DeleteGenericCache(self->GCache);
	MEM_FREE(self);
}
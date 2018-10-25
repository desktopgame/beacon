#include "il_type_argument.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../env/namespace.h"
#include "../env/class_loader.h"
#include "../env/import_manager.h"
#include "../il/call_context.h"

il_type_argument* NewILTypeArgument() {
	il_type_argument* ret = (il_type_argument*)MEM_MALLOC(sizeof(il_type_argument));
	ret->gcache = NewGenericCache();
	ret->gtype = NULL;
	return ret;
}

void PrintILTypeArgument(Vector* iltype_args) {
	if(iltype_args->Length == 0) {
		return;
	}
	printf("<");
	for(int i=0; i<iltype_args->Length; i++) {
		il_type_argument* e = (il_type_argument*)AtVector(iltype_args, i);
		PrintGenericCache(e->gcache);
		if(i != iltype_args->Length - 1) {
			printf(",");
		}
	}
	printf("<");
}

void ResolveILTypeArgument(Vector* iltype_args, CallContext* cctx) {
	for(int i=0; i<iltype_args->Length; i++) {
		il_type_argument* e = (il_type_argument*)AtVector(iltype_args, i);
		if(e->gtype == NULL) {
	//		Namespace* scope = cc_namespace(
			e->gtype = ResolveImportManager(cctx->Scope, e->gcache, cctx);
			//assert(e->gtype->core_type != NULL || e->gtype->virtual_type_index != -1);
		}
	}
}

void DeleteILTypeArgument(il_type_argument* self) {
	DeleteGenericCache(self->gcache);
	MEM_FREE(self);
}
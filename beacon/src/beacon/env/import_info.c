#include "import_info.h"
#include <stdlib.h>
#include "../util/mem.h"

bc_ImportInfo * bc_NewImportInfo() {
	bc_ImportInfo* ret = (bc_ImportInfo*)MEM_MALLOC(sizeof(bc_ImportInfo));
	ret->IsConsume = false;
	ret->Context = NULL;
	return ret;
}

void bc_DeleteImportInfo(bc_ImportInfo* self) {
	MEM_FREE(self);
}

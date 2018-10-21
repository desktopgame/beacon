#include "import_info.h"
#include <stdlib.h>
#include "../util/mem.h"

ImportInfo * NewImportInfo() {
	ImportInfo* ret = (ImportInfo*)MEM_MALLOC(sizeof(ImportInfo));
	ret->IsConsume = false;
	ret->Context = NULL;
	return ret;
}

void DeleteImportInfo(ImportInfo* self) {
	MEM_FREE(self);
}

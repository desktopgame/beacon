#include "import_info.h"
#include <stdlib.h>
#include "../util/mem.h"

import_info * NewImportInfo() {
	import_info* ret = (import_info*)MEM_MALLOC(sizeof(import_info));
	ret->consume = false;
	ret->context = NULL;
	return ret;
}

void DeleteImportInfo(import_info* self) {
	MEM_FREE(self);
}

#include "import_info.h"
#include <stdlib.h>
#include "../util/mem.h"

import_info * import_info_new() {
	import_info* ret = (import_info*)MEM_MALLOC(sizeof(import_info));
	ret->consume = false;
	ret->context = NULL;
	return ret;
}

void import_info_delete(import_info* self) {
	MEM_FREE(self);
}

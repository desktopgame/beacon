#include "import_manager.h"
#include "class_loader.h"
#include "class.h"
#include "namespace.h"
#include "fqcn_cache.h"
#include "../util/mem.h"
#include <string.h>
#include <stdlib.h>

import_manager * import_manager_new() {
	import_manager* ret = (import_manager*)MEM_MALLOC(sizeof(import_manager));
	ret->class_loader_list = vector_new();
	return ret;
}

void import_manager_import(import_manager * self, class_loader * target) {
	vector_push(self->class_loader_list, target);
}

class_ * import_manager_resolve(import_manager* self, namespace_* scope, fqcn_cache* fqcn) {
	return fqcn_class(fqcn, scope);
}

void import_manager_delete(import_manager * self) {
	vector_delete(self->class_loader_list, vector_deleter_null);
	MEM_FREE(self);
}

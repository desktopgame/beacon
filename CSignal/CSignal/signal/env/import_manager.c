#include "import_manager.h"
#include "class_loader.h"
#include "type_interface.h"
#include "namespace.h"
#include "fqcn_cache.h"
#include "import_info.h"
#include "../util/mem.h"
#include <string.h>
#include <stdlib.h>

import_manager * import_manager_new() {
	import_manager* ret = (import_manager*)MEM_MALLOC(sizeof(import_manager));
	ret->infoVec = vector_new();
	return ret;
}

import_info* import_manager_import(import_manager * self, class_loader * target) {
	import_info* info = import_info_new();
	info->context = target;
	vector_push(self->infoVec, info);
//	vector_push(self->class_loader_list, target);
	return info;
}

bool import_manager_loaded(import_manager * self, int index) {
	if (index >= self->infoVec->length) {
		return false;
	}
	import_info* info = (import_info*)vector_at(self->infoVec, index);
	return info->consume;
}

type * import_manager_resolve(import_manager* self, namespace_* scope, fqcn_cache* fqcn) {
	return fqcn_type(fqcn, scope);
}

void import_manager_delete(import_manager * self) {
	vector_delete(self->infoVec, vector_deleter_null);
	MEM_FREE(self);
}

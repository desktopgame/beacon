#include "import_manager.h"
#include "class_loader.h"
#include "type_interface.h"
#include "namespace.h"
#include "fqcn_cache.h"
#include "import_info.h"
#include "../util/mem.h"
#include <string.h>
#include <stdlib.h>
#include"generic_cache.h"
#include "generic_type.h"

//proto
static void import_manager_delete_import_info(vector_item item);

import_manager * import_manager_new() {
	import_manager* ret = (import_manager*)MEM_MALLOC(sizeof(import_manager));
	ret->info_vec = vector_new();
	return ret;
}

import_info* import_manager_import(import_manager * self, class_loader * target) {
	import_info* info = import_info_new();
	info->context = target;
	vector_push(self->info_vec, info);
//	vector_push(self->class_loader_list, target);
	return info;
}

bool import_manager_loaded(import_manager * self, int index) {
	if (index >= self->info_vec->length) {
		return false;
	}
	import_info* info = (import_info*)vector_at(self->info_vec, index);
	return info->consume;
}

generic_type * import_manager_resolve(import_manager* self, namespace_* scope, generic_cache* fqcn) {
	return generic_cache_type(fqcn, scope);
}

void import_manager_delete(import_manager * self) {
	vector_delete(self->info_vec, import_manager_delete_import_info);
	MEM_FREE(self);
}
//private
static void import_manager_delete_import_info(vector_item item) {
	import_info* e = (import_info*)item;
	import_info_delete(e);
}
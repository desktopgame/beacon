#include "import_manager.h"
#include "class_loader.h"
#include "type_interface.h"
#include "namespace.h"
#include "fqcn_cache.h"
#include "import_info.h"
#include "method.h"
#include "../util/mem.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include"generic_cache.h"
#include "generic_type.h"
#include "type_impl.h"
#include "../il/il_context.h"

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

void import_manager_resolve(import_manager* self, namespace_* scope, generic_cache* fqcn, il_context* ilcache, virtual_type* dest) {
	type* core_type = fqcn_type(fqcn->fqcn, scope);
	//名前空間でラッピングされていなくて、
	//型が見つからない
	if(core_type == NULL && fqcn->fqcn->scope_vec->length == 0) {
		type* container = (type*)vector_top(ilcache->type_vec);
		dest->tag = virtualtype_class_tv;
		dest->u.index = type_for_generic_index(container, fqcn->fqcn->name);
		if(dest->u.index == -1) {
			method* m = (method*)vector_top(ilcache->method_vec);
			dest->tag = virtualtype_method_tv;
			dest->u.index = method_for_generic_index(m, fqcn->fqcn->name);
		}
		assert(fqcn->type_args->length == 0);
		return;
	}
	//型引数がない
	if(fqcn->type_args->length == 0) {
		if(core_type->tag == type_class) {
			type_init_generic(core_type, core_type->u.class_->type_parameter_list->length);
		} else if(core_type->tag == type_interface) {
			type_init_generic(core_type, core_type->u.interface_->type_parameter_list->length);
		}
		assert(core_type->generic_self != NULL);
		dest->tag = virtualtype_default;
		dest->u.gtype = core_type->generic_self;
		return;
	}

	generic_type* ret2 = generic_type_new(core_type);
	assert(core_type->tag != type_enum);
	for (int i = 0; i < fqcn->type_args->length; i++) {
		generic_cache* e = (generic_cache*)vector_at(fqcn->type_args, i);
		generic_type* child = generic_cache_gtype(e, scope, ilcache);
		generic_type_fixtype(child);
		generic_type_addargs(ret2, child);
	}
	if (core_type->tag == type_class) {
		vector_push(core_type->u.class_->generic_instance_list, ret2);
	} else if (core_type->tag == type_interface) {
		vector_push(core_type->u.interface_->generic_instance_list, ret2);
	}
	assert(ret2 != NULL);
	dest->tag = virtualtype_default;
	dest->u.gtype = ret2;
//	return generic_cache_gtype(fqcn, scope, ilcache);
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
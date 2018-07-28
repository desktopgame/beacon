#include "import_manager.h"
#include "class_loader.h"
#include "type_interface.h"
#include "namespace.h"
#include "fqcn_cache.h"
#include "import_info.h"
#include "compile_context.h"
#include "method.h"
#include "../util/mem.h"
#include "../util/text.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include"generic_cache.h"
#include "generic_type.h"
#include "type_impl.h"

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
	return info;
}

bool import_manager_loaded(import_manager * self, int index) {
	if (index >= self->info_vec->length) {
		return false;
	}
	import_info* info = (import_info*)vector_at(self->info_vec, index);
	return info->consume;
}

generic_type* import_manager_resolve(import_manager* self, namespace_* scope, generic_cache* fqcn) {
	type* core_type = fqcn_type(fqcn->fqcn, scope);
	//名前空間でラッピングされていなくて、
	//型が見つからない
	if(core_type == NULL && fqcn->fqcn->scope_vec->length == 0) {
		generic_type* parameterized = generic_type_new(NULL);
		//メソッドの型引数から見つけられなかったら
		//クラスの型引数を参照する
		bool found = false;
		if(cchas_method()) {
			method* m = cctop_method();
			parameterized->tag = generic_type_tag_method;
			parameterized->virtual_type_index = method_for_generic_index(m, fqcn->fqcn->namev);
			parameterized->u.method_ = m;
			found = (parameterized->virtual_type_index != -1);
		}
		if(!found && cchas_ctor()) {
			type* container = cctop_type();
			parameterized->tag = generic_type_tag_ctor;
			parameterized->virtual_type_index = type_for_generic_index(container, fqcn->fqcn->namev);
			parameterized->u.type_ = container;
			found = (parameterized->virtual_type_index != -1);
		}
		if(!found) {
			type* container = cctop_type();
			parameterized->tag = generic_type_tag_class;
			parameterized->virtual_type_index = type_for_generic_index(container, fqcn->fqcn->namev);
			parameterized->u.type_ = container;
			found = (parameterized->virtual_type_index != -1);
		}
		assert(fqcn->type_args->length == 0);
		return parameterized;
	}
	//Int, String などはっきりした型が見つかった
	//また、型引数もない
	if(fqcn->type_args->length == 0) {
		//text_printfln("`[%s]\n", string_pool_ref2str(type_name(core_type)));
		assert(core_type->generic_self != NULL);
		return core_type->generic_self;
	}
	//Array, Dictionary などはっきりした型が見つかった
	//が、型引数があるのでそれを解決する
	generic_type* normalGType = generic_type_new(core_type);
	assert(core_type->tag != type_enum);
	for (int i = 0; i < fqcn->type_args->length; i++) {
		generic_cache* e = (generic_cache*)vector_at(fqcn->type_args, i);
		generic_type* child = import_manager_resolve(self, scope, e);
		generic_type_addargs(normalGType, child);
	}
	return normalGType;
}

generic_type* import_manager_resolvef(import_manager* self, namespace_* scope, fqcn_cache* fqcn) {
type* core_type = fqcn_type(fqcn, scope);
	//名前空間でラッピングされていなくて、
	//型が見つからない
	if(core_type == NULL && fqcn->scope_vec->length == 0) {
		generic_type* parameterized = generic_type_new(NULL);
		//メソッドの型引数から見つけられなかったら
		//クラスの型引数を参照する
		bool found = false;
		if(cchas_method()) {
			method* m = cctop_method();
			parameterized->tag = generic_type_tag_method;
			parameterized->virtual_type_index = method_for_generic_index(m, fqcn->namev);
			parameterized->u.method_ = m;
			found = (parameterized->virtual_type_index != -1);
		}
		if(!found && cchas_ctor()) {
			type* container = cctop_type();
			parameterized->tag = generic_type_tag_ctor;
			parameterized->virtual_type_index = type_for_generic_index(container, fqcn->namev);
			parameterized->u.type_ = container;
			found = (parameterized->virtual_type_index != -1);
		}
		if(!found) {
			type* container = cctop_type();
			parameterized->tag = generic_type_tag_class;
			parameterized->virtual_type_index = type_for_generic_index(container, fqcn->namev);
			parameterized->u.type_ = container;
			found = (parameterized->virtual_type_index != -1);
		}
		return parameterized;
	}
	//Array, Dictionary などはっきりした型が見つかった
	//が、型引数があるのでそれを解決する
	generic_type* normalGType = generic_type_new(core_type);
	assert(core_type->tag != type_enum);
	return normalGType;
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
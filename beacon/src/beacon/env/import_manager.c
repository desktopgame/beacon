#include "import_manager.h"
#include "class_loader.h"
#include "type_interface.h"
#include "namespace.h"
#include "fqcn_cache.h"
#include "import_info.h"
#include "method.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../il/call_context.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include"generic_cache.h"
#include "generic_type.h"
#include "TYPE_IMPL.h"

//proto
static void import_manager_delete_import_info(VectorItem item);

import_manager * import_manager_new() {
	import_manager* ret = (import_manager*)MEM_MALLOC(sizeof(import_manager));
	ret->info_vec = NewVector();
	return ret;
}

import_info* import_manager_import(import_manager * self, class_loader * target) {
	import_info* info = import_info_new();
	info->context = target;
	PushVector(self->info_vec, info);
	return info;
}

bool import_manager_loaded(import_manager * self, int index) {
	if (index >= self->info_vec->length) {
		return false;
	}
	import_info* info = (import_info*)AtVector(self->info_vec, index);
	return info->consume;
}

generic_type* import_manager_resolve(namespace_* scope, generic_cache* fqcn, call_context* cctx) {
	type* core_type = fqcn_type(fqcn->fqcn, scope);
	#if defined(DEBUG)
	const char* ctname = Ref2Str(type_name(core_type));
	const char* it = Ref2Str(fqcn->fqcn->namev);
	if(fqcn->fqcn->namev == InternString("Token")) {
		int a = 0;
	}
	#endif
	//Int, Double
	if(core_type != NULL && fqcn->type_args->length == 0) {
		assert(core_type->generic_self != NULL);
		return core_type->generic_self;
	}
	//Array[T], Dictionary[K, V]
	if(core_type != NULL && fqcn->type_args->length > 0) {
		//Array, Dictionary などはっきりした型が見つかった
		//が、型引数があるのでそれを解決する
		generic_type* normalGType = generic_type_new(core_type);
		assert(core_type->tag != TYPE_ENUM_T);
		for (int i = 0; i < fqcn->type_args->length; i++) {
			generic_cache* e = (generic_cache*)AtVector(fqcn->type_args, i);
			generic_type* child = import_manager_resolve(scope, e, cctx);
			generic_type_addargs(normalGType, child);
		}
		return normalGType;
	}
	assert(core_type == NULL);
	assert(fqcn->fqcn->scope_vec->length == 0);
	if(fqcn->type_args->length > 0) {
		return NULL;
	}
	generic_type* parameterized = generic_type_new(NULL);
	//T, Eなど
	method* mt = call_context_method(cctx);
	if(parameterized->virtual_type_index == -1 && mt != NULL) {
		parameterized->tag = GENERIC_TYPE_TAG_METHOD_T;
		parameterized->virtual_type_index = method_for_generic_index(mt, fqcn->fqcn->namev);
		parameterized->u.method_ = mt;
	}
	type* ty = call_context_type(cctx);
	if(parameterized->virtual_type_index == -1 &&  ty != NULL) {
		parameterized->tag = GENERIC_TYPE_TAG_CLASS_T;
		parameterized->virtual_type_index = type_for_generic_index(ty, fqcn->fqcn->namev);
		parameterized->u.type_ = ty;
	}
	//現在の名前空間でクラス名を解決できなかったし、
	//現在のコンテキストで型変数として解決することもできなかった
	if(parameterized->virtual_type_index == -1) {
		return NULL;
	}
	return parameterized;
}

generic_type* import_manager_resolvef(namespace_* scope, fqcn_cache* fqcn, call_context* cctx) {
	type* core_type = fqcn_type(fqcn, scope);
	//Int
	//Foo::MyClass
	if(core_type != NULL) {
		return core_type->generic_self;
	}
	//Foo::UndefinedClassName
	if(fqcn->scope_vec->length > 0) {
		return NULL;
	}
	//T, E などの型変数
	//例えば Dictionary[K, V] なら
	//K = class_tag 0
	//V = class_tag 1
	generic_type* parameterized = generic_type_new(NULL);
	//まずはメソッドの型変数を調べる
	method* mt = call_context_method(cctx);
	if(parameterized->virtual_type_index == -1 && mt != NULL) {
		#if defined(DEBUG)
		const char* methodname = Ref2Str(mt->namev);
		#endif
		int index = method_for_generic_index(mt, fqcn->namev);
		parameterized->tag = GENERIC_TYPE_TAG_METHOD_T;
		parameterized->virtual_type_index = index;
		parameterized->u.method_ = mt;
	}
	//次にクラスの型変数を調べる
	type* ty = call_context_type(cctx);
	if(parameterized->virtual_type_index == -1 && ty != NULL) {
		#if defined(DEBUG)
		const char* typename_ = Ref2Str(type_name(ty));
		#endif
		int index = type_for_generic_index(ty, fqcn->namev);
		parameterized->tag = GENERIC_TYPE_TAG_CLASS_T;
		parameterized->virtual_type_index = index;
		parameterized->u.type_ = ty;
	}
	assert(parameterized->virtual_type_index != -1);
	return parameterized;
}

void import_manager_delete(import_manager * self) {
	DeleteVector(self->info_vec, import_manager_delete_import_info);
	MEM_FREE(self);
}
//private
static void import_manager_delete_import_info(VectorItem item) {
	import_info* e = (import_info*)item;
	import_info_delete(e);
}
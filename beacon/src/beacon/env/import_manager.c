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
static void DeleteImportManager_import_info(VectorItem item);

ImportManager * NewImportManager() {
	ImportManager* ret = (ImportManager*)MEM_MALLOC(sizeof(ImportManager));
	ret->Items = NewVector();
	return ret;
}

ImportInfo* ImportImportManager(ImportManager * self, class_loader * target) {
	ImportInfo* info = NewImportInfo();
	info->Context = target;
	PushVector(self->Items, info);
	return info;
}

bool IsLoadedImportManager(ImportManager * self, int index) {
	if (index >= self->Items->Length) {
		return false;
	}
	ImportInfo* info = (ImportInfo*)AtVector(self->Items, index);
	return info->IsConsume;
}

generic_type* ResolveImportManager(namespace_* scope, generic_cache* fqcn, CallContext* cctx) {
	type* core_type = GetTypeFQCN(fqcn->fqcn, scope);
	#if defined(DEBUG)
	const char* ctname = Ref2Str(GetTypeName(core_type));
	const char* it = Ref2Str(fqcn->fqcn->namev);
	if(fqcn->fqcn->namev == InternString("Token")) {
		int a = 0;
	}
	#endif
	//Int, Double
	if(core_type != NULL && fqcn->type_args->Length == 0) {
		assert(core_type->generic_self != NULL);
		return core_type->generic_self;
	}
	//Array[T], Dictionary[K, V]
	if(core_type != NULL && fqcn->type_args->Length > 0) {
		//Array, Dictionary などはっきりした型が見つかった
		//が、型引数があるのでそれを解決する
		generic_type* normalGType = generic_NewType(core_type);
		assert(core_type->tag != TYPE_ENUM_T);
		for (int i = 0; i < fqcn->type_args->Length; i++) {
			generic_cache* e = (generic_cache*)AtVector(fqcn->type_args, i);
			generic_type* child = ResolveImportManager(scope, e, cctx);
			AddArgsGenericType(normalGType, child);
		}
		return normalGType;
	}
	assert(core_type == NULL);
	assert(fqcn->fqcn->scope_vec->Length == 0);
	if(fqcn->type_args->Length > 0) {
		return NULL;
	}
	generic_type* parameterized = generic_NewType(NULL);
	//T, Eなど
	method* mt = GetMethodCContext(cctx);
	if(parameterized->virtual_type_index == -1 && mt != NULL) {
		parameterized->tag = GENERIC_TYPE_TAG_METHOD_T;
		parameterized->virtual_type_index = GetGenericIndexForMethod(mt, fqcn->fqcn->namev);
		parameterized->u.method_ = mt;
	}
	type* ty = GetTypeCContext(cctx);
	if(parameterized->virtual_type_index == -1 &&  ty != NULL) {
		parameterized->tag = GENERIC_TYPE_TAG_CLASS_T;
		parameterized->virtual_type_index = GetGenericIndexType(ty, fqcn->fqcn->namev);
		parameterized->u.type_ = ty;
	}
	//現在の名前空間でクラス名を解決できなかったし、
	//現在のコンテキストで型変数として解決することもできなかった
	if(parameterized->virtual_type_index == -1) {
		return NULL;
	}
	return parameterized;
}

generic_type* ResolvefImportManager(namespace_* scope, fqcn_cache* fqcn, CallContext* cctx) {
	type* core_type = GetTypeFQCN(fqcn, scope);
	//Int
	//Foo::MyClass
	if(core_type != NULL) {
		return core_type->generic_self;
	}
	//Foo::UndefinedClassName
	if(fqcn->scope_vec->Length > 0) {
		return NULL;
	}
	//T, E などの型変数
	//例えば Dictionary[K, V] なら
	//K = class_tag 0
	//V = class_tag 1
	generic_type* parameterized = generic_NewType(NULL);
	//まずはメソッドの型変数を調べる
	method* mt = GetMethodCContext(cctx);
	if(parameterized->virtual_type_index == -1 && mt != NULL) {
		#if defined(DEBUG)
		const char* methodname = Ref2Str(mt->namev);
		#endif
		int index = GetGenericIndexForMethod(mt, fqcn->namev);
		parameterized->tag = GENERIC_TYPE_TAG_METHOD_T;
		parameterized->virtual_type_index = index;
		parameterized->u.method_ = mt;
	}
	//次にクラスの型変数を調べる
	type* ty = GetTypeCContext(cctx);
	if(parameterized->virtual_type_index == -1 && ty != NULL) {
		#if defined(DEBUG)
		const char* typename_ = Ref2Str(GetTypeName(ty));
		#endif
		int index = GetGenericIndexType(ty, fqcn->namev);
		parameterized->tag = GENERIC_TYPE_TAG_CLASS_T;
		parameterized->virtual_type_index = index;
		parameterized->u.type_ = ty;
	}
	assert(parameterized->virtual_type_index != -1);
	return parameterized;
}

void DeleteImportManager(ImportManager * self) {
	DeleteVector(self->Items, DeleteImportManager_import_info);
	MEM_FREE(self);
}
//private
static void DeleteImportManager_import_info(VectorItem item) {
	ImportInfo* e = (ImportInfo*)item;
	DeleteImportInfo(e);
}
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
static void delete_import_info(bc_VectorItem item);

bc_ImportManager * bc_NewImportManager() {
	bc_ImportManager* ret = (bc_ImportManager*)MEM_MALLOC(sizeof(bc_ImportManager));
	ret->Items = bc_NewVector();
	return ret;
}

bc_ImportInfo* bc_ImportImportManager(bc_ImportManager * self, bc_ClassLoader * target) {
	bc_ImportInfo* info = bc_NewImportInfo();
	info->Context = target;
	bc_PushVector(self->Items, info);
	return info;
}

bool bc_IsLoadedImportManager(bc_ImportManager * self, int index) {
	if (index >= self->Items->Length) {
		return false;
	}
	bc_ImportInfo* info = (bc_ImportInfo*)bc_AtVector(self->Items, index);
	return info->IsConsume;
}

bc_GenericType* bc_ResolveImportManager(bc_Namespace* scope, bc_GenericCache* fqcn, bc_CallContext* cctx) {
	bc_Type* CoreType = bc_GetTypeFQCN(fqcn->FQCN, scope);
	#if defined(DEBUG)
	const char* ctname = bc_Ref2Str(bc_GetTypeName(CoreType));
	const char* it = bc_Ref2Str(fqcn->FQCN->Name);
	#endif
	//Int, Double
	if(CoreType != NULL && fqcn->TypeArgs->Length == 0) {
		assert(CoreType->GenericSelf != NULL);
		return CoreType->GenericSelf;
	}
	//Array[T], Dictionary[K, V]
	if(CoreType != NULL && fqcn->TypeArgs->Length > 0) {
		//Array, Dictionary などはっきりした型が見つかった
		//が、型引数があるのでそれを解決する
		bc_GenericType* normalGType = bc_NewGenericType(CoreType);
		assert(CoreType->Tag != TYPE_ENUM_T);
		for (int i = 0; i < fqcn->TypeArgs->Length; i++) {
			bc_GenericCache* e = (bc_GenericCache*)bc_AtVector(fqcn->TypeArgs, i);
			bc_GenericType* child = bc_ResolveImportManager(scope, e, cctx);
			bc_AddArgsGenericType(normalGType, child);
		}
		return normalGType;
	}
	assert(CoreType == NULL);
	assert(fqcn->FQCN->Scope->Length == 0);
	if(fqcn->TypeArgs->Length > 0) {
		return NULL;
	}
	bc_GenericType* parameterized = bc_NewGenericType(NULL);
	//T, Eなど
	bc_Method* mt = bc_GetMethodCContext(cctx);
	if(parameterized->VirtualTypeIndex == -1 && mt != NULL) {
		parameterized->Tag = GENERIC_TYPE_TAG_METHOD_T;
		parameterized->VirtualTypeIndex = bc_GetGenericIndexForMethod(mt, fqcn->FQCN->Name);
		parameterized->Kind.Method = mt;
	}
	bc_Type* ty = bc_GetTypeCContext(cctx);
	if(parameterized->VirtualTypeIndex == -1 &&  ty != NULL) {
		parameterized->Tag = GENERIC_TYPE_TAG_CLASS_T;
		parameterized->VirtualTypeIndex = bc_GetGenericIndexType(ty, fqcn->FQCN->Name);
		parameterized->Kind.Type = ty;
	}
	//現在の名前空間でクラス名を解決できなかったし、
	//現在のコンテキストで型変数として解決することもできなかった
	if(parameterized->VirtualTypeIndex == -1) {
		return NULL;
	}
	return parameterized;
}

bc_GenericType* bc_ResolvefImportManager(bc_Namespace* scope, bc_FQCNCache* fqcn, bc_CallContext* cctx) {
	bc_Type* CoreType = bc_GetTypeFQCN(fqcn, scope);
	//Int
	//Foo::MyClass
	if(CoreType != NULL) {
		return CoreType->GenericSelf;
	}
	//Foo::UndefinedClassName
	if(fqcn->Scope->Length > 0) {
		return NULL;
	}
	//T, E などの型変数
	//例えば Dictionary[K, V] なら
	//K = class_tag 0
	//V = class_tag 1
	bc_GenericType* parameterized = bc_NewGenericType(NULL);
	//まずはメソッドの型変数を調べる
	bc_Method* mt = bc_GetMethodCContext(cctx);
	if(parameterized->VirtualTypeIndex == -1 && mt != NULL) {
		#if defined(DEBUG)
		const char* methodname = bc_Ref2Str(mt->Name);
		#endif
		int index = bc_GetGenericIndexForMethod(mt, fqcn->Name);
		parameterized->Tag = GENERIC_TYPE_TAG_METHOD_T;
		parameterized->VirtualTypeIndex = index;
		parameterized->Kind.Method = mt;
	}
	//次にクラスの型変数を調べる
	bc_Type* ty = bc_GetTypeCContext(cctx);
	if(parameterized->VirtualTypeIndex == -1 && ty != NULL) {
		#if defined(DEBUG)
		const char* typename_ = bc_Ref2Str(bc_GetTypeName(ty));
		#endif
		int index = bc_GetGenericIndexType(ty, fqcn->Name);
		parameterized->Tag = GENERIC_TYPE_TAG_CLASS_T;
		parameterized->VirtualTypeIndex = index;
		parameterized->Kind.Type = ty;
	}
	assert(parameterized->VirtualTypeIndex != -1);
	return parameterized;
}

void bc_DeleteImportManager(bc_ImportManager * self) {
	bc_DeleteVector(self->Items, delete_import_info);
	MEM_FREE(self);
}
//private
static void delete_import_info(bc_VectorItem item) {
	bc_ImportInfo* e = (bc_ImportInfo*)item;
	bc_DeleteImportInfo(e);
}
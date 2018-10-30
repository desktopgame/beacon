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

ImportInfo* ImportImportManager(ImportManager * self, ClassLoader * target) {
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

GenericType* ResolveImportManager(Namespace* scope, GenericCache* fqcn, CallContext* cctx) {
	Type* CoreType = GetTypeFQCN(fqcn->FQCN, scope);
	#if defined(DEBUG)
	const char* ctname = Ref2Str(GetTypeName(CoreType));
	const char* it = Ref2Str(fqcn->FQCN->Name);
	if(fqcn->FQCN->Name == InternString("Token")) {
		int a = 0;
	}
	#endif
	//Int, Double
	if(CoreType != NULL && fqcn->TypeArgs->Length == 0) {
		assert(CoreType->generic_self != NULL);
		return CoreType->generic_self;
	}
	//Array[T], Dictionary[K, V]
	if(CoreType != NULL && fqcn->TypeArgs->Length > 0) {
		//Array, Dictionary などはっきりした型が見つかった
		//が、型引数があるのでそれを解決する
		GenericType* normalGType = generic_NewType(CoreType);
		assert(CoreType->tag != TYPE_ENUM_T);
		for (int i = 0; i < fqcn->TypeArgs->Length; i++) {
			GenericCache* e = (GenericCache*)AtVector(fqcn->TypeArgs, i);
			GenericType* child = ResolveImportManager(scope, e, cctx);
			AddArgsGenericType(normalGType, child);
		}
		return normalGType;
	}
	assert(CoreType == NULL);
	assert(fqcn->FQCN->Scope->Length == 0);
	if(fqcn->TypeArgs->Length > 0) {
		return NULL;
	}
	GenericType* parameterized = generic_NewType(NULL);
	//T, Eなど
	Method* mt = GetMethodCContext(cctx);
	if(parameterized->VirtualTypeIndex == -1 && mt != NULL) {
		parameterized->Tag = GENERIC_TYPE_TAG_METHOD_T;
		parameterized->VirtualTypeIndex = GetGenericIndexForMethod(mt, fqcn->FQCN->Name);
		parameterized->Kind.Method = mt;
	}
	Type* ty = GetTypeCContext(cctx);
	if(parameterized->VirtualTypeIndex == -1 &&  ty != NULL) {
		parameterized->Tag = GENERIC_TYPE_TAG_CLASS_T;
		parameterized->VirtualTypeIndex = GetGenericIndexType(ty, fqcn->FQCN->Name);
		parameterized->Kind.Type = ty;
	}
	//現在の名前空間でクラス名を解決できなかったし、
	//現在のコンテキストで型変数として解決することもできなかった
	if(parameterized->VirtualTypeIndex == -1) {
		return NULL;
	}
	return parameterized;
}

GenericType* ResolvefImportManager(Namespace* scope, FQCNCache* fqcn, CallContext* cctx) {
	Type* CoreType = GetTypeFQCN(fqcn, scope);
	//Int
	//Foo::MyClass
	if(CoreType != NULL) {
		return CoreType->generic_self;
	}
	//Foo::UndefinedClassName
	if(fqcn->Scope->Length > 0) {
		return NULL;
	}
	//T, E などの型変数
	//例えば Dictionary[K, V] なら
	//K = class_tag 0
	//V = class_tag 1
	GenericType* parameterized = generic_NewType(NULL);
	//まずはメソッドの型変数を調べる
	Method* mt = GetMethodCContext(cctx);
	if(parameterized->VirtualTypeIndex == -1 && mt != NULL) {
		#if defined(DEBUG)
		const char* methodname = Ref2Str(mt->Name);
		#endif
		int index = GetGenericIndexForMethod(mt, fqcn->Name);
		parameterized->Tag = GENERIC_TYPE_TAG_METHOD_T;
		parameterized->VirtualTypeIndex = index;
		parameterized->Kind.Method = mt;
	}
	//次にクラスの型変数を調べる
	Type* ty = GetTypeCContext(cctx);
	if(parameterized->VirtualTypeIndex == -1 && ty != NULL) {
		#if defined(DEBUG)
		const char* typename_ = Ref2Str(GetTypeName(ty));
		#endif
		int index = GetGenericIndexType(ty, fqcn->Name);
		parameterized->Tag = GENERIC_TYPE_TAG_CLASS_T;
		parameterized->VirtualTypeIndex = index;
		parameterized->Kind.Type = ty;
	}
	assert(parameterized->VirtualTypeIndex != -1);
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
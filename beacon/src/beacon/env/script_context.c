#include "script_context.h"
#include "heap.h"
#include "namespace.h"
#include "field.h"
#include "type_interface.h"
#include "type/class_impl.h"
#include "class_loader.h"
#include <stdlib.h>
#include <assert.h>
#include "generic_type.h"
#include "../util/mem.h"
#include "../util/io.h"
#include "../lib/bc_library_interface.h"
#include "../thread/thread.h"
#include "../util/text.h"
//proto
static bc_ScriptContext* malloc_script_context(void);
static void free_script_context(bc_ScriptContext* self);
static void delete_class_loader(const char* name, TreeItem item);

static void unlink_namespace(NumericMapKey key, NumericMapItem item);
static void delete_namespace(NumericMapKey key, NumericMapItem item);
static void clear_impl(bc_Field* item);
static void delete_cache(VectorItem item);
static void delete_mcache(NumericMapKey key, NumericMapItem item);

static Vector* gScriptContextVec = NULL;
static bc_ScriptContext* gScriptContext = NULL;

bc_ScriptContext* bc_OpenScriptContext() {
	if(gScriptContextVec == NULL) {
		gScriptContextVec = NewVector();
		LaunchSGThread();
	}
	bc_ScriptContext* sctx = malloc_script_context();
	gScriptContext = sctx;
	PushVector(gScriptContextVec, sctx);
	bc_BootstrapScriptContext(sctx);
	return sctx;
}

bc_ScriptContext * bc_GetCurrentScriptContext() {
	assert(gScriptContext != NULL);
	return gScriptContext;
}

void bc_CloseScriptContext() {
	bc_ScriptContext* sctx = (bc_ScriptContext*)PopVector(gScriptContextVec);
	free_script_context(sctx);
	gScriptContext = NULL;
	if(gScriptContextVec->Length == 0) {
		DestroySGThread();
		DeleteVector(gScriptContextVec, VectorDeleterOfNull);
		gScriptContextVec = NULL;
	} else {
		gScriptContext = (bc_ScriptContext*)TopVector(gScriptContextVec);
	}
}

void bc_BootstrapScriptContext(bc_ScriptContext* self) {
	self->Heap->AcceptBlocking++;
	//プリロード
	bc_Namespace* beacon = bc_CreateNamespaceAtRoot(InternString("beacon"));
	bc_Namespace* lang = bc_AddNamespaceNamespace(beacon, InternString("lang"));
	bc_Namespace* unsafe = bc_AddNamespaceNamespace(beacon, InternString("unsafe"));
	bc_Namespace* placeholder = bc_CreateNamespaceAtRoot(InternString("$placeholder"));
	InitObject();
	InitArray();
	InitException();
	InitInt();
	InitDouble();
	InitChar();
	InitString();
	InitBool();
	InitVoid();
	InitConsole();
	InitNull();
	InitFile();
	InitSystem();
	InitLocaleType();
	InitTime();
	//ブートストラップクラスローダー
	self->BootstrapClassLoader = bc_NewClassLoader("bootstrap", CONTENT_LIB_T);
	bc_SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/Object.bc");

	bc_SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/Int.bc");
	bc_SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/Double.bc");
	bc_SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/Char.bc");
	bc_SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/Bool.bc");
	bc_SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/Null.bc");
	bc_SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/Void.bc");

	bc_SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/Iterable.bc");
	bc_SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/Iterator.bc");
	bc_SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/Array.bc");
	bc_SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/String.bc");
	bc_SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/Console.bc");
	bc_SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/Exception.bc");
	bc_SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/StackTraceElement.bc");

	bc_SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/World.bc");
	//退避していたコンテキストを復帰
	self->Heap->AcceptBlocking--;
}

void bc_EachStaticScriptContext(bc_ScriptContext* self, bc_StaticEach act) {
	bc_ScriptContext* ctx = self;
	for (int i = 0; i < ctx->TypeList->Length; i++) {
		bc_Type* e = (bc_Type*)AtVector(ctx->TypeList, i);
		if (e->Tag != TYPE_CLASS_T) {
			continue;
		}
		Class* cls = e->Kind.Class;
		for (int j = 0; j < cls->StaticFields->Length; j++) {
			bc_Field* f = (bc_Field*)AtVector(cls->StaticFields, j);
			if(bc_IsStaticModifier(f->Modifier)) {
				act(f);
			}
		}
	}
}

void bc_ClearScriptContext(bc_ScriptContext* self) {
	bc_EachStaticScriptContext(self, clear_impl);
}

bc_Object* bc_IInternScriptContext(bc_ScriptContext* self, int i) {
	bc_Heap* he = self->Heap;
	NumericMap* cell = GetNumericMapCell(self->IntegerCacheMap, i);
	he->AcceptBlocking++;
	if(cell == NULL) {
		bc_Object* obj = (bc_Object*)NewInteger(i);
		obj->Paint = PAINT_ONEXIT_T;
		cell = PutNumericMap(self->IntegerCacheMap, i, obj);
	}
	he->AcceptBlocking--;
	return (bc_Object*)cell->Item;
}

void bc_CacheScriptContext() {
	bc_ScriptContext* self = bc_GetCurrentScriptContext();
	if(self == NULL) return;
	bc_Heap* h = bc_GetHeap();
	if(h != NULL) h->AcceptBlocking++;
	//すでにキャッシュされている
	if(self->PositiveIntegerCacheList->Length > 0 ||
	   self->NegativeIntegerCacheList->Length > 0) {
		if(h != NULL) h->AcceptBlocking--;
		   return;
	   }
	//正の数のキャッシュ
	for(int i=0; i<100; i++) {
		bc_Object* a = (bc_Object*)NewInteger(i);
		PushVector(self->PositiveIntegerCacheList, a);
		a->Paint = PAINT_ONEXIT_T;
	}
	//負の数のキャッシュ
	for(int i=1; i<10; i++) {
		bc_Object* a = (bc_Object*)NewInteger(-i);
		PushVector(self->NegativeIntegerCacheList, a);
		a->Paint = PAINT_ONEXIT_T;
	}
	if(h != NULL) h->AcceptBlocking--;
}

//private
static bc_ScriptContext* malloc_script_context(void) {
	bc_ScriptContext* ret = (bc_ScriptContext*)MEM_MALLOC(sizeof(bc_ScriptContext));
	ret->NamespaceMap = NewNumericMap();
	ret->ClassLoaderMap = NewTreeMap();
	ret->Heap = bc_NewHeap();
	ret->TypeList = NewVector();
	ret->ThreadList = NewVector();
	ret->BootstrapClassLoader = NULL;
	ret->AllGenericList = NewVector();
	ret->True = NULL;
	ret->False = NULL;
	ret->Null = NULL;
#if defined(_MSC_VER)
	char* path = bc_GetAbsolutePath("script-lib/beacon/lang");
	ret->IncludeList = bc_GetFiles(path);
	MEM_FREE(path);
#else
	ret->IncludeList = bc_GetFiles("script-lib/beacon/lang");
#endif
	ret->PositiveIntegerCacheList = NewVector();
	ret->NegativeIntegerCacheList = NewVector();
	ret->IntegerCacheMap = NewNumericMap();
	ret->IsPrintError = true;
	ret->IsAbortOnError = true;
	PushVector(ret->ThreadList, GetMainSGThread());
	return ret;
}

static void free_script_context(bc_ScriptContext* self) {
	int aa = bc_CountActiveObject();
	assert(self->Heap->CollectBlocking == 0);
	//全ての例外フラグをクリア
	Frame* thv = GetSGThreadFrameRef(GetCurrentSGThread(self));
	CatchVM(thv);
	bc_DeleteClassLoader(self->BootstrapClassLoader);
	if(self->Null != NULL) {
		bc_IgnoreHeap(self->Heap, self->Null);
		self->Null->Paint = PAINT_ONEXIT_T;
		bc_DestroyObject(self->Null);
	}
	bc_DeleteHeap(self->Heap);
	DeleteVector(self->NegativeIntegerCacheList, delete_cache);
	DeleteVector(self->PositiveIntegerCacheList, delete_cache);
	DeleteNumericMap(self->IntegerCacheMap, delete_mcache);
	//DeleteObject(self->Null);
	bc_CollectGenericType();
	DeleteVector(self->AllGenericList, VectorDeleterOfNull);
	int x = bc_CountActiveObject();

	DeleteVector(self->TypeList, VectorDeleterOfNull);
	DeleteVector(self->ThreadList, VectorDeleterOfNull);
	DeleteTreeMap(self->ClassLoaderMap, delete_class_loader);
	//ブートストラップクラスローダを意図的に起動していないなら、
	//ここはまだNULL
	if(self->NamespaceMap != NULL) {
		EachNumericMap(self->NamespaceMap, unlink_namespace);
	}

	int a = bc_CountActiveObject();
	DeleteNumericMap(self->NamespaceMap, delete_namespace);
	bc_DeleteFiles(self->IncludeList);
	MEM_FREE(self);
}

static void delete_class_loader(const char* name, TreeItem item) {
	bc_ClassLoader* e = (bc_ClassLoader*)item;
	bc_DeleteClassLoader(e);
}

static void unlink_namespace(NumericMapKey key, NumericMapItem item) {
	bc_Namespace* e = (bc_Namespace*)item;
	bc_UnlinkNamespace(e);
}

static void delete_namespace(NumericMapKey key, NumericMapItem item) {
	bc_Namespace* e = (bc_Namespace*)item;
	bc_DeleteNamespace(e);
}

static void clear_impl(bc_Field* item) {
	item->StaticValue = bc_GetNullObject();
}

static void delete_cache(VectorItem item) {
	bc_DestroyObject((bc_Object*)item);
}

static void delete_mcache(NumericMapKey key, NumericMapItem item) {
	bc_DestroyObject((bc_Object*)item);
}
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
static ScriptContext* ScriptContext_malloc(void);
static void ScriptContext_free(ScriptContext* self);
static void ScriptContext_DeleteClassLoader(const char* name, TreeItem item);

static void ScriptContext_UnlinkNamespace(NumericMapKey key, NumericMapItem item);
static void ScriptContext_DeleteNamespace(NumericMapKey key, NumericMapItem item);
static void ClearScriptContextImpl(Field* item);
static void CacheScriptContext_delete(VectorItem item);
static void ScriptContext_mcache_delete(NumericMapKey key, NumericMapItem item);

static Vector* gScriptContextVec = NULL;
static ScriptContext* gScriptContext = NULL;

ScriptContext* OpenScriptContext() {
	if(gScriptContextVec == NULL) {
		gScriptContextVec = NewVector();
		LaunchSGThread();
	}
	ScriptContext* sctx = ScriptContext_malloc();
	gScriptContext = sctx;
	PushVector(gScriptContextVec, sctx);
	BootstrapScriptContext(sctx);
	return sctx;
}

ScriptContext * GetCurrentScriptContext() {
	assert(gScriptContext != NULL);
	return gScriptContext;
}

void CloseScriptContext() {
	ScriptContext* sctx = (ScriptContext*)PopVector(gScriptContextVec);
	ScriptContext_free(sctx);
	gScriptContext = NULL;
	if(gScriptContextVec->Length == 0) {
		DestroySGThread();
		DeleteVector(gScriptContextVec, VectorDeleterOfNull);
		gScriptContextVec = NULL;
	} else {
		gScriptContext = (ScriptContext*)TopVector(gScriptContextVec);
	}
}

void BootstrapScriptContext(ScriptContext* self) {
	self->Heap->AcceptBlocking++;
	//プリロード
	Namespace* beacon = CreateNamespaceAtRoot(InternString("beacon"));
	Namespace* lang = AddNamespaceNamespace(beacon, InternString("lang"));
	Namespace* unsafe = AddNamespaceNamespace(beacon, InternString("unsafe"));
	Namespace* placeholder = CreateNamespaceAtRoot(InternString("$placeholder"));
	InitBCObject();
	InitBCArray();
	InitBCException();
	InitBCInt();
	InitBCDouble();
	InitBCChar();
	InitBCString();
	InitBCBool();
	InitBCVoid();
	InitBCConsole();
	InitBCNull();
	InitBCFile();
	InitBCSystem();
	InitBCLocaleType();
	InitBCTime();
	//ブートストラップクラスローダー
	self->BootstrapClassLoader = NewClassLoader("bootstrap", CONTENT_LIB_T);
	SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/Object.bc");

	SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/Int.bc");
	SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/Double.bc");
	SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/Char.bc");
	SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/Bool.bc");
	SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/Null.bc");
	SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/Void.bc");

	SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/Iterable.bc");
	SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/Iterator.bc");
	SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/Array.bc");
	SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/String.bc");
	SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/Console.bc");
	SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/Exception.bc");
	SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/StackTraceElement.bc");

	SpecialLoadClassLoader(self->BootstrapClassLoader, "beacon/lang/World.bc");
	//退避していたコンテキストを復帰
	self->Heap->AcceptBlocking--;
}

void EachStaticScriptContext(ScriptContext* self, static_each act) {
	ScriptContext* ctx = self;
	for (int i = 0; i < ctx->TypeList->Length; i++) {
		Type* e = (Type*)AtVector(ctx->TypeList, i);
		if (e->tag != TYPE_CLASS_T) {
			continue;
		}
		class_* cls = e->u.class_;
		for (int j = 0; j < cls->sfield_list->Length; j++) {
			Field* f = (Field*)AtVector(cls->sfield_list, j);
			if(IsStaticModifier(f->modifier)) {
				act(f);
			}
		}
	}
}

void ClearScriptContext(ScriptContext* self) {
	EachStaticScriptContext(self, ClearScriptContextImpl);
}

Object* IInternScriptContext(ScriptContext* self, int i) {
	Heap* he = self->Heap;
	NumericMap* cell = GetNumericMapCell(self->IntegerCacheMap, i);
	he->AcceptBlocking++;
	if(cell == NULL) {
		Object* obj = Object_int_new(i);
		obj->Paint = PAINT_ONEXIT_T;
		cell = PutNumericMap(self->IntegerCacheMap, i, obj);
	}
	he->AcceptBlocking--;
	return (Object*)cell->Item;
}

void CacheScriptContext() {
	ScriptContext* self = GetCurrentScriptContext();
	if(self == NULL) return;
	Heap* h = GetHeap();
	if(h != NULL) h->AcceptBlocking++;
	//すでにキャッシュされている
	if(self->PositiveIntegerCacheList->Length > 0 ||
	   self->NegativeIntegerCacheList->Length > 0) {
		if(h != NULL) h->AcceptBlocking--;
		   return;
	   }
	//正の数のキャッシュ
	for(int i=0; i<100; i++) {
		Object* a = Object_int_new(i);
		PushVector(self->PositiveIntegerCacheList, a);
		a->Paint = PAINT_ONEXIT_T;
	}
	//負の数のキャッシュ
	for(int i=1; i<10; i++) {
		Object* a = Object_int_new(-i);
		PushVector(self->NegativeIntegerCacheList, a);
		a->Paint = PAINT_ONEXIT_T;
	}
	if(h != NULL) h->AcceptBlocking--;
}

//private
static ScriptContext* ScriptContext_malloc(void) {
	ScriptContext* ret = (ScriptContext*)MEM_MALLOC(sizeof(ScriptContext));
	ret->NamespaceMap = NewNumericMap();
	ret->ClassLoaderMap = NewTreeMap();
	ret->Heap = NewHeap();
	ret->TypeList = NewVector();
	ret->ThreadList = NewVector();
	ret->BootstrapClassLoader = NULL;
	ret->AllGenericList = NewVector();
	ret->True = NULL;
	ret->False = NULL;
	ret->Null = NULL;
#if defined(_MSC_VER)
	char* path = GetAbsolutePath("script-lib/beacon/lang");
	ret->IncludeList = GetFiles(path);
	MEM_FREE(path);
#else
	ret->IncludeList = GetFiles("script-lib/beacon/lang");
#endif
	ret->PositiveIntegerCacheList = NewVector();
	ret->NegativeIntegerCacheList = NewVector();
	ret->IntegerCacheMap = NewNumericMap();
	ret->IsPrintError = true;
	ret->IsAbortOnError = true;
	PushVector(ret->ThreadList, GetMainSGThread());
	return ret;
}

static void ScriptContext_free(ScriptContext* self) {
	int aa = CountActiveObject();
	assert(self->Heap->CollectBlocking == 0);
	//全ての例外フラグをクリア
	Frame* thv = GetSGThreadFrameRef(GetCurrentSGThread(self));
	CatchVM(thv);
	DeleteClassLoader(self->BootstrapClassLoader);
	if(self->Null != NULL) {
		IgnoreHeap(self->Heap, self->Null);
		self->Null->Paint = PAINT_ONEXIT_T;
		DestroyObject(self->Null);
	}
	DeleteHeap(self->Heap);
	DeleteVector(self->NegativeIntegerCacheList, CacheScriptContext_delete);
	DeleteVector(self->PositiveIntegerCacheList, CacheScriptContext_delete);
	DeleteNumericMap(self->IntegerCacheMap, ScriptContext_mcache_delete);
	//DeleteObject(self->Null);
	CollectGenericType();
	DeleteVector(self->AllGenericList, VectorDeleterOfNull);
	int x = CountActiveObject();

	DeleteVector(self->TypeList, VectorDeleterOfNull);
	DeleteVector(self->ThreadList, VectorDeleterOfNull);
	DeleteTreeMap(self->ClassLoaderMap, ScriptContext_DeleteClassLoader);
	//ブートストラップクラスローダを意図的に起動していないなら、
	//ここはまだNULL
	if(self->NamespaceMap != NULL) {
		EachNumericMap(self->NamespaceMap, ScriptContext_UnlinkNamespace);
	}

	int a = CountActiveObject();
	DeleteNumericMap(self->NamespaceMap, ScriptContext_DeleteNamespace);
	DeleteFiles(self->IncludeList);
	MEM_FREE(self);
}

static void ScriptContext_DeleteClassLoader(const char* name, TreeItem item) {
	ClassLoader* e = (ClassLoader*)item;
	DeleteClassLoader(e);
}

static void ScriptContext_UnlinkNamespace(NumericMapKey key, NumericMapItem item) {
	Namespace* e = (Namespace*)item;
	UnlinkNamespace(e);
}

static void ScriptContext_DeleteNamespace(NumericMapKey key, NumericMapItem item) {
	Namespace* e = (Namespace*)item;
	DeleteNamespace(e);
}

static void ClearScriptContextImpl(Field* item) {
	item->static_value = GetNullObject();
}

static void CacheScriptContext_delete(VectorItem item) {
	DestroyObject((Object*)item);
}

static void ScriptContext_mcache_delete(NumericMapKey key, NumericMapItem item) {
	DestroyObject((Object*)item);
}
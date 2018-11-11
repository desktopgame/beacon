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
static ScriptContext* malloc_script_context(void);
static void free_script_context(ScriptContext* self);
static void delete_class_loader(const char* name, TreeItem item);

static void unlink_namespace(NumericMapKey key, NumericMapItem item);
static void delete_namespace(NumericMapKey key, NumericMapItem item);
static void clear_impl(Field* item);
static void delete_cache(VectorItem item);
static void delete_mcache(NumericMapKey key, NumericMapItem item);

static Vector* gScriptContextVec = NULL;
static ScriptContext* gScriptContext = NULL;

ScriptContext* OpenScriptContext() {
	if(gScriptContextVec == NULL) {
		gScriptContextVec = NewVector();
		LaunchSGThread();
	}
	ScriptContext* sctx = malloc_script_context();
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
	free_script_context(sctx);
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
	InitFile();
	InitBCSystem();
	InitLocaleType();
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

void EachStaticScriptContext(ScriptContext* self, StaticEach act) {
	ScriptContext* ctx = self;
	for (int i = 0; i < ctx->TypeList->Length; i++) {
		Type* e = (Type*)AtVector(ctx->TypeList, i);
		if (e->Tag != TYPE_CLASS_T) {
			continue;
		}
		Class* cls = e->Kind.Class;
		for (int j = 0; j < cls->StaticFields->Length; j++) {
			Field* f = (Field*)AtVector(cls->StaticFields, j);
			if(IsStaticModifier(f->Modifier)) {
				act(f);
			}
		}
	}
}

void ClearScriptContext(ScriptContext* self) {
	EachStaticScriptContext(self, clear_impl);
}

Object* IInternScriptContext(ScriptContext* self, int i) {
	Heap* he = self->Heap;
	NumericMap* cell = GetNumericMapCell(self->IntegerCacheMap, i);
	he->AcceptBlocking++;
	if(cell == NULL) {
		Object* obj = (Object*)NewInteger(i);
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
		Object* a = (Object*)NewInteger(i);
		PushVector(self->PositiveIntegerCacheList, a);
		a->Paint = PAINT_ONEXIT_T;
	}
	//負の数のキャッシュ
	for(int i=1; i<10; i++) {
		Object* a = (Object*)NewInteger(-i);
		PushVector(self->NegativeIntegerCacheList, a);
		a->Paint = PAINT_ONEXIT_T;
	}
	if(h != NULL) h->AcceptBlocking--;
}

//private
static ScriptContext* malloc_script_context(void) {
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

static void free_script_context(ScriptContext* self) {
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
	DeleteVector(self->NegativeIntegerCacheList, delete_cache);
	DeleteVector(self->PositiveIntegerCacheList, delete_cache);
	DeleteNumericMap(self->IntegerCacheMap, delete_mcache);
	//DeleteObject(self->Null);
	CollectGenericType();
	DeleteVector(self->AllGenericList, VectorDeleterOfNull);
	int x = CountActiveObject();

	DeleteVector(self->TypeList, VectorDeleterOfNull);
	DeleteVector(self->ThreadList, VectorDeleterOfNull);
	DeleteTreeMap(self->ClassLoaderMap, delete_class_loader);
	//ブートストラップクラスローダを意図的に起動していないなら、
	//ここはまだNULL
	if(self->NamespaceMap != NULL) {
		EachNumericMap(self->NamespaceMap, unlink_namespace);
	}

	int a = CountActiveObject();
	DeleteNumericMap(self->NamespaceMap, delete_namespace);
	DeleteFiles(self->IncludeList);
	MEM_FREE(self);
}

static void delete_class_loader(const char* name, TreeItem item) {
	ClassLoader* e = (ClassLoader*)item;
	DeleteClassLoader(e);
}

static void unlink_namespace(NumericMapKey key, NumericMapItem item) {
	Namespace* e = (Namespace*)item;
	UnlinkNamespace(e);
}

static void delete_namespace(NumericMapKey key, NumericMapItem item) {
	Namespace* e = (Namespace*)item;
	DeleteNamespace(e);
}

static void clear_impl(Field* item) {
	item->StaticValue = GetNullObject();
}

static void delete_cache(VectorItem item) {
	DestroyObject((Object*)item);
}

static void delete_mcache(NumericMapKey key, NumericMapItem item) {
	DestroyObject((Object*)item);
}
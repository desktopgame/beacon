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
static script_context* script_context_malloc(void);
static void script_context_free(script_context* self);
static void script_context_DeleteClassLoader(const char* name, TreeItem item);

static void script_context_UnlinkNamespace(NumericMapKey key, NumericMapItem item);
static void script_context_DeleteNamespace(NumericMapKey key, NumericMapItem item);
static void ClearScriptContextImpl(field* item);
static void CacheScriptContext_delete(VectorItem item);
static void script_context_mcache_delete(NumericMapKey key, NumericMapItem item);

static Vector* gScriptContextVec = NULL;
static script_context* gScriptContext = NULL;

script_context* OpenScriptContext() {
	if(gScriptContextVec == NULL) {
		gScriptContextVec = NewVector();
		LaunchSGThread();
	}
	script_context* sctx = script_context_malloc();
	gScriptContext = sctx;
	PushVector(gScriptContextVec, sctx);
	BootstrapScriptContext(sctx);
	return sctx;
}

script_context * GetCurrentScriptContext() {
	assert(gScriptContext != NULL);
	return gScriptContext;
}

void CloseScriptContext() {
	script_context* sctx = (script_context*)PopVector(gScriptContextVec);
	script_context_free(sctx);
	gScriptContext = NULL;
	if(gScriptContextVec->Length == 0) {
		DestroySGThread();
		DeleteVector(gScriptContextVec, VectorDeleterOfNull);
		gScriptContextVec = NULL;
	} else {
		gScriptContext = (script_context*)TopVector(gScriptContextVec);
	}
}

void BootstrapScriptContext(script_context* self) {
	self->heap->AcceptBlocking++;
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
	self->bootstrap_class_loader = NewClassLoader("bootstrap", CONTENT_LIB_T);
	SpecialLoadClassLoader(self->bootstrap_class_loader, "beacon/lang/Object.bc");

	SpecialLoadClassLoader(self->bootstrap_class_loader, "beacon/lang/Int.bc");
	SpecialLoadClassLoader(self->bootstrap_class_loader, "beacon/lang/Double.bc");
	SpecialLoadClassLoader(self->bootstrap_class_loader, "beacon/lang/Char.bc");
	SpecialLoadClassLoader(self->bootstrap_class_loader, "beacon/lang/Bool.bc");
	SpecialLoadClassLoader(self->bootstrap_class_loader, "beacon/lang/Null.bc");
	SpecialLoadClassLoader(self->bootstrap_class_loader, "beacon/lang/Void.bc");

	SpecialLoadClassLoader(self->bootstrap_class_loader, "beacon/lang/Iterable.bc");
	SpecialLoadClassLoader(self->bootstrap_class_loader, "beacon/lang/Iterator.bc");
	SpecialLoadClassLoader(self->bootstrap_class_loader, "beacon/lang/Array.bc");
	SpecialLoadClassLoader(self->bootstrap_class_loader, "beacon/lang/String.bc");
	SpecialLoadClassLoader(self->bootstrap_class_loader, "beacon/lang/Console.bc");
	SpecialLoadClassLoader(self->bootstrap_class_loader, "beacon/lang/Exception.bc");
	SpecialLoadClassLoader(self->bootstrap_class_loader, "beacon/lang/StackTraceElement.bc");

	SpecialLoadClassLoader(self->bootstrap_class_loader, "beacon/lang/World.bc");
	//退避していたコンテキストを復帰
	self->heap->AcceptBlocking--;
}

void EachStaticScriptContext(script_context* self, static_each act) {
	script_context* ctx = self;
	for (int i = 0; i < ctx->type_vec->Length; i++) {
		type* e = (type*)AtVector(ctx->type_vec, i);
		if (e->tag != TYPE_CLASS_T) {
			continue;
		}
		class_* cls = e->u.class_;
		for (int j = 0; j < cls->sfield_list->Length; j++) {
			field* f = (field*)AtVector(cls->sfield_list, j);
			if(IsStaticModifier(f->modifier)) {
				act(f);
			}
		}
	}
}

void ClearScriptContext(script_context* self) {
	EachStaticScriptContext(self, ClearScriptContextImpl);
}

object* IInternScriptContext(script_context* self, int i) {
	Heap* he = self->heap;
	NumericMap* cell = GetNumericMapCell(self->n_int_map, i);
	he->AcceptBlocking++;
	if(cell == NULL) {
		object* obj = object_int_new(i);
		obj->paint = PAINT_ONEXIT_T;
		cell = PutNumericMap(self->n_int_map, i, obj);
	}
	he->AcceptBlocking--;
	return (object*)cell->Item;
}

void CacheScriptContext() {
	script_context* self = GetCurrentScriptContext();
	if(self == NULL) return;
	Heap* h = GetHeap();
	if(h != NULL) h->AcceptBlocking++;
	//すでにキャッシュされている
	if(self->pos_int_vec->Length > 0 ||
	   self->neg_int_vec->Length > 0) {
		if(h != NULL) h->AcceptBlocking--;
		   return;
	   }
	//正の数のキャッシュ
	for(int i=0; i<100; i++) {
		object* a = object_int_new(i);
		PushVector(self->pos_int_vec, a);
		a->paint = PAINT_ONEXIT_T;
	}
	//負の数のキャッシュ
	for(int i=1; i<10; i++) {
		object* a = object_int_new(-i);
		PushVector(self->neg_int_vec, a);
		a->paint = PAINT_ONEXIT_T;
	}
	if(h != NULL) h->AcceptBlocking--;
}

//private
static script_context* script_context_malloc(void) {
	script_context* ret = (script_context*)MEM_MALLOC(sizeof(script_context));
	ret->Namespacenmap = NewNumericMap();
	ret->class_loader_map = NewTreeMap();
	ret->heap = NewHeap();
	ret->type_vec = NewVector();
	ret->thread_vec = NewVector();
	ret->bootstrap_class_loader = NULL;
	ret->all_generic_vec = NewVector();
	ret->true_obj = NULL;
	ret->false_obj = NULL;
	ret->null_obj = NULL;
#if defined(_MSC_VER)
	char* path = GetAbsolutePath("script-lib/beacon/lang");
	ret->include_vec = GetFiles(path);
	MEM_FREE(path);
#else
	ret->include_vec = GetFiles("script-lib/beacon/lang");
#endif
	ret->pos_int_vec = NewVector();
	ret->neg_int_vec = NewVector();
	ret->n_int_map = NewNumericMap();
	ret->print_error = true;
	ret->abort_on_error = true;
	PushVector(ret->thread_vec, GetMainSGThread());
	return ret;
}

static void script_context_free(script_context* self) {
	int aa = CountActiveObject();
	assert(self->heap->CollectBlocking == 0);
	//全ての例外フラグをクリア
	Frame* thv = GetSGThreadFrameRef(GetCurrentSGThread(self));
	CatchVM(thv);
	DeleteClassLoader(self->bootstrap_class_loader);
	if(self->null_obj != NULL) {
		IgnoreHeap(self->heap, self->null_obj);
		self->null_obj->paint = PAINT_ONEXIT_T;
		DestroyObject(self->null_obj);
	}
	DeleteHeap(self->heap);
	DeleteVector(self->neg_int_vec, CacheScriptContext_delete);
	DeleteVector(self->pos_int_vec, CacheScriptContext_delete);
	DeleteNumericMap(self->n_int_map, script_context_mcache_delete);
	//DeleteObject(self->null_obj);
	CollectGenericType();
	DeleteVector(self->all_generic_vec, VectorDeleterOfNull);
	int x = CountActiveObject();

	DeleteVector(self->type_vec, VectorDeleterOfNull);
	DeleteVector(self->thread_vec, VectorDeleterOfNull);
	DeleteTreeMap(self->class_loader_map, script_context_DeleteClassLoader);
	//ブートストラップクラスローダを意図的に起動していないなら、
	//ここはまだNULL
	if(self->Namespacenmap != NULL) {
		EachNumericMap(self->Namespacenmap, script_context_UnlinkNamespace);
	}

	int a = CountActiveObject();
	DeleteNumericMap(self->Namespacenmap, script_context_DeleteNamespace);
	DeleteFiles(self->include_vec);
	MEM_FREE(self);
}

static void script_context_DeleteClassLoader(const char* name, TreeItem item) {
	class_loader* e = (class_loader*)item;
	DeleteClassLoader(e);
}

static void script_context_UnlinkNamespace(NumericMapKey key, NumericMapItem item) {
	Namespace* e = (Namespace*)item;
	UnlinkNamespace(e);
}

static void script_context_DeleteNamespace(NumericMapKey key, NumericMapItem item) {
	Namespace* e = (Namespace*)item;
	DeleteNamespace(e);
}

static void ClearScriptContextImpl(field* item) {
	item->static_value = GetNullObject();
}

static void CacheScriptContext_delete(VectorItem item) {
	DestroyObject((object*)item);
}

static void script_context_mcache_delete(NumericMapKey key, NumericMapItem item) {
	DestroyObject((object*)item);
}
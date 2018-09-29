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
static void script_context_class_loader_delete(const char* name, tree_item item);

static void script_context_namespace_unlink(NumericMapKey key, NumericMapItem item);
static void script_context_namespace_delete(NumericMapKey key, NumericMapItem item);
static void script_context_static_clearImpl(field* item);
static void script_context_cache_delete(VectorItem item);
static void script_context_mcache_delete(NumericMapKey key, NumericMapItem item);

static Vector* gScriptContextVec = NULL;
static script_context* gScriptContext = NULL;

script_context* script_context_open() {
	if(gScriptContextVec == NULL) {
		gScriptContextVec = NewVector();
		sg_thread_launch();
	}
	script_context* sctx = script_context_malloc();
	gScriptContext = sctx;
	PushVector(gScriptContextVec, sctx);
	script_context_bootstrap(sctx);
	return sctx;
}

script_context * script_context_get_current() {
	assert(gScriptContext != NULL);
	return gScriptContext;
}

void script_context_close() {
	script_context* sctx = (script_context*)PopVector(gScriptContextVec);
	script_context_free(sctx);
	gScriptContext = NULL;
	if(gScriptContextVec->length == 0) {
		sg_thread_destroy();
		DeleteVector(gScriptContextVec, VectorDeleterOfNull);
		gScriptContextVec = NULL;
	} else {
		gScriptContext = (script_context*)TopVector(gScriptContextVec);
	}
}

void script_context_bootstrap(script_context* self) {
	self->heap->accept_blocking++;
	//プリロード
	namespace_* beacon = namespace_create_at_root(InternString("beacon"));
	namespace_* lang = namespace_add_namespace(beacon, InternString("lang"));
	namespace_* unsafe = namespace_add_namespace(beacon, InternString("unsafe"));
	namespace_* placeholder = namespace_create_at_root(InternString("$placeholder"));
	bc_object_init();
	bc_array_init();
	bc_exception_init();
	bc_int_init();
	bc_double_init();
	bc_char_init();
	bc_string_init();
	bc_bool_init();
	bc_void_init();
	bc_console_init();
	bc_null_init();
	bc_file_init();
	bc_system_init();
	bc_locale_init();
	bc_time_init();
	//ブートストラップクラスローダー
	self->bootstrap_class_loader = class_loader_new("bootstrap", content_lib_T);
	class_loader_special(self->bootstrap_class_loader, "beacon/lang/Object.bc");

	class_loader_special(self->bootstrap_class_loader, "beacon/lang/Int.bc");
	class_loader_special(self->bootstrap_class_loader, "beacon/lang/Double.bc");
	class_loader_special(self->bootstrap_class_loader, "beacon/lang/Char.bc");
	class_loader_special(self->bootstrap_class_loader, "beacon/lang/Bool.bc");
	class_loader_special(self->bootstrap_class_loader, "beacon/lang/Null.bc");
	class_loader_special(self->bootstrap_class_loader, "beacon/lang/Void.bc");

	class_loader_special(self->bootstrap_class_loader, "beacon/lang/Iterable.bc");
	class_loader_special(self->bootstrap_class_loader, "beacon/lang/Iterator.bc");
	class_loader_special(self->bootstrap_class_loader, "beacon/lang/Array.bc");
	class_loader_special(self->bootstrap_class_loader, "beacon/lang/String.bc");
	class_loader_special(self->bootstrap_class_loader, "beacon/lang/Console.bc");
	class_loader_special(self->bootstrap_class_loader, "beacon/lang/Exception.bc");
	class_loader_special(self->bootstrap_class_loader, "beacon/lang/StackTraceElement.bc");

	class_loader_special(self->bootstrap_class_loader, "beacon/lang/World.bc");
	//退避していたコンテキストを復帰
	self->heap->accept_blocking--;
}

void script_context_static_each(script_context* self, static_each act) {
	script_context* ctx = self;
	for (int i = 0; i < ctx->type_vec->length; i++) {
		type* e = (type*)AtVector(ctx->type_vec, i);
		if (e->tag != type_class_T) {
			continue;
		}
		class_* cls = e->u.class_;
		for (int j = 0; j < cls->sfield_list->length; j++) {
			field* f = (field*)AtVector(cls->sfield_list, j);
			if(modifier_is_static(f->modifier)) {
				act(f);
			}
		}
	}
}

void script_context_static_clear(script_context* self) {
	script_context_static_each(self, script_context_static_clearImpl);
}

object* script_context_iintern(script_context* self, int i) {
	heap* he = self->heap;
	NumericMap* cell = GetNumericMapCell(self->n_int_map, i);
	he->accept_blocking++;
	if(cell == NULL) {
		object* obj = object_int_new(i);
		obj->paint = paint_onexit_T;
		cell = PutNumericMap(self->n_int_map, i, obj);
	}
	he->accept_blocking--;
	return (object*)cell->item;
}

void script_context_cache() {
	script_context* self = script_context_get_current();
	if(self == NULL) return;
	heap* h = heap_get();
	if(h != NULL) h->accept_blocking++;
	//すでにキャッシュされている
	if(self->pos_int_vec->length > 0 ||
	   self->neg_int_vec->length > 0) {
		if(h != NULL) h->accept_blocking--;
		   return;
	   }
	//正の数のキャッシュ
	for(int i=0; i<100; i++) {
		object* a = object_int_new(i);
		PushVector(self->pos_int_vec, a);
		a->paint = paint_onexit_T;
	}
	//負の数のキャッシュ
	for(int i=1; i<10; i++) {
		object* a = object_int_new(-i);
		PushVector(self->neg_int_vec, a);
		a->paint = paint_onexit_T;
	}
	if(h != NULL) h->accept_blocking--;
}

//private
static script_context* script_context_malloc(void) {
	script_context* ret = (script_context*)MEM_MALLOC(sizeof(script_context));
	ret->namespace_nmap = NewNumericMap();
	ret->class_loader_map = NewTreeMap();
	ret->heap = heap_new();
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
	PushVector(ret->thread_vec, sg_thread_main());
	return ret;
}

static void script_context_free(script_context* self) {
	int aa = object_count();
	assert(self->heap->collect_blocking == 0);
	//全ての例外フラグをクリア
	frame* thv = sg_thread_get_frame_ref(sg_thread_current(self));
	vm_catch(thv);
	class_loader_delete(self->bootstrap_class_loader);
	if(self->null_obj != NULL) {
		heap_ignore(self->heap, self->null_obj);
		self->null_obj->paint = paint_onexit_T;
		object_destroy(self->null_obj);
	}
	heap_delete(self->heap);
	DeleteVector(self->neg_int_vec, script_context_cache_delete);
	DeleteVector(self->pos_int_vec, script_context_cache_delete);
	DeleteNumericMap(self->n_int_map, script_context_mcache_delete);
	//object_delete(self->null_obj);
	generic_type_collect();
	DeleteVector(self->all_generic_vec, VectorDeleterOfNull);
	int x = object_count();

	DeleteVector(self->type_vec, VectorDeleterOfNull);
	DeleteVector(self->thread_vec, VectorDeleterOfNull);
	DeleteTreeMap(self->class_loader_map, script_context_class_loader_delete);
	//ブートストラップクラスローダを意図的に起動していないなら、
	//ここはまだNULL
	if(self->namespace_nmap != NULL) {
		EachNumericMap(self->namespace_nmap, script_context_namespace_unlink);
	}

	int a = object_count();
	DeleteNumericMap(self->namespace_nmap, script_context_namespace_delete);
	DeleteFiles(self->include_vec);
	MEM_FREE(self);
}

static void script_context_class_loader_delete(const char* name, tree_item item) {
	class_loader* e = (class_loader*)item;
	class_loader_delete(e);
}

static void script_context_namespace_unlink(NumericMapKey key, NumericMapItem item) {
	namespace_* e = (namespace_*)item;
	namespace_unlink(e);
}

static void script_context_namespace_delete(NumericMapKey key, NumericMapItem item) {
	namespace_* e = (namespace_*)item;
	namespace_delete(e);
}

static void script_context_static_clearImpl(field* item) {
	item->static_value = object_get_null();
}

static void script_context_cache_delete(VectorItem item) {
	object_destroy((object*)item);
}

static void script_context_mcache_delete(NumericMapKey key, NumericMapItem item) {
	object_destroy((object*)item);
}
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

static void script_context_namespace_unlink(numeric_key key, numeric_map_item item);
static void script_context_namespace_delete(numeric_key key, numeric_map_item item);
static void script_context_static_clearImpl(field* item);
static void script_context_cache_delete(vector_item item);
static void script_context_mcache_delete(numeric_key key, numeric_map_item item);

static vector* gScriptContextVec = NULL;
static script_context* gScriptContext = NULL;

script_context* script_context_open() {
	if(gScriptContextVec == NULL) {
		gScriptContextVec = vector_new();
	}
	sg_thread_launch();
	script_context* sctx = script_context_malloc();
	gScriptContext = sctx;
	vector_push(gScriptContextVec, sctx);
	script_context_bootstrap(sctx);
	return sctx;
}

script_context * script_context_get_current() {
	return gScriptContext;
}

void script_context_close() {
	script_context* sctx = (script_context*)vector_pop(gScriptContextVec);
	script_context_free(sctx);
	gScriptContext = NULL;
	if(gScriptContextVec->length == 0) {
		sg_thread_destroy();
		vector_delete(gScriptContextVec, vector_deleter_null);
		gScriptContextVec = NULL;
	} else {
		gScriptContext = (script_context*)vector_top(gScriptContextVec);
	}
}

void script_context_bootstrap(script_context* self) {
	//一時的に現在のコンテキストを無効にして、
	//引数のコンテキストを設定する
	//FIXME:スタック?
	self->heap->accept_blocking++;
	//プリロード
	namespace_* beacon = namespace_create_at_root(string_pool_intern("beacon"));
	namespace_* lang = namespace_add_namespace(beacon, string_pool_intern("lang"));
	namespace_* unsafe = namespace_add_namespace(beacon, string_pool_intern("unsafe"));
	namespace_* placeholder = namespace_create_at_root(string_pool_intern("$placeholder"));
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
	self->bootstrap_class_loader = class_loader_new("bootstrap", content_lib);
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
		type* e = (type*)vector_at(ctx->type_vec, i);
		if (e->tag != type_class) {
			continue;
		}
		class_* cls = e->u.class_;
		for (int j = 0; j < cls->sfield_list->length; j++) {
			field* f = (field*)vector_at(cls->sfield_list, j);
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
	numeric_map* cell = numeric_map_cell(self->n_int_map, i);
	he->accept_blocking++;
	if(cell == NULL) {
		object* obj = object_int_new(i);
		obj->paint = paint_onexit;
		cell = numeric_map_put(self->n_int_map, i, obj);
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
		vector_push(self->pos_int_vec, a);
		a->paint = paint_onexit;
	}
	//負の数のキャッシュ
	for(int i=1; i<10; i++) {
		object* a = object_int_new(-i);
		vector_push(self->neg_int_vec, a);
		a->paint = paint_onexit;
	}
	if(h != NULL) h->accept_blocking--;
}

//private
static script_context* script_context_malloc(void) {
	script_context* ret = (script_context*)MEM_MALLOC(sizeof(script_context));
	ret->namespace_nmap = numeric_map_new();
	ret->class_loader_map = tree_map_new();
	ret->heap = heap_new();
	ret->type_vec = vector_new();
	ret->thread_vec = vector_new();
	ret->bootstrap_class_loader = NULL;
	ret->all_generic_vec = vector_new();
	ret->oTrue = NULL;
	ret->oFalse = NULL;
	ret->oNull = NULL;
	ret->include_vec = io_list_files("script-lib/beacon/lang");
	ret->pos_int_vec = vector_new();
	ret->neg_int_vec = vector_new();
	ret->n_int_map = numeric_map_new();
	vector_push(ret->thread_vec, sg_thread_main());
	return ret;
}

static void script_context_free(script_context* self) {
	int aa = object_count();
	assert(self->heap->collect_blocking == 0);
	//全ての例外フラグをクリア
	frame* thv = sg_thread_get_frame_ref(sg_thread_current(self));
	vm_catch(thv);
	class_loader_delete(self->bootstrap_class_loader);
	if(self->oNull != NULL) {
		heap_ignore(self->heap, self->oNull);
		self->oNull->paint = paint_onexit;
		object_destroy(self->oNull);
	}
	heap_delete(self->heap);
	vector_delete(self->neg_int_vec, script_context_cache_delete);
	vector_delete(self->pos_int_vec, script_context_cache_delete);
	numeric_map_delete(self->n_int_map, script_context_mcache_delete);
	//object_delete(self->oNull);
	generic_type_collect();
	vector_delete(self->all_generic_vec, vector_deleter_null);
	int x = object_count();

	vector_delete(self->type_vec, vector_deleter_null);
	vector_delete(self->thread_vec, vector_deleter_null);
	tree_map_delete(self->class_loader_map, script_context_class_loader_delete);
	//ブートストラップクラスローダを意図的に起動していないなら、
	//ここはまだNULL
	if(self->namespace_nmap != NULL) {
		numeric_map_each(self->namespace_nmap, script_context_namespace_unlink);
	}

	int a = object_count();
	numeric_map_delete(self->namespace_nmap, script_context_namespace_delete);
	io_list_files_delete(self->include_vec);
	MEM_FREE(self);
}

static void script_context_class_loader_delete(const char* name, tree_item item) {
	class_loader* e = (class_loader*)item;
	class_loader_delete(e);
}

static void script_context_namespace_unlink(numeric_key key, numeric_map_item item) {
	namespace_* e = (namespace_*)item;
	namespace_unlink(e);
}

static void script_context_namespace_delete(numeric_key key, numeric_map_item item) {
	namespace_* e = (namespace_*)item;
	namespace_delete(e);
}

static void script_context_static_clearImpl(field* item) {
	item->static_value = object_get_null();
}

static void script_context_cache_delete(vector_item item) {
	object_destroy((object*)item);
}

static void script_context_mcache_delete(numeric_key key, numeric_map_item item) {
	object_destroy((object*)item);
}
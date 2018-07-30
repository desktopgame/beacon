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
static script_context* script_context_new();
static script_context* script_context_check_init(void);
static void script_context_launch(script_context* self);
static script_context* script_context_malloc(void);
static void script_context_free(script_context* self);
static void script_context_class_loader_delete(const char* name, tree_item item);

static void script_context_namespace_unlink(numeric_key key, numeric_map_item item);
static void script_context_namespace_delete(numeric_key key, numeric_map_item item);
static void script_context_static_clearImpl(field* item);
static void script_context_cache_delete(vector_item item);

static script_context* gScriptContext = NULL;
static script_context* gScriptContextCurrent = NULL;
static bool gScriptBootstrap = true;

void script_context_open() {
	sg_thread_launch();
	script_context_check_init();
}

script_context * script_context_add() {
	script_context* ret = script_context_new();
	script_context* ptr = gScriptContext;
	while (ptr->next != NULL) {
		ptr = ptr->next;
	}
	ptr->next = ret;
	ret->prev = ptr;
	return ret;
}

script_context * script_context_remove(script_context * self) {
	script_context* next = NULL;
	if (self->prev != NULL) {
		next = self->prev;
	} else if (self->next != NULL) {
		next = self->next;
	}
	if (self->prev != NULL) self->prev->next = self->next;
	if (self->next != NULL)  self->next->prev = self->prev;
	script_context_free(self);
	script_context_set_current(next);
	return next;
}

script_context * script_context_back() {
	script_context* g = script_context_check_init();
	if (g->next == NULL) {
		return g;
	}
	script_context* pointee = g;
	while (1) {
		if (pointee->next == NULL) {
			break;
		}
		pointee = pointee->next;
	}
	return pointee;
}

void script_context_set_current(script_context * self) {
	gScriptContextCurrent = self;
}

script_context * script_context_get_current() {
	return gScriptContextCurrent;
}

void script_context_delete(script_context * self) {
	assert(self != NULL);
	assert(self != gScriptContext);
	//前の要素がある
	if (self->prev != NULL) {
		//次の要素がある
		if (self->next != NULL) {
			self->prev->next = self->next;
		} else {
			self->prev->next = NULL;
		}
	}
	//次の要素がある
	if (self->next != NULL) {
		//前の要素がある
		if (self->prev != NULL) {
			self->next->prev = self->prev;
		} else {
			self->next->prev = NULL;
		}
	}
	script_context_free(self);
}

void script_context_close() {
	script_context* pointee = gScriptContext;
	while (1) {
		if (!pointee) {
			break;
		}
		script_context* temp = pointee;
		pointee = pointee->next;
		script_context_free(temp);
		//free(temp);
	}
	gScriptContext = NULL;
	gScriptContextCurrent = NULL;
	sg_thread_destroy();
}

void script_context_bootstrap(script_context* self) {
	//一時的に現在のコンテキストを無効にして、
	//引数のコンテキストを設定する
	//FIXME:スタック?
	script_context* selected = script_context_get_current();
	script_context_set_current(self);
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
	//ブートストラップクラスローダー
	self->bootstrap_class_loader = class_loader_new(content_lib);
	self->bootstrap_class_loader->filename = text_strdup("bootstrap");
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
	script_context_set_current(selected);
}

void script_context_set_bootstrap(bool b) {
	gScriptBootstrap = b;
}

bool script_context_get_bootstrap() {
	return gScriptBootstrap;
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

void script_context_cache() {
	script_context* self = script_context_get_current();
	if(self == NULL) return;
	heap* h = heap_get();
	if(h != NULL) h->accept_blocking++;
	//すでにキャッシュされている
	if(self->pos_int_vec->length > 0 ||
	   self->neg_int_vec->length > 0) {
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
static script_context* script_context_new() {
	script_context* ret = script_context_malloc();
	script_context_launch(ret);
	return ret;
}

static script_context* script_context_check_init(void) {
	if (gScriptContext == NULL) {
		gScriptContext = script_context_malloc();
		gScriptContextCurrent = gScriptContext;
		script_context_launch(gScriptContext);
	}
	return gScriptContext;
}

static void script_context_launch(script_context* self) {
	if(!gScriptBootstrap) {
		return;
	}
	script_context_bootstrap(self);
}

static script_context* script_context_malloc(void) {
	script_context* ret = (script_context*)MEM_MALLOC(sizeof(script_context));
	ret->parser_stack = NULL;
	ret->namespace_nmap = numeric_map_new();
	ret->class_loader_map = tree_map_new();
	ret->heap = heap_new();
	ret->type_vec = vector_new();
	ret->prev = NULL;
	ret->next = NULL;
	ret->thread_vec = vector_new();
	ret->bootstrap_class_loader = NULL;
	ret->all_generic_vec = vector_new();
	ret->oTrue = NULL;
	ret->oFalse = NULL;
	ret->oNull = NULL;
	ret->include_vec = io_list_files("beacon/lang");
	ret->pos_int_vec = vector_new();
	ret->neg_int_vec = vector_new();
	vector_push(ret->thread_vec, sg_thread_main());
	return ret;
}

static void script_context_free(script_context* self) {
	int aa = object_count();
	assert(heap_get()->collect_blocking == 0);
	//全ての例外フラグをクリア
	frame* thv = sg_thread_get_frame_ref(sg_thread_current());
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
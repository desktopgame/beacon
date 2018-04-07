#include "script_context.h"
#include "../util/logger.h"
#include "heap.h"
#include "namespace.h"
#include "type_interface.h"
#include "type/class_impl.h"
#include "class_loader.h"
#include <stdlib.h>
#include <assert.h>
#include "generic_type.h"
#include "../util/mem.h"
#include "../lib/sg_library_interface.h"
#include "../thread/thread.h"
#include "../util/text.h"
//proto
static script_context* script_context_new();
static script_context* script_context_check_init(void);
static void script_context_launch(script_context* self);
static script_context* script_context_malloc(void);
static void script_context_free(script_context* self);
static void script_context_class_loader_delete(vector_item item);

static void script_context_namespace_unlink(char* name, tree_item item);
static void script_context_namespace_delete(tree_item item);

static script_context* gScriptContext = NULL;
static script_context* gScriptContextCurrent = NULL;
static bool gScriptBootstrap = true;

void script_context_open() {
	sg_thread_launch();
	script_context_check_init();
	INFO("script-context open");
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
	INFO("script-context close");
	sg_thread_destroy();
}

void script_context_bootstrap(script_context* self) {
	//一時的に現在のコンテキストを無効にして、
	//引数のコンテキストを設定する
	//FIXME:スタック?
	script_context* selected = script_context_get_current();
	script_context_set_current(self);
	self->heap->blocking++;
	//プリロード
	namespace_* signal = namespace_create_at_root("signal");
	namespace_* lang = namespace_add_namespace(signal, "lang");
	sg_object_init();
	sg_array_init();
	sg_exception_init();
	sg_int_init();
	sg_double_init();
	sg_char_init();
	sg_string_init();
	sg_bool_init();
	sg_void_init();
	sg_console_init();
	sg_null_init();
	//ブートストラップクラスローダー
	self->bootstrap_class_loader = class_loader_new();
	self->bootstrap_class_loader->filename = text_strdup("bootstrap");
	class_loader_rsub(self->bootstrap_class_loader, "Object.signal");

	class_loader_rsub(self->bootstrap_class_loader, "Int.signal");
	class_loader_rsub(self->bootstrap_class_loader, "Double.signal");
	class_loader_rsub(self->bootstrap_class_loader, "Char.signal");
	class_loader_rsub(self->bootstrap_class_loader, "Bool.signal");
	class_loader_rsub(self->bootstrap_class_loader, "Null.signal");
	class_loader_rsub(self->bootstrap_class_loader, "Void.signal");

	class_loader_rsub(self->bootstrap_class_loader, "Array.signal");
	class_loader_rsub(self->bootstrap_class_loader, "String.signal");
	class_loader_rsub(self->bootstrap_class_loader, "Console.signal");
	class_loader_rsub(self->bootstrap_class_loader, "Exception.signal");
	class_loader_rsub(self->bootstrap_class_loader, "StackTraceElement.signal");
	//退避していたコンテキストを復帰
	self->heap->blocking--;
	script_context_set_current(selected);
}

void script_context_set_bootstrap(bool b) {
	gScriptBootstrap = b;
}

bool script_context_get_bootstrap() {
	return gScriptBootstrap;
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
	ret->namespace_map = NULL;
	ret->class_loader_map = tree_map_new();
	ret->heap = heap_new();
	ret->type_vec = vector_new();
	ret->prev = NULL;
	ret->next = NULL;
	ret->thread_vec = vector_new();
	ret->bootstrap_class_loader = NULL;
	ret->all_generic_vec = vector_new();
	vector_push(ret->thread_vec, sg_thread_main());
	return ret;
}

static void script_context_free(script_context* self) {
	int aa = object_count();

	class_loader_delete(self->bootstrap_class_loader);
	heap_delete(self->heap);
	generic_type_collect();
	int x = object_count();

	vector_delete(self->type_vec, vector_deleter_null);
	vector_delete(self->thread_vec, vector_deleter_null);
	tree_map_delete(self->class_loader_map, script_context_class_loader_delete);
	//ブートストラップクラスローダを意図的に起動していないなら、
	//ここはまだNULL
	if(self->namespace_map != NULL) {
		tree_map_each(self->namespace_map, script_context_namespace_unlink);
	}

	int a = object_count();
//	text_printfln("---");
//	mem_dump();
//	text_printfln("---");
	tree_map_delete(self->namespace_map, script_context_namespace_delete);
	MEM_FREE(self);
}

static void script_context_class_loader_delete(vector_item item) {
	class_loader* e = (class_loader*)item;
	class_loader_delete(e);
}

static void script_context_namespace_unlink(char* name, tree_item item) {
	namespace_* e = (namespace_*)item;
	namespace_unlink(e);
}

static void script_context_namespace_delete(tree_item item) {
	namespace_* e = (namespace_*)item;
	namespace_delete(e);
}


#include "script_context.h"
#include "../util/logger.h"
#include "heap.h"
#include "namespace.h"
#include "type_interface.h"
#include "type/class_impl.h"
#include "class_loader.h"
#include <stdlib.h>
#include <assert.h>
#include "../util/mem.h"
#include "../lib/sg_library_interface.h"
//proto
static script_context* script_context_check_init(void);
static void script_context_launch(script_context* self);
static script_context* script_context_malloc(void);
static script_context* script_context_free(script_context* self);
static void script_context_class_loader_delete(vector_item item);
static void script_context_namespace_delete(vector_item item);

static script_context* gScriptContext = NULL;
static script_context* gScriptContextCurrent = NULL;

void script_context_open() {
	script_context_check_init();
	INFO("script-context open");
}

script_context* script_context_new() {
	script_context* ret = script_context_malloc();
	ret->prev = script_context_back();
	script_context_launch(ret);
	return ret;
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
}

//private
static script_context* script_context_check_init(void) {
	if (gScriptContext == NULL) {
		gScriptContext = script_context_malloc();
		gScriptContextCurrent = gScriptContext;
		script_context_launch(gScriptContext);
	}
	return gScriptContext;
}

static void script_context_launch(script_context* self) {
	//一時的に現在のコンテキストを無効にして、
	//引数のコンテキストを設定する
	//FIXME:スタック?
	script_context* selected = script_context_get_current();
	script_context_set_current(self);
	//プリロード
	namespace_* signal = namespace_create_at_root("signal");
	namespace_* lang = namespace_add_namespace(signal, "lang");
	sg_int_init();
	sg_double_init();
	sg_char_init();
	sg_string_init();
	sg_bool_init();
	sg_void_init();
	sg_console_init();
	//退避していたコンテキストを復帰
	script_context_set_current(selected);
}

static script_context* script_context_malloc(void) {
	script_context* ret = (script_context*)MEM_MALLOC(sizeof(script_context));
	ret->parserStack = NULL;
	ret->namespaceMap = NULL;
	ret->classLoaderMap = tree_map_new();
	ret->heap = heap_new();
	ret->type_vec = vector_new();
	ret->prev = NULL;
	ret->next = NULL;
	return ret;
}

static script_context* script_context_free(script_context* self) {
	vector_delete(self->type_vec, vector_deleter_null);
	tree_map_delete(self->classLoaderMap, script_context_class_loader_delete);
	tree_map_delete(self->namespaceMap, script_context_namespace_delete);
	heap_delete(self->heap);
	MEM_FREE(self);
}

static void script_context_class_loader_delete(vector_item item) {
	class_loader* e = (class_loader*)item;
	class_loader_delete(e);
}

static void script_context_namespace_delete(vector_item item) {
	namespace_* e = (namespace_*)item;
	namespace_delete(e);
}
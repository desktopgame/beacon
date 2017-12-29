#include "heap.h"
#include "script_context.h"
#include <stdlib.h>

//proto
static void heap_delete_object(vector_item item);

heap * heap_new() {
	heap* ret = (heap*)malloc(sizeof(heap));
	ret->threshold = 16;
	ret->object_vec = vector_new();
	return ret;
}

heap * heap_get() {
	script_context* ctx = script_context_get_current();
	return ctx->heap;
}

void heap_add(heap * self, object * obj) {
	vector_push(self->object_vec, obj);
}

void heap_gc(heap * self) {
}

void heap_delete(heap * self) {
	vector_delete(self->object_vec, heap_delete_object);
	free(self);
}

//private
static void heap_delete_object(vector_item item) {
	object* e = (object*)item;
	object_delete(e);
}
#include "heap.h"
#include "script_context.h"
#include <stdlib.h>
#include <assert.h>
#include "../util/mem.h"
#include "../util/text.h"
#include "../env/generic_type.h"
#include "../thread/thread.h"
#include "../vm/vm.h"

//proto
static void heap_delete_object(vector_item item);
static void gc_clear(heap* self);
static void gc_mark(heap* self);
static void gc_sweep(heap* self);
static void gc_delete(vector_item item);


heap * heap_new() {
	heap* ret = (heap*)MEM_MALLOC(sizeof(heap));
	ret->object_vec = vector_new();
	ret->accept_blocking = 0;
	ret->collect_blocking = 0;
	return ret;
}

heap * heap_get() {
	script_context* ctx = script_context_get_current();
	if(ctx == NULL) { return NULL; }
	return ctx->heap;
}

void heap_add(heap * self, object * obj) {
	if(self == NULL) {
		obj->paint = paint_onexit_T;
		return;
	}
	if (self->accept_blocking > 0) {
		obj->paint = paint_onexit_T;
		return;
	}
	vector_push(self->object_vec, obj);
}

void heap_gc(heap * self) {
	if(self->collect_blocking > 0) {
		return;
	}
	gc_clear(self);
	gc_mark(self);
	gc_sweep(self);
}

void heap_ignore(heap* self, object* o) {
	int i = vector_find(self->object_vec, o);
	if(i >= 0) {
		vector_remove(self->object_vec, i);
	}
}

void heap_delete(heap * self) {
	vector_delete(self->object_vec,heap_delete_object);
	MEM_FREE(self);
}

void heap_dump(heap* self) {
	printf("heap dump:\n");
	for(int i=0; i<self->object_vec->length; i++) {
		object* a = vector_at(self->object_vec, i);
		printf("    ");
		generic_type_print(a->gtype);
		printf("\n");
	}
}

//private
static void heap_delete_object(vector_item item) {
	object* e = (object*)item;
	object_delete(e);
}

static void gc_clear(heap* self) {
	for (int i = 0; i < self->object_vec->length; i++) {
		object* e = (object*)vector_at(self->object_vec, i);
		if (e->paint == paint_marked_T) {
			e->paint = paint_unmarked_T;
		}
	}
}

static void gc_mark(heap* self) {
	//今はまだマルチスレッドに対応していないので、
	//とりあえず実行中のスレッドのみを対象とする
	sg_thread* th = sg_thread_current(script_context_get_current());
	frame* top = sg_thread_get_frame_ref(th);
	assert(top != NULL);
	frame_markall(top);

	//true/false/nullは常にマーク
	object_get_true()->paint = paint_marked_T;
	object_get_false()->paint = paint_marked_T;
	object_get_null()->paint = paint_marked_T;
}

static void gc_sweep(heap* self) {
	int sweep = 0;
	vector* recycle = vector_new();
	vector* garabage = vector_new();
	for (int i = 0; i < self->object_vec->length; i++) {
		object* e = (object*)vector_at(self->object_vec, i);
		if (e->paint == paint_unmarked_T) {
			vector_push(garabage, e);
			sweep++;
		} else {
			vector_push(recycle, e);
		}
	}
	vector_delete(self->object_vec, vector_deleter_null);
	vector_delete(garabage, gc_delete);
	self->object_vec = recycle;
}

static void gc_delete(vector_item item) {
	object* e = (object*)item;
	object_delete(e);
}
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
static void DeleteHeap_object(VectorItem item);
static void gc_clear(heap* self);
static void gc_mark(heap* self);
static void gc_sweep(heap* self);
static void gc_delete(VectorItem item);


heap * NewHeap() {
	heap* ret = (heap*)MEM_MALLOC(sizeof(heap));
	ret->object_vec = NewVector();
	ret->accept_blocking = 0;
	ret->collect_blocking = 0;
	return ret;
}

heap * GetHeap() {
	script_context* ctx = GetCurrentScriptContext();
	if(ctx == NULL) { return NULL; }
	return ctx->heap;
}

void AddHeap(heap * self, object * obj) {
	if(self == NULL) {
		obj->paint = PAINT_ONEXIT_T;
		return;
	}
	if (self->accept_blocking > 0) {
		obj->paint = PAINT_ONEXIT_T;
		return;
	}
	PushVector(self->object_vec, obj);
}

void CollectHeap(heap * self) {
	if(self->collect_blocking > 0) {
		return;
	}
	gc_clear(self);
	gc_mark(self);
	gc_sweep(self);
}

void IgnoreHeap(heap* self, object* o) {
	int i = FindVector(self->object_vec, o);
	if(i >= 0) {
		RemoveVector(self->object_vec, i);
	}
}

void DeleteHeap(heap * self) {
	DeleteVector(self->object_vec,DeleteHeap_object);
	MEM_FREE(self);
}

void DumpHeap(heap* self) {
	printf("heap dump:\n");
	for(int i=0; i<self->object_vec->Length; i++) {
		object* a = AtVector(self->object_vec, i);
		printf("    ");
		PrintGenericType(a->gtype);
		printf("\n");
	}
}

//private
static void DeleteHeap_object(VectorItem item) {
	object* e = (object*)item;
	DeleteObject(e);
}

static void gc_clear(heap* self) {
	for (int i = 0; i < self->object_vec->Length; i++) {
		object* e = (object*)AtVector(self->object_vec, i);
		if (e->paint == PAINT_MARKED_T) {
			e->paint = PAINT_UNMARKED_T;
		}
	}
}

static void gc_mark(heap* self) {
	//今はまだマルチスレッドに対応していないので、
	//とりあえず実行中のスレッドのみを対象とする
	sg_thread* th = GetCurrentSGThread(GetCurrentScriptContext());
	frame* top = GetSGThreadFrameRef(th);
	assert(top != NULL);
	MarkAllFrame(top);

	//true/false/nullは常にマーク
	GetTrueObject()->paint = PAINT_MARKED_T;
	GetFalseObject()->paint = PAINT_MARKED_T;
	GetNullObject()->paint = PAINT_MARKED_T;
}

static void gc_sweep(heap* self) {
	int sweep = 0;
	Vector* recycle = NewVector();
	Vector* garabage = NewVector();
	for (int i = 0; i < self->object_vec->Length; i++) {
		object* e = (object*)AtVector(self->object_vec, i);
		if (e->paint == PAINT_UNMARKED_T) {
			PushVector(garabage, e);
			sweep++;
		} else {
			PushVector(recycle, e);
		}
	}
	DeleteVector(self->object_vec, VectorDeleterOfNull);
	DeleteVector(garabage, gc_delete);
	self->object_vec = recycle;
}

static void gc_delete(VectorItem item) {
	object* e = (object*)item;
	DeleteObject(e);
}
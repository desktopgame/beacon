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
static void gc_clear(Heap* self);
static void gc_mark(Heap* self);
static void gc_sweep(Heap* self);
static void gc_delete(VectorItem item);


Heap * NewHeap() {
	Heap* ret = (Heap*)MEM_MALLOC(sizeof(Heap));
	ret->Objects = NewVector();
	ret->AcceptBlocking= 0;
	ret->CollectBlocking = 0;
	return ret;
}

Heap * GetHeap() {
	script_context* ctx = GetCurrentScriptContext();
	if(ctx == NULL) { return NULL; }
	return ctx->heap;
}

void AddHeap(Heap * self, object * obj) {
	if(self == NULL) {
		obj->paint = PAINT_ONEXIT_T;
		return;
	}
	if (self->AcceptBlocking > 0) {
		obj->paint = PAINT_ONEXIT_T;
		return;
	}
	PushVector(self->Objects, obj);
}

void CollectHeap(Heap * self) {
	if(self->CollectBlocking > 0) {
		return;
	}
	gc_clear(self);
	gc_mark(self);
	gc_sweep(self);
}

void IgnoreHeap(Heap* self, object* o) {
	int i = FindVector(self->Objects, o);
	if(i >= 0) {
		RemoveVector(self->Objects, i);
	}
}

void DeleteHeap(Heap * self) {
	DeleteVector(self->Objects,DeleteHeap_object);
	MEM_FREE(self);
}

void DumpHeap(Heap* self) {
	printf("heap dump:\n");
	for(int i=0; i<self->Objects->Length; i++) {
		object* a = AtVector(self->Objects, i);
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

static void gc_clear(Heap* self) {
	for (int i = 0; i < self->Objects->Length; i++) {
		object* e = (object*)AtVector(self->Objects, i);
		if (e->paint == PAINT_MARKED_T) {
			e->paint = PAINT_UNMARKED_T;
		}
	}
}

static void gc_mark(Heap* self) {
	//今はまだマルチスレッドに対応していないので、
	//とりあえず実行中のスレッドのみを対象とする
	ScriptThread* th = GetCurrentSGThread(GetCurrentScriptContext());
	Frame* top = GetSGThreadFrameRef(th);
	assert(top != NULL);
	MarkAllFrame(top);

	//true/false/nullは常にマーク
	GetTrueObject()->paint = PAINT_MARKED_T;
	GetFalseObject()->paint = PAINT_MARKED_T;
	GetNullObject()->paint = PAINT_MARKED_T;
}

static void gc_sweep(Heap* self) {
	int sweep = 0;
	Vector* recycle = NewVector();
	Vector* garabage = NewVector();
	for (int i = 0; i < self->Objects->Length; i++) {
		object* e = (object*)AtVector(self->Objects, i);
		if (e->paint == PAINT_UNMARKED_T) {
			PushVector(garabage, e);
			sweep++;
		} else {
			PushVector(recycle, e);
		}
	}
	DeleteVector(self->Objects, VectorDeleterOfNull);
	DeleteVector(garabage, gc_delete);
	self->Objects = recycle;
}

static void gc_delete(VectorItem item) {
	object* e = (object*)item;
	DeleteObject(e);
}
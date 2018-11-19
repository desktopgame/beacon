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
static void delete_object(VectorItem item);
static void gc_clear(bc_Heap* self);
static void gc_mark(bc_Heap* self);
static void gc_sweep(bc_Heap* self);
static void gc_delete(VectorItem item);


bc_Heap * bc_NewHeap() {
	bc_Heap* ret = (bc_Heap*)MEM_MALLOC(sizeof(bc_Heap));
	ret->Objects = NewVector();
	ret->AcceptBlocking= 0;
	ret->CollectBlocking = 0;
	return ret;
}

bc_Heap * bc_GetHeap() {
	bc_ScriptContext* ctx = bc_GetCurrentScriptContext();
	if(ctx == NULL) { return NULL; }
	return ctx->Heap;
}

void bc_AddHeap(bc_Heap * self, bc_Object * obj) {
	if(self == NULL) {
		obj->Paint = PAINT_ONEXIT_T;
		return;
	}
	if (self->AcceptBlocking > 0) {
		obj->Paint = PAINT_ONEXIT_T;
		return;
	}
	PushVector(self->Objects, obj);
}

void bc_CollectHeap(bc_Heap * self) {
	if(self->CollectBlocking > 0) {
		return;
	}
	gc_clear(self);
	gc_mark(self);
	gc_sweep(self);
}

void bc_IgnoreHeap(bc_Heap* self, bc_Object* o) {
	int i = FindVector(self->Objects, o);
	if(i >= 0) {
		RemoveVector(self->Objects, i);
	}
}

void bc_DeleteHeap(bc_Heap * self) {
	DeleteVector(self->Objects,delete_object);
	MEM_FREE(self);
}

void bc_DumpHeap(bc_Heap* self) {
	printf("heap dump:\n");
	for(int i=0; i<self->Objects->Length; i++) {
		bc_Object* a = AtVector(self->Objects, i);
		printf("    ");
		bc_PrintGenericType(a->GType);
		printf("\n");
	}
}

//private
static void delete_object(VectorItem item) {
	bc_Object* e = (bc_Object*)item;
	bc_DeleteObject(e);
}

static void gc_clear(bc_Heap* self) {
	for (int i = 0; i < self->Objects->Length; i++) {
		bc_Object* e = (bc_Object*)AtVector(self->Objects, i);
		if (e->Paint == PAINT_MARKED_T) {
			e->Paint = PAINT_UNMARKED_T;
		}
	}
}

static void gc_mark(bc_Heap* self) {
	//今はまだマルチスレッドに対応していないので、
	//とりあえず実行中のスレッドのみを対象とする
	ScriptThread* th = GetCurrentSGThread(bc_GetCurrentScriptContext());
	Frame* top = GetSGThreadFrameRef(th);
	assert(top != NULL);
	MarkAllFrame(top);

	//true/false/nullは常にマーク
	bc_GetTrueObject()->Paint = PAINT_MARKED_T;
	bc_GetFalseObject()->Paint = PAINT_MARKED_T;
	bc_GetNullObject()->Paint = PAINT_MARKED_T;
}

static void gc_sweep(bc_Heap* self) {
	int sweep = 0;
	Vector* recycle = NewVector();
	Vector* garabage = NewVector();
	for (int i = 0; i < self->Objects->Length; i++) {
		bc_Object* e = (bc_Object*)AtVector(self->Objects, i);
		if (e->Paint == PAINT_UNMARKED_T) {
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
	bc_Object* e = (bc_Object*)item;
	bc_DeleteObject(e);
}
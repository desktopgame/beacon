#include "heap.h"
#include <assert.h>
#include <stdlib.h>
#include "../env/generic_type.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../vm/script_thread.h"
#include "../vm/vm.h"
#include "script_context.h"

// proto
static void delete_object(bc_VectorItem item);
static void gc_clear(bc_Heap* self);
static void gc_mark(bc_Heap* self);
static void gc_sweep(bc_Heap* self);
static void gc_delete(bc_VectorItem item);

bc_Heap* bc_NewHeap() {
        bc_Heap* ret = (bc_Heap*)MEM_MALLOC(sizeof(bc_Heap));
        ret->Objects = bc_NewVector();
        ret->AcceptBlocking = 0;
        ret->CollectBlocking = 0;
        return ret;
}

bc_Heap* bc_GetHeap() {
        bc_ScriptContext* ctx = bc_GetCurrentScriptContext();
        if (ctx == NULL) {
                return NULL;
        }
        return ctx->Heap;
}

void bc_AddHeap(bc_Heap* self, bc_Object* obj) {
        if (self == NULL) {
                obj->Paint = PAINT_ONEXIT_T;
                return;
        }
        if (self->AcceptBlocking > 0) {
                obj->Paint = PAINT_ONEXIT_T;
                return;
        }
        bc_PushVector(self->Objects, obj);
}

void bc_CollectHeap(bc_Heap* self) {
        if (self->CollectBlocking > 0) {
                return;
        }
        gc_clear(self);
        gc_mark(self);
        gc_sweep(self);
}

void bc_IgnoreHeap(bc_Heap* self, bc_Object* o) {
        int i = bc_FindVector(self->Objects, o);
        if (i >= 0) {
                bc_RemoveVector(self->Objects, i);
        }
}

void bc_DeleteHeap(bc_Heap* self) {
        bc_DeleteVector(self->Objects, delete_object);
        MEM_FREE(self);
}

void bc_DumpHeap(bc_Heap* self) {
        printf("heap dump:\n");
        for (int i = 0; i < self->Objects->Length; i++) {
                bc_Object* a = bc_AtVector(self->Objects, i);
                printf("    ");
                bc_PrintGenericType(a->GType);
                printf("\n");
        }
}

// private
static void delete_object(bc_VectorItem item) {
        bc_Object* e = (bc_Object*)item;
        bc_DeleteObject(e);
}

static void gc_clear(bc_Heap* self) {
        for (int i = 0; i < self->Objects->Length; i++) {
                bc_Object* e = (bc_Object*)bc_AtVector(self->Objects, i);
                if (e->Paint == PAINT_MARKED_T) {
                        e->Paint = PAINT_UNMARKED_T;
                }
        }
}

static void gc_mark(bc_Heap* self) {
        //今はまだマルチスレッドに対応していないので、
        //とりあえず実行中のスレッドのみを対象とする
        bc_ScriptThread* th = bc_GetCurrentScriptThread();
        bc_Frame* top = bc_GetScriptThreadFrameRef(th);
        assert(top != NULL);
        bc_MarkAllFrame(top);

        // true/false/nullは常にマーク
        bc_GetTrueObject()->Paint = PAINT_MARKED_T;
        bc_GetFalseObject()->Paint = PAINT_MARKED_T;
        bc_GetNullObject()->Paint = PAINT_MARKED_T;
}

static void gc_sweep(bc_Heap* self) {
        int sweep = 0;
        bc_Vector* recycle = bc_NewVector();
        bc_Vector* garabage = bc_NewVector();
        for (int i = 0; i < self->Objects->Length; i++) {
                bc_Object* e = (bc_Object*)bc_AtVector(self->Objects, i);
                if (e->Paint == PAINT_UNMARKED_T) {
                        bc_PushVector(garabage, e);
                        sweep++;
                } else {
                        bc_PushVector(recycle, e);
                }
        }
        bc_DeleteVector(self->Objects, bc_VectorDeleterOfNull);
        bc_DeleteVector(garabage, gc_delete);
        self->Objects = recycle;
}

static void gc_delete(bc_VectorItem item) {
        bc_Object* e = (bc_Object*)item;
        bc_DeleteObject(e);
}
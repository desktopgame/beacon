#include "heap.h"
#include <assert.h>
#include <glib.h>
#include <stdlib.h>
#include "../env/generic_type.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../vm/script_thread.h"
#include "../vm/vm.h"
#include "script_context.h"

// proto
static bc_Heap* bc_new_heap();
static void delete_object(bc_VectorItem item);
// mutex
static void sem_v_signal(GAsyncQueue* q);
static void sem_p_wait(GAsyncQueue* q);
static void bc_request_stw();
static void bc_resume_stw();
// gc
static gpointer gc_run(gpointer data);
static void gc_promotion(bc_Heap* self);
static void gc_collect_all_root(bc_Heap* self);
static void gc_clear(bc_Heap* self);
static void gc_mark(bc_Heap* self);
static void gc_mark_wait(bc_Heap* self);
static void gc_mark_barrier(bc_Heap* self);
static void gc_sweep(bc_Heap* self);
static void gc_delete(bc_VectorItem item);

static bc_Heap* gHeap = NULL;
// STWwait
static GAsyncQueue* gReqQ;
static GAsyncQueue* gResQ;
static GRWLock gQSLock;
static volatile bool gRRR = false;

static GThread* gGCThread = NULL;
static bool gGCContinue = true;

void bc_InitHeap() {
        assert(gHeap == NULL);
        gReqQ = g_async_queue_new();
        gResQ = g_async_queue_new();
        gHeap = bc_new_heap();
        gGCThread = g_thread_new("gc", gc_run, NULL);
}

void bc_DestroyHeap() {
        bc_CheckSTWRequest();
        gGCContinue = false;
        g_thread_join(gGCThread);
        bc_DeleteCache(gHeap->Objects, delete_object);
        g_async_queue_unref(gReqQ);
        g_async_queue_unref(gResQ);
        MEM_FREE(gHeap);
        gGCThread = NULL;
        gHeap = NULL;
        gReqQ = NULL;
        gResQ = NULL;
}

bc_Heap* bc_GetHeap() {
        assert(gHeap != NULL);
        return gHeap;
}

void bc_AddHeap(bc_Object* obj) {
        bc_Heap* self = bc_GetHeap();
        if (self == NULL) {
                obj->Paint = PAINT_ONEXIT_T;
                return;
        }
        if (self->AcceptBlocking > 0) {
                obj->Paint = PAINT_ONEXIT_T;
                return;
        }
        bc_StoreCache(self->Objects, obj);
}

void bc_IgnoreHeap(bc_Object* o) {
        bc_CheckSTWRequest();
        bc_EraseCache(bc_GetHeap()->Objects, o);
}

void bc_DumpHeap() {
        printf("heap dump:\n");
        bc_Cache* iter = bc_GetHeap()->Objects;
        while (iter != NULL) {
                if (iter->Data == NULL) {
                        iter = iter->Next;
                        continue;
                }
                bc_Object* a = iter->Data;
                printf("    ");
                bc_PrintGenericType(a->GType);
                printf("\n");
                iter = iter->Next;
        }
}

void bc_CheckSTWRequest() {
        if (g_thread_self() == gGCThread) {
                fprintf(stderr,
                        "this function must be not called from gc thread\n");
                abort();
        }
        if (bc_GetHeap()->CollectBlocking > 0) {
                return;
        }
        g_rw_lock_reader_lock(&gQSLock);
        if (!gRRR) {
                g_rw_lock_reader_unlock(&gQSLock);
                return;
        }
        g_rw_lock_reader_unlock(&gQSLock);
        sem_v_signal(gResQ);
        sem_p_wait(gReqQ);
}

// private
static bc_Heap* bc_new_heap() {
        bc_Heap* ret = (bc_Heap*)MEM_MALLOC(sizeof(bc_Heap));
        ret->Objects = bc_NewCache(100);
        ret->Roots = bc_NewCache(100);
        ret->AcceptBlocking = 0;
        ret->CollectBlocking = 0;
        return ret;
}

static void delete_object(bc_VectorItem item) {
        bc_Object* e = (bc_Object*)item;
        bc_DeleteObject(e);
}

// mutex
static void sem_v_signal(GAsyncQueue* q) {
        g_async_queue_push(q, GINT_TO_POINTER(1));
}

static void sem_p_wait(GAsyncQueue* q) { g_async_queue_pop(q); }

static void bc_request_stw() {
        g_rw_lock_writer_lock(&gQSLock);
        gRRR = true;
        g_rw_lock_writer_unlock(&gQSLock);
        sem_p_wait(gResQ);
}

static void bc_resume_stw() {
        g_rw_lock_writer_lock(&gQSLock);
        gRRR = false;
        g_rw_lock_writer_unlock(&gQSLock);
        sem_v_signal(gReqQ);
}

// gc

static gpointer gc_run(gpointer data) {
        bc_Heap* self = bc_GetHeap();
        while (gGCContinue) {
                //ヒープを保護してルートを取得
                bc_request_stw();
                gc_promotion(self);
                gc_collect_all_root(self);
                bc_resume_stw();
                //ルートを全てマーク
                gc_mark(self);
                //ライトバリアーを確認
                bc_request_stw();
                gc_mark_wait(self);
                gc_mark_barrier(self);
                bc_resume_stw();
                //ライトバリアーを確認
                gc_sweep(self);
        }
        return NULL;
}

static void gc_promotion(bc_Heap* self) {
        bc_Cache* iter = self->Roots;
        while (iter != NULL) {
                if (iter->Data == NULL) {
                        iter = iter->Next;
                        continue;
                }
                bc_Object* e = iter->Data;
                if (e->Paint == PAINT_DIFF_T) {
                        e->Paint = PAINT_UNMARKED_T;
                }
                iter = iter->Next;
        }
}

static void gc_collect_all_root(bc_Heap* self) {
        for (int i = 0; i < bc_GetScriptThreadCount(); i++) {
                bc_ScriptThread* th = bc_GetScriptThreadAt(i);
                //全ての静的フィールドをマーク
                bc_ScriptContext* sctx = bc_SelectedScriptContext(th);
                bc_CollectStaticFields(sctx, self->Roots);
                //全てのスタック変数をマーク
                // GC直後にフレームを解放した場合はNULLになる
                bc_Frame* top = bc_GetScriptThreadFrameRef(th);
                if (top != NULL) {
                        bc_CollectAllFrame(top, self->Roots);
                }
                // true, false, null
                bc_StoreCache(self->Roots, bc_GetUniqueTrueObject(sctx));
                bc_StoreCache(self->Roots, bc_GetUniqueFalseObject(sctx));
                bc_StoreCache(self->Roots, bc_GetUniqueNullObject(sctx));
        }
}

static void gc_mark(bc_Heap* self) {
        bc_Cache* iter = self->Roots;
        while (iter != NULL) {
                if (iter->Data == NULL) {
                        iter = iter->Next;
                        continue;
                }
                bc_Object* e = iter->Data;
                bc_MarkAllObject(e);
                iter = iter->Next;
        }
}

static void gc_mark_wait(bc_Heap* self) {
        bc_Cache* iter = self->Objects;
        while (iter != NULL) {
                if (iter->Data == NULL) {
                        iter = iter->Next;
                        continue;
                }
                bc_Object* e = iter->Data;
                if (e->Paint == PAINT_DIFF_T) {
                        e->Paint = PAINT_UNMARKED_T;
                        bc_MarkAllObject(e);
                }
                iter = iter->Next;
        }
}

static void gc_mark_barrier(bc_Heap* self) {
        bc_Cache* iter = self->Objects;
        while (iter != NULL) {
                bc_Object* e = iter->Data;
                if (iter->Data == NULL) {
                        iter = iter->Next;
                        continue;
                }
                if (!e->Update) {
                        iter = iter->Next;
                        continue;
                }
                bc_MarkAllObject(e);
                e->Update = false;
                iter = iter->Next;
        }
}

static void gc_sweep(bc_Heap* self) {
        int sweep = 0;
        bc_Cache* iter = self->Objects;
        while (iter != NULL) {
                bc_Object* e = iter->Data;
                if (iter->Data == NULL) {
                        iter = iter->Next;
                        continue;
                }
                if (e->Paint == PAINT_UNMARKED_T) {
                        bc_DeleteObject(e);
                        iter->Data = NULL;
                } else if (e->Paint == PAINT_MARKED_T) {
                        e->Paint = PAINT_UNMARKED_T;
                }
                iter = iter->Next;
        }
        bc_EraseCacheAll(self->Roots);
}

static void gc_delete(bc_VectorItem item) {
        bc_Object* e = (bc_Object*)item;
        bc_DeleteObject(e);
}

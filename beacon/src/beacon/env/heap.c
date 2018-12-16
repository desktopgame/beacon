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
static void delete_object(bc_VectorItem item);
static void gc_collect_all_root(bc_Heap* self);
static void gc_clear(bc_Heap* self);
static void gc_mark(bc_Heap* self);
static void gc_mark_barrier(bc_Heap* self);
static void gc_sweep(bc_Heap* self);
static void gc_delete(bc_VectorItem item);
static bc_Heap* bc_new_heap();
static gpointer gc_run(gpointer data);
static void sem_v_signal(GAsyncQueue* q);
static void sem_p_wait(GAsyncQueue* q);

static bc_Heap* gHeap = NULL;
// GCwait
static GCond gGCCond;
static GRecMutex gGCMtx;
static volatile bool gGCTrigger = false;
// STWwait
static GAsyncQueue* gReqQ;
static GAsyncQueue* gResQ;
static GRWLock gQSLock;
static volatile bool gRRR = false;
static GCond gSTWReqCond;
static GRecMutex gSTWReqMtx;
static GCond gSTWResCond;
static GRecMutex gSTWResMtx;
static volatile bool gSTWAccept = false;
static volatile bool gSTWRequest = false;

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
        bc_CollectHeap(gHeap);
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

void bc_AddHeap(bc_Heap* self, bc_Object* obj) {
        if (self == NULL) {
                obj->Paint = PAINT_ONEXIT_T;
                return;
        }
        if (self->AcceptBlocking > 0) {
                obj->Paint = PAINT_ONEXIT_T;
                return;
        }
        bc_CheckSTWRequest();
        bc_StoreCache(self->Objects, obj);
}

void bc_CollectHeap(bc_Heap* self) {
        if (self->CollectBlocking > 0) {
                return;
        }
        bc_CheckSTWRequest();
        g_rec_mutex_lock(&gGCMtx);
        gGCTrigger = true;
        g_cond_signal(&gGCCond);
        g_rec_mutex_unlock(&gGCMtx);
}

void bc_IgnoreHeap(bc_Heap* self, bc_Object* o) {
        bc_CheckSTWRequest();
        bc_EraseCache(self->Objects, o);
}

void bc_DumpHeap(bc_Heap* self) {
        printf("heap dump:\n");
        bc_Cache* iter = self->Objects;
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

void bc_RequestSTW() {
        /*
        //フラグをオンにして、
        // VMがこのフラグを見るまで待機します.
        g_rec_mutex_lock(&gSTWReqMtx);
        gSTWRequest = true;
        gSTWAccept = false;
        g_rec_mutex_unlock(&gSTWReqMtx);
        g_rec_mutex_lock(&gSTWResMtx);
        //フラグが確認されたらここを抜ける
        assert(!gSTWAccept);
        assert(gSTWRequest);
        while (!gSTWAccept) {
                g_cond_wait(&gSTWResCond, &gSTWResMtx);
        }
        g_rec_mutex_unlock(&gSTWResMtx);
        */
        g_rw_lock_writer_lock(&gQSLock);
        gRRR = true;
        g_rw_lock_writer_unlock(&gQSLock);
        sem_p_wait(gResQ);
}

void bc_ResumeSTW() {
        g_rw_lock_writer_lock(&gQSLock);
        gRRR = false;
        g_rw_lock_writer_unlock(&gQSLock);
        sem_v_signal(gReqQ);
        /*
        g_rec_mutex_lock(&gSTWReqMtx);
        gSTWAccept = false;
        gSTWRequest = false;
        g_cond_signal(&gSTWReqCond);
        g_rec_mutex_unlock(&gSTWReqMtx);
        */
}

void bc_CheckSTWRequest() {
        if (g_thread_self() == gGCThread) {
                fprintf(stderr,
                        "this function must be not called from gc thread\n");
                abort();
        }
        g_rw_lock_reader_lock(&gQSLock);
        if (!gRRR) {
                g_rw_lock_reader_unlock(&gQSLock);
                return;
        }
        g_rw_lock_reader_unlock(&gQSLock);
        sem_v_signal(gResQ);
        sem_p_wait(gReqQ);
        /*
        //フラグが有効ならウェイトする
        g_rec_mutex_lock(&gSTWReqMtx);
        if (gSTWRequest) {
                g_rec_mutex_lock(&gSTWResMtx);
                gSTWAccept = true;
                g_cond_signal(&gSTWResCond);
                g_rec_mutex_unlock(&gSTWResMtx);
                assert(gSTWRequest);
                assert(gSTWAccept);
                while (gSTWRequest) {
                        g_cond_wait(&gSTWReqCond, &gSTWReqMtx);
                }
        }
        g_rec_mutex_unlock(&gSTWReqMtx);
        */
}

// private
static void delete_object(bc_VectorItem item) {
        bc_Object* e = (bc_Object*)item;
        bc_DeleteObject(e);
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

static void gc_clear(bc_Heap* self) {
        bc_Cache* iter = self->Objects;
        while (iter != NULL) {
                bc_Object* e = iter->Data;
                if (iter->Data == NULL) {
                        iter = iter->Next;
                        continue;
                }
                if (e->Paint == PAINT_MARKED_T) {
                        e->Paint = PAINT_UNMARKED_T;
                }
                iter = iter->Next;
        }
}

static void gc_mark(bc_Heap* self) {
        bc_Cache* iter = self->Roots;
        while (iter != NULL) {
                bc_Object* e = iter->Data;
                bc_MarkAllObject(e);
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
                }
                iter = iter->Next;
        }
        bc_EraseCacheAll(self->Roots);
}

static void gc_delete(bc_VectorItem item) {
        bc_Object* e = (bc_Object*)item;
        bc_DeleteObject(e);
}

static bc_Heap* bc_new_heap() {
        bc_Heap* ret = (bc_Heap*)MEM_MALLOC(sizeof(bc_Heap));
        ret->Objects = bc_NewCache(100);
        ret->Roots = bc_NewCache(100);
        ret->AcceptBlocking = 0;
        ret->CollectBlocking = 0;
        return ret;
}

static gpointer gc_run(gpointer data) {
        bc_Heap* self = bc_GetHeap();
        while (gGCContinue) {
                // 待機
                g_rec_mutex_lock(&gGCMtx);
                while (!gGCTrigger) {
                        g_cond_wait(&gGCCond, &gGCMtx);
                }
                g_rec_mutex_unlock(&gGCMtx);
                //ヒープを保護してルートを取得
                bc_RequestSTW();
                gc_collect_all_root(self);
                bc_ResumeSTW();
                //ルートを全てマーク
                gc_mark(self);
                //ライトバリアーを確認
                bc_RequestSTW();
                gc_mark_barrier(self);
                bc_ResumeSTW();
                //ライトバリアーを確認
                gc_sweep(self);
        }
        return NULL;
}

static void sem_v_signal(GAsyncQueue* q) {
        g_async_queue_push(q, GINT_TO_POINTER(1));
}

static void sem_p_wait(GAsyncQueue* q) { g_async_queue_pop(q); }
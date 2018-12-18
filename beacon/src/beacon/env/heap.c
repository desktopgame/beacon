#include "heap.h"
#include <assert.h>
#include <glib.h>
#include <stdio.h>
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
static bool is_contains_diff_on_roots();
static bool is_force_quit_now();
static void gc_roots_lock();
static void gc_roots_unlock();

static bc_Heap* gHeap = NULL;
static int gGCRuns = 0;
// STWwait
static GAsyncQueue* gReqQ;
static GAsyncQueue* gResQ;
static GRWLock gQSLock;
static volatile bool gSTWRequested = false;

// Roots
static GRecMutex gRootsMtx;

static GThread* gGCThread = NULL;
static bool gGCContinue = true;

// force quit
static GRWLock gForceQuitLock;
static volatile bool gForceQuit = false;

#define REPORT_GC

#ifdef REPORT_GC
#define gcReportPath ("./report/gc.txt")
static FILE* gReportFP;
#endif

void bc_InitHeap() {
        assert(gHeap == NULL);
        gReqQ = g_async_queue_new();
        gResQ = g_async_queue_new();
        gHeap = bc_new_heap();
        gGCThread = g_thread_new("gc", gc_run, NULL);
#ifdef REPORT_GC
        //リポートファイルをクリアして作成
        if (bc_ExistsFile(gcReportPath)) {
                bc_DeleteFile(gcReportPath);
        }
        gReportFP = fopen(gcReportPath, "w");
#endif
}

void bc_DestroyHeap() {
        bc_WaitFullGC();
#ifdef REPORT_GC
        //リポートファイルを閉じる
        fclose(gReportFP);
        gReportFP = NULL;
#endif
        // ロック中なら強制的に再開
        // resume_stwの後に毎回確認される
        g_rw_lock_reader_lock(&gQSLock);
        if (gSTWRequested) {
                g_rw_lock_writer_lock(&gForceQuitLock);
                gForceQuit = true;
                sem_v_signal(gResQ);
                g_rw_lock_writer_unlock(&gForceQuitLock);
        }
        g_rw_lock_reader_unlock(&gQSLock);
        gGCContinue = false;
        g_thread_join(gGCThread);
        bc_DeleteCache(gHeap->Objects, delete_object);
        int idc = bc_CountActiveObject();
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
        //定数は入れてはいけない
        if (self == NULL || self->AcceptBlocking > 0) {
                obj->Paint = PAINT_ONEXIT_T;
                return;
        }
        bc_StoreCache(self->Objects, obj);
}

void bc_AddRoot(bc_Object* obj) {
        if (obj == NULL) {
                return;
        }
        if (obj->Paint != PAINT_ONEXIT_T) {
                bc_StoreCache(bc_GetHeap()->Roots, obj);
        }
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

void bc_WaitFullGC() {
        if (gHeap == NULL) {
                return;
        }
        while (is_contains_diff_on_roots()) {
                bc_CheckSTWRequest();
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
        if (!gSTWRequested) {
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
        gSTWRequested = true;
        g_rw_lock_writer_unlock(&gQSLock);
        sem_p_wait(gResQ);
}

static void bc_resume_stw() {
        g_rw_lock_writer_lock(&gQSLock);
        gSTWRequested = false;
        g_rw_lock_writer_unlock(&gQSLock);
        sem_v_signal(gReqQ);
}

// gc

static gpointer gc_run(gpointer data) {
        bc_Heap* self = bc_GetHeap();
        while (gGCContinue) {
                if (is_force_quit_now()) {
                        break;
                }
                //ヒープを保護してルートを取得
                bc_request_stw();
                if (is_force_quit_now()) {
                        break;
                }
                gc_promotion(self);
                gc_collect_all_root(self);
                bc_resume_stw();

                //ルートを全てマーク
                gc_mark(self);
                //ライトバリアーを確認
                bc_request_stw();
                if (is_force_quit_now()) {
                        break;
                }
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
        //全ての静的フィールドをマーク
        bc_ScriptContext* sctx = bc_GetScriptContext();
        if (bc_GetScriptContextState() != SCTX_STATE_DESTROYED) {
                bc_CollectStaticFields(sctx, self->Roots);
        }
        // true, false, null
        bc_AddRoot(bc_GetUniqueTrueObject(sctx));
        bc_AddRoot(bc_GetUniqueFalseObject(sctx));
        bc_AddRoot(bc_GetUniqueNullObject(sctx));
        for (int i = 0; i < bc_GetScriptThreadCount(); i++) {
                bc_ScriptThread* th = bc_GetScriptThreadAt(i);
                //全てのスタック変数をマーク
                // GC直後にフレームを解放した場合はNULLになる
                bc_Frame* top = bc_GetScriptThreadFrameRef(th);
                if (top != NULL) {
                        bc_CollectAllFrame(top, self->Roots);
                }
        }
}

static void gc_mark(bc_Heap* self) {
        gc_roots_lock();
        bc_Cache* iter = self->Roots;
        while (iter != NULL) {
                if (iter->Data == NULL) {
                        iter = iter->Next;
                        continue;
                }
                bc_Object* e = iter->Data;
                if (e->Paint != PAINT_ONEXIT_T) {
                        bc_MarkAllObject(e);
                }
                iter = iter->Next;
        }
        gc_roots_unlock();
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
                if (e->Paint != PAINT_ONEXIT_T) {
                        bc_MarkAllObject(e);
                }
                e->Update = false;
                iter = iter->Next;
        }
}

static void gc_sweep(bc_Heap* self) {
        gGCRuns++;
#ifdef REPORT_GC
        GTimeVal before, after;
        g_get_current_time(&before);
#endif
        int all = 0;
        int sweep = 0;
        bc_Cache* iter = self->Objects;
        while (iter != NULL) {
                bc_Object* e = iter->Data;
                if (iter->Data == NULL) {
                        iter = iter->Next;
                        continue;
                }
                all++;
                if (e->Paint == PAINT_UNMARKED_T) {
                        bc_DeleteObject(e);
                        iter->Data = NULL;
                        sweep++;
                } else if (e->Paint == PAINT_MARKED_T) {
                        e->Paint = PAINT_UNMARKED_T;
                }
                iter = iter->Next;
        }
        gc_roots_lock();
        bc_EraseCacheAll(self->Roots);
        gc_roots_unlock();
#ifdef REPORT_GC
        g_get_current_time(&after);
        glong diff = after.tv_usec - before.tv_usec;
        if (sweep == 0) {
                fprintf(gReportFP, "sweep(%d)\n", gGCRuns);
        } else {
                fprintf(gReportFP, "!sweep(%d)\n", gGCRuns);
        }
        fprintf(gReportFP, "    %d - %d = %d\n", all, sweep, (all - sweep));
        fprintf(gReportFP, "    delete  : %d\n", sweep);
        fprintf(gReportFP, "    time    : %ld\n", diff);
#endif
}

static void gc_delete(bc_VectorItem item) {
        bc_Object* e = (bc_Object*)item;
        bc_DeleteObject(e);
}

static bool is_contains_diff_on_roots() {
        gc_roots_lock();
        bc_Heap* self = bc_GetHeap();
        bc_Cache* iter = self->Roots;
        while (iter != NULL) {
                if (iter->Data == NULL) {
                        iter = iter->Next;
                        continue;
                }
                bc_Object* o = iter->Data;
                if (o->Paint == PAINT_DIFF_T) {
                        gc_roots_unlock();
                        return true;
                }
                iter = iter->Next;
        }
        gc_roots_unlock();
        return false;
}

static bool is_force_quit_now() {
        bool ret = false;
        g_rw_lock_reader_lock(&gForceQuitLock);
        ret = gForceQuit;
        g_rw_lock_reader_unlock(&gForceQuitLock);
        return ret;
}

static void gc_roots_lock() { g_rec_mutex_lock(&gRootsMtx); }

static void gc_roots_unlock() { g_rec_mutex_unlock(&gRootsMtx); }
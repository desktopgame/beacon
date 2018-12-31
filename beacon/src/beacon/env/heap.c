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

typedef enum stw_result {
        stw_none,
        stw_success,
        stw_fail_by_safe_invoke,
        stw_fail_by_force_quit,
        stw_fail_by_fgc,
} stw_result;
// proto
static bc_Heap* bc_new_heap();
static void delete_object(bc_VectorItem item);
// mutex
static void sem_v_signal(GAsyncQueue* q);
static void sem_p_wait(GAsyncQueue* q);
static stw_result bc_request_stw();
static void bc_resume_stw();
// gc
static gpointer gc_run(gpointer data);
static void gc_promotion(bc_Heap* self);
static void gc_collect_all_root(bc_Heap* self);
static void gc_clear(bc_Heap* self);
static void gc_mark(bc_Heap* self);
static void gc_mark_wait(bc_Heap* self);
static void gc_mark_barrier(bc_Heap* self);
static void gc_reset_roots();
static void gc_reset_mark();
static void gc_overwrite_mark(bc_ObjectPaint paint);
static void gc_sweep(bc_Heap* self);
static void gc_delete(bc_VectorItem item);
static bool is_contains_diff_on_roots();
static void gc_roots_lock();
static void gc_roots_unlock();
static void safe_invoke();
static bool gc_full();

static bc_Heap* gHeap = NULL;
static int gGCRuns = 0;
// STWwait
static GAsyncQueue* gReqQ;
static GAsyncQueue* gResQ;
#define gSTWRequest_V (1)
#define gSTWNotRequest_V (0)
static volatile gint gSTWRequestedAtm = gSTWNotRequest_V;

static GRWLock gSTWResultLock;
static volatile stw_result gSTWResult = stw_none;
static stw_result read_stw_result() {
        g_rw_lock_reader_lock(&gSTWResultLock);
        stw_result ret = gSTWResult;
        g_rw_lock_reader_unlock(&gSTWResultLock);
        return ret;
}
static void write_stw_result(stw_result write) {
        g_rw_lock_writer_lock(&gSTWResultLock);
        gSTWResult = write;
        g_rw_lock_writer_unlock(&gSTWResultLock);
}

static GAsyncQueue* gInvokeReqQ;
static GAsyncQueue* gInvokeResQ;
#define gInvokeYes_V (1)
#define gInvokeNo_V (0)
static volatile gint gInvokeAtm = gInvokeNo_V;

#define gInvokeStopForInvokeYes_V (1)
#define gInvokeStopForInvokeNo_V (0)
static volatile gint gStopForInvokeAtm = gInvokeStopForInvokeNo_V;

#define gFGCYes_V (1)
#define gFGCNo_V (0)
static volatile gint gFGCAtm = gFGCNo_V;
static GAsyncQueue* gFGCQ;

// Roots
static GRecMutex gRootsMtx;

static GThread* gGCThread = NULL;

// force quit
#define gForceQuitYes_V (1)
#define gForceQuitNo_V (0)
static volatile gint gForceQuitAtm = gForceQuitNo_V;

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
        gInvokeReqQ = g_async_queue_new();
        gInvokeResQ = g_async_queue_new();
        gFGCQ = g_async_queue_new();
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
        // ロック中なら強制的に再開
        // resume_stwの後に毎回確認される
        // bc_BeginHeapSafeInvoke();
        g_atomic_int_set(&gForceQuitAtm, gForceQuitYes_V);
        if (g_atomic_int_get(&gSTWRequestedAtm) == gSTWRequest_V) {
                sem_v_signal(gResQ);
        }
        // bc_EndHeapSafeInvoke();
        g_thread_join(gGCThread);
        bc_DeleteCache(gHeap->Objects, delete_object);
        int idc = bc_CountActiveObject();
        g_async_queue_unref(gReqQ);
        g_async_queue_unref(gResQ);
        g_async_queue_unref(gFGCQ);
        MEM_FREE(gHeap);
        gGCThread = NULL;
        gHeap = NULL;
        gReqQ = NULL;
        gResQ = NULL;
#ifdef REPORT_GC
        //リポートファイルを閉じる
        fclose(gReportFP);
        gReportFP = NULL;
#endif
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
        g_atomic_int_set(&gFGCAtm, gFGCYes_V);
        //現在STWを待機しているか
        if (g_atomic_int_get(&gSTWRequestedAtm) == gSTWRequest_V) {
                write_stw_result(stw_fail_by_fgc);
                sem_v_signal(gResQ);
        }
        g_async_queue_pop(gFGCQ);
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
        if (g_atomic_int_get(&gSTWRequestedAtm) == gSTWNotRequest_V) {
                return;
        }
        write_stw_result(stw_success);
        sem_v_signal(gResQ);
        sem_p_wait(gReqQ);
}

void bc_BeginHeapSafeInvoke() {
#if BC_DEBUG
        assert(g_thread_self() != gGCThread);
#endif
        //セーフインボーク中としてマーク
        g_atomic_int_set(&gInvokeAtm, gInvokeYes_V);
        //現在STWを待機しているか
        if (g_atomic_int_get(&gSTWRequestedAtm) == gSTWRequest_V) {
                write_stw_result(stw_fail_by_safe_invoke);
                sem_v_signal(gResQ);
        }
        //スレッドが止まるまで待つ
        sem_p_wait(gInvokeResQ);
}

void bc_EndHeapSafeInvoke() {
#if BC_DEBUG
        assert(g_thread_self() != gGCThread);
#endif
        //セーフインボークを解除
        g_atomic_int_set(&gInvokeAtm, gInvokeNo_V);
        //スレッドを再開
        sem_v_signal(gInvokeReqQ);
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

static stw_result bc_request_stw() {
        g_atomic_int_set(&gSTWRequestedAtm, gSTWRequest_V);
        if (g_atomic_int_get(&gInvokeAtm) == gInvokeYes_V) {
                g_atomic_int_set(&gSTWRequestedAtm, gSTWNotRequest_V);
                return stw_fail_by_safe_invoke;
        }
        if (g_atomic_int_get(&gForceQuitAtm) == gForceQuitYes_V) {
                g_atomic_int_set(&gSTWRequestedAtm, gSTWNotRequest_V);
                return stw_fail_by_force_quit;
        }
        if (g_atomic_int_get(&gFGCAtm) == gFGCYes_V) {
                g_atomic_int_set(&gSTWRequestedAtm, gSTWNotRequest_V);
                return stw_fail_by_fgc;
        }
        sem_p_wait(gResQ);
        return read_stw_result();
}

static void bc_resume_stw() {
        g_atomic_int_set(&gSTWRequestedAtm, gSTWNotRequest_V);
        sem_v_signal(gReqQ);
}

// gc

static gpointer gc_run(gpointer data) {
        bc_Heap* self = bc_GetHeap();
        while (true) {
                if (g_atomic_int_get(&gForceQuitAtm) == gForceQuitYes_V) {
                        break;
                }
                gc_full();
                safe_invoke();
                //ヒープを保護してルートを取得
                if (bc_request_stw() == stw_success) {
                        if (g_atomic_int_get(&gForceQuitAtm) ==
                            gForceQuitYes_V) {
                                break;
                        }
                        gc_promotion(self);
                        gc_collect_all_root(self);
                        bc_resume_stw();
                        //ルートを全てマーク
                        gc_mark(self);
                        //ライトバリアーを確認
                        if (bc_request_stw() == stw_success) {
                                if (g_atomic_int_get(&gForceQuitAtm) ==
                                    gForceQuitYes_V) {
                                        break;
                                }
                                gc_mark_wait(self);
                                gc_mark_barrier(self);
                                bc_resume_stw();
                                //ライトバリアーを確認
                                gc_sweep(self);
                        } else {
                                gc_reset_roots();
                                gc_reset_mark();
                        }
                } else {
                        gc_reset_roots();
                        gc_reset_mark();
                }
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

static void gc_reset_roots() {
        gc_roots_lock();
        bc_EraseCacheAll(gHeap->Roots);
        gc_roots_unlock();
}

static void gc_reset_mark() {
        bc_Cache* iter = gHeap->Objects;
        while (iter != NULL) {
                if (iter->Data == NULL) {
                        iter = iter->Next;
                        continue;
                }
                bc_Object* obj = iter->Data;
                if (obj->Paint == PAINT_MARKED_T) {
                        obj->Paint = PAINT_UNMARKED_T;
                }
                iter = iter->Next;
        }
}

static void gc_overwrite_mark(bc_ObjectPaint paint) {
        bc_Cache* iter = gHeap->Objects;
        while (iter != NULL) {
                if (iter->Data == NULL) {
                        iter = iter->Next;
                        continue;
                }
                bc_Object* obj = iter->Data;
                obj->Paint = paint;
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
        gc_reset_roots();
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

static void gc_roots_lock() { g_rec_mutex_lock(&gRootsMtx); }

static void gc_roots_unlock() { g_rec_mutex_unlock(&gRootsMtx); }

static void safe_invoke() {
        if (g_atomic_int_get(&gInvokeAtm) == gInvokeYes_V) {
                g_atomic_int_set(&gStopForInvokeAtm, gInvokeStopForInvokeYes_V);
                sem_v_signal(gInvokeResQ);
                sem_p_wait(gInvokeReqQ);
        }
        g_atomic_int_set(&gStopForInvokeAtm, gInvokeStopForInvokeNo_V);
}

static bool gc_full() {
        if (g_atomic_int_get(&gFGCAtm) != gFGCYes_V) {
                return false;
        }
        gc_overwrite_mark(PAINT_UNMARKED_T);
        gc_reset_roots();
        bc_Heap* he = bc_GetHeap();
        gc_collect_all_root(he);
        gc_mark(he);
        gc_sweep(he);
        g_atomic_int_set(&gFGCAtm, gFGCNo_V);
        g_async_queue_push(gFGCQ, GINT_TO_POINTER(1));
        return true;
}
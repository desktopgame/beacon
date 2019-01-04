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

struct bc_Heap {
        bc_Cache* Objects;
        bc_Cache* Roots;
        bc_Cache* Garabage;
        //この値が 1以上 なら、新しく確保されたオブジェクトは
        //ヒープに関連づけられません。
        //つまり、オブジェクトを自分で解放する必要があります。
        //これはリテラルのための機構です。
        int AcceptBlocking;
        //この値が 1以上 なら、新しくオブジェクトを確保した時に
        //オブジェクトの総数が閾値を上回っていてもGCを施工しません。
        int CollectBlocking;
};

typedef enum insn_code {
        insn_collect = 0,
        insn_mark,
        insn_mark_barrier,
        insn_sweep,
        insn_full_gc,
        insn_safe_invoke,
        insn_quit,
} insn_code;

typedef enum stw_result {
        stw_none,
        stw_success,
        stw_fail_by_safe_invoke,
        stw_fail_by_quit,
        stw_fail_by_fgc,
} stw_result;
// proto
static bc_Heap* bc_new_heap();
static void delete_object(bc_VectorItem item);
// mutex
static void sem_v_signal(GAsyncQueue* q);
static void sem_p_wait(GAsyncQueue* q);

static insn_code insn_pop();
static void insn_push(insn_code code);

static stw_result bc_request_stw();
static void bc_resume_stw();
// gc
static gpointer gc_run(gpointer data);
static void gc_insn_collect();
static void gc_insn_mark();
static void gc_insn_mark_barrier();
static void gc_insn_sweep();
static void gc_insn_full_gc();
static void gc_insn_safe_invoke();

static void gc_promotion();
static void gc_collect_all_root();
static void gc_clear();
static void gc_mark();
static void gc_mark_wait();
static void gc_mark_barrier();
static void gc_reset_roots();
static void gc_reset_mark();
static void gc_overwrite_mark(bc_ObjectPaint paint);
static void gc_sweep_prepare();
static void gc_sweep();
static void gc_delete(bc_VectorItem item);
static void safe_invoke();
static bool gc_full();

static bc_Heap* gHeap = NULL;
static int gGCRuns = 0;
// STWwait
static GAsyncQueue* gReqQ;
static GAsyncQueue* gResQ;
static const gint STW_REQUEST_ON = 1;
static const gint STW_REQUEST_OFF = 0;
static volatile gint gSTWRequestedAtm = STW_REQUEST_OFF;

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
static const gint SAFE_INVOKE_ON = 1;
static const gint SAFE_INVOKE_OFF = 0;
static volatile gint gInvokeAtm = SAFE_INVOKE_OFF;

static const gint STOP_FOR_ON = 1;
static const gint STOP_FOR_OFF = 0;
static volatile gint gStopForInvokeAtm = STOP_FOR_OFF;

static const gint FULL_GC_ON = 1;
static const gint FULL_GC_OFF = 0;
static volatile gint gFGCAtm = FULL_GC_OFF;
static GAsyncQueue* gFGCQ;

static volatile gint gHeapWaitStack = 0;
static volatile gint gHeapSyncStack = 0;
static GRecMutex gSTWStateMtx;
static GAsyncQueue* gRunQueue;

static GThread* gGCThread = NULL;

// quit
static const gint QUIT_ON = 1;
static const gint QUIT_OFF = 0;
static volatile gint gQuitAtm = QUIT_OFF;

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
        gRunQueue = g_async_queue_new();
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
        g_atomic_int_set(&gQuitAtm, QUIT_ON);
        if (g_atomic_int_get(&gSTWRequestedAtm) == STW_REQUEST_ON) {
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

void bc_AddHeap(bc_Object* obj) {
        //定数は入れてはいけない
        if (gHeap == NULL || gHeap->AcceptBlocking > 0) {
                obj->Paint = PAINT_ONEXIT_T;
                return;
        }
        bc_StoreCache(gHeap->Objects, obj);
}

void bc_AddRoot(bc_Object* obj) {
        if (obj == NULL) {
                return;
        }
        if (obj->Paint != PAINT_ONEXIT_T) {
                bc_StoreCache(gHeap->Roots, obj);
        }
}

void bc_IgnoreHeap(bc_Object* o) {
        bc_CheckSTWRequest();
        bc_EraseCache(gHeap->Objects, o);
}

void bc_DumpHeap() {
        printf("heap dump:\n");
        bc_Cache* iter = gHeap->Objects;
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
        int c = bc_GetActiveScriptThreadCount();
        assert(c == 1);
        g_atomic_int_set(&gFGCAtm, FULL_GC_ON);
        //現在STWを待機しているか
        if (g_atomic_int_get(&gSTWRequestedAtm) == STW_REQUEST_ON) {
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
        if (gHeap->CollectBlocking > 0) {
                return;
        }
        g_rec_mutex_lock(&gSTWStateMtx);
        if (g_atomic_int_get(&gSTWRequestedAtm) == STW_REQUEST_OFF) {
                g_rec_mutex_unlock(&gSTWStateMtx);
                return;
        }
        insn_push(insn_full_gc);
        // STW中は全てのスレッドが待機しなければいけない
        //なのでスレッドを生成できないように
        bc_LockScriptThread();
        //スレッドをカウント
        int thread_count = bc_GetActiveScriptThreadCount();
        g_atomic_int_inc(&gHeapWaitStack);
        gint waitStack = g_atomic_int_get(&gHeapWaitStack);
        gint syncStack = g_atomic_int_get(&gHeapSyncStack);
        if ((waitStack + syncStack) == thread_count) {
                write_stw_result(stw_success);
                sem_v_signal(gResQ);
        }
        bc_UnlockScriptThread();
        g_rec_mutex_unlock(&gSTWStateMtx);
        sem_p_wait(gReqQ);
}

bool bc_BeginSyncHeap() {
        g_rec_mutex_lock(&gSTWStateMtx);
        bool ret = false;
        bc_LockScriptThread();
        int thread_count = bc_GetActiveScriptThreadCount();
        g_atomic_int_inc(&gHeapSyncStack);
        gint waitStack = g_atomic_int_get(&gHeapWaitStack);
        gint syncStack = g_atomic_int_get(&gHeapSyncStack);
        if ((waitStack + syncStack) == thread_count) {
                write_stw_result(stw_success);
                sem_v_signal(gResQ);
                ret = true;
        }
        assert((waitStack + syncStack) <= thread_count);
        bc_UnlockScriptThread();
        g_rec_mutex_unlock(&gSTWStateMtx);
        return ret;
}

void bc_EndSyncHeap() {
        g_rec_mutex_lock(&gSTWStateMtx);
        g_atomic_int_dec_and_test(&gHeapSyncStack);
        g_rec_mutex_unlock(&gSTWStateMtx);
}

void bc_BeginHeapSafeInvoke() {
#if BC_DEBUG
        assert(g_thread_self() != gGCThread);
#endif
        insn_push(insn_safe_invoke);
        //セーフインボーク中としてマーク
        g_atomic_int_set(&gInvokeAtm, SAFE_INVOKE_ON);
        //現在STWを待機しているか
        if (g_atomic_int_get(&gSTWRequestedAtm) == STW_REQUEST_ON) {
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
        g_atomic_int_set(&gInvokeAtm, SAFE_INVOKE_OFF);
        //スレッドを再開
        sem_v_signal(gInvokeReqQ);
}

void bc_BeginNewConstant() { gHeap->AcceptBlocking++; }

void bc_EndNewConstant() { gHeap->AcceptBlocking--; }

int bc_BeginNewRuntime() {
        int ret = gHeap->AcceptBlocking;
        gHeap->AcceptBlocking = 0;
}

void bc_EndNewRuntime(int depth) { gHeap->AcceptBlocking = depth; }

void bc_BeginGCPending() { gHeap->CollectBlocking++; }

void bc_EndGCPending() { gHeap->CollectBlocking--; }

void bc_ResetHeapStack() {
        gHeap->AcceptBlocking = 0;
        gHeap->CollectBlocking = 0;
}

// private
static bc_Heap* bc_new_heap() {
        bc_Heap* ret = (bc_Heap*)MEM_MALLOC(sizeof(bc_Heap));
        ret->Objects = bc_NewCache(100);
        ret->Roots = bc_NewCache(100);
        ret->Garabage = bc_NewCache(100);
        ret->AcceptBlocking = 0;
        ret->CollectBlocking = 0;
        return ret;
}

static void delete_object(bc_VectorItem item) {
        bc_Object* e = (bc_Object*)item;
        bc_DeleteObject(e);
}

// utility
static void sem_v_signal(GAsyncQueue* q) {
        g_async_queue_push(q, GINT_TO_POINTER(1));
}

static void sem_p_wait(GAsyncQueue* q) { g_async_queue_pop(q); }

static insn_code insn_pop() { return g_async_queue_pop(gRunQueue); }

static void insn_push(insn_code code) {
        g_async_queue_push(gRunQueue, GINT_TO_POINTER(code));
}

static stw_result bc_request_stw() {
        g_rec_mutex_lock(&gSTWStateMtx);
        g_atomic_int_set(&gSTWRequestedAtm, STW_REQUEST_ON);
        if (g_atomic_int_get(&gInvokeAtm) == SAFE_INVOKE_ON) {
                g_atomic_int_set(&gSTWRequestedAtm, STW_REQUEST_OFF);
                g_rec_mutex_unlock(&gSTWStateMtx);
                return stw_fail_by_safe_invoke;
        }
        if (g_atomic_int_get(&gQuitAtm) == QUIT_ON) {
                g_atomic_int_set(&gSTWRequestedAtm, STW_REQUEST_OFF);
                g_rec_mutex_unlock(&gSTWStateMtx);
                return stw_fail_by_quit;
        }
        if (g_atomic_int_get(&gFGCAtm) == FULL_GC_ON) {
                g_atomic_int_set(&gSTWRequestedAtm, STW_REQUEST_OFF);
                g_rec_mutex_unlock(&gSTWStateMtx);
                return stw_fail_by_fgc;
        }
        g_rec_mutex_unlock(&gSTWStateMtx);
        sem_p_wait(gResQ);
        return read_stw_result();
}

static void bc_interrupt_stw() {
        g_rec_mutex_lock(&gSTWStateMtx);
        if (g_atomic_int_get(&gSTWRequestedAtm) == STW_REQUEST_ON) {
                sem_v_signal(gResQ);
                g_atomic_int_set(&gSTWRequestedAtm, STW_REQUEST_OFF);
        }
        g_rec_mutex_unlock(&gSTWStateMtx);
}

static void bc_resume_stw() {
        g_rec_mutex_lock(&gSTWStateMtx);
        g_atomic_int_set(&gSTWRequestedAtm, STW_REQUEST_OFF);
        //待機中の全てのスレッドを解放する
        while (g_atomic_int_get(&gHeapWaitStack) > 0) {
                g_atomic_int_dec_and_test(&gHeapWaitStack);
                sem_v_signal(gReqQ);
        }
        g_rec_mutex_unlock(&gSTWStateMtx);
        // bc_UnlockScriptThread();
}

// gc

static gpointer gc_run(gpointer data) {
        bool go = true;
        while (go) {
                gint code = insn_pop();
                switch (code) {
                        case insn_collect:
                                gc_insn_collect();
                                break;
                        case insn_mark:
                                gc_insn_mark();
                                break;
                        case insn_mark_barrier:
                                gc_insn_mark_barrier();
                                break;
                        case insn_sweep:
                                gc_insn_sweep();
                                break;
                        case insn_full_gc:
                                gc_insn_full_gc();
                                break;
                        case insn_safe_invoke:
                                gc_insn_safe_invoke();
                                break;
                        case insn_quit:
                                go = false;
                                break;
                }
        }
        return NULL;
}

static void gc_insn_collect() {
        if (bc_request_stw() == stw_success) {
                if (g_atomic_int_get(&gQuitAtm) == QUIT_ON) {
                        insn_push(insn_quit);
                        return;
                }
                gc_promotion();
                gc_collect_all_root();
                bc_resume_stw();
                insn_push(insn_mark);
        } else {
                gc_reset_roots();
                gc_reset_mark();
                insn_push(insn_collect);
        }
}

static void gc_insn_mark() {
        gc_mark();
        insn_push(insn_mark_barrier);
}

static void gc_insn_mark_barrier() {
        //ライトバリアーを確認
        if (bc_request_stw() == stw_success) {
                if (g_atomic_int_get(&gQuitAtm) == QUIT_ON) {
                        insn_push(insn_quit);
                        return;
                }
                gc_mark_wait();
                gc_mark_barrier();
                gc_sweep_prepare();
                bc_resume_stw();
                insn_push(insn_sweep);
        } else {
                gc_reset_roots();
                gc_reset_mark();
                insn_push(insn_collect);
        }
}

static void gc_insn_sweep() {
        gc_sweep();
        insn_push(insn_collect);
}

static void gc_insn_full_gc() {
        gc_full();
        insn_push(insn_collect);
}

static void gc_insn_safe_invoke() {
        safe_invoke();
        insn_push(insn_collect);
}

// gc functions
static void gc_promotion() {
        bc_Cache* iter = gHeap->Objects;
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

static void gc_collect_all_root() {
        //全ての静的フィールドをマーク
        bc_ScriptContext* sctx = bc_GetScriptContext();
        if (bc_GetScriptContextState() != SCTX_STATE_DESTROYED) {
                bc_CollectStaticFields(sctx, gHeap->Roots);
        }
        // true, false, null
        bc_AddRoot(bc_GetUniqueTrueObject(sctx));
        bc_AddRoot(bc_GetUniqueFalseObject(sctx));
        bc_AddRoot(bc_GetUniqueNullObject(sctx));
        bc_LockScriptThread();
        int sthn = bc_GetScriptThreadCount();
        for (int i = 0; i < sthn; i++) {
                bc_ScriptThread* th = bc_GetScriptThreadAt(i);
                //全てのスタック変数をマーク
                // GC直後にフレームを解放した場合はNULLになる
                bc_Frame* top = bc_GetScriptThreadFrameRef(th);
                if (top != NULL) {
                        bc_CollectAllFrame(top, gHeap->Roots);
                }
        }
        bc_UnlockScriptThread();
}

static void gc_mark() {
        bc_Cache* iter = gHeap->Roots;
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
}

static void gc_mark_wait() {
        bc_Cache* iter = gHeap->Objects;
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

static void gc_mark_barrier() {
        bc_Cache* iter = gHeap->Objects;
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

static void gc_reset_roots() { bc_EraseCacheAll(gHeap->Roots); }

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
                if (obj->Paint != PAINT_ONEXIT_T) {
                        obj->Paint = paint;
                }
                iter = iter->Next;
        }
}

static void gc_sweep_prepare() {
        bc_EraseCacheAll(gHeap->Garabage);
        bc_Cache* iter = gHeap->Objects;
        while (iter != NULL) {
                bc_Object* e = iter->Data;
                if (iter->Data == NULL) {
                        iter = iter->Next;
                        continue;
                }
                if (e->Paint == PAINT_UNMARKED_T) {
                        // bc_DeleteObject(e);
                        bc_StoreCache(gHeap->Garabage, iter->Data);
                        iter->Data = NULL;
                } else if (e->Paint == PAINT_MARKED_T) {
                        e->Paint = PAINT_UNMARKED_T;
                }
                iter = iter->Next;
        }
}

static void gc_sweep() {
        gGCRuns++;
#ifdef REPORT_GC
        GTimeVal before, after;
        g_get_current_time(&before);
#endif
        int all = 0;
        int sweep = 0;
        bc_Cache* iter = gHeap->Garabage;
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

static void safe_invoke() {
        if (g_atomic_int_get(&gInvokeAtm) == SAFE_INVOKE_ON) {
                g_atomic_int_set(&gStopForInvokeAtm, STOP_FOR_ON);
                sem_v_signal(gInvokeResQ);
                sem_p_wait(gInvokeReqQ);
        }
        g_atomic_int_set(&gStopForInvokeAtm, STOP_FOR_OFF);
}

static bool gc_full() {
        if (g_atomic_int_get(&gFGCAtm) != FULL_GC_ON) {
                return false;
        }
        gc_overwrite_mark(PAINT_UNMARKED_T);
        gc_reset_roots();
        gc_collect_all_root();
        gc_mark();
        gc_sweep();
        g_atomic_int_set(&gFGCAtm, FULL_GC_OFF);
        g_async_queue_push(gFGCQ, GINT_TO_POINTER(1));
        return true;
}
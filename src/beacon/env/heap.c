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
        insn_collect = 1,
        insn_mark,
        insn_mark_barrier,
        insn_sweep,
        insn_full_gc,
        insn_safe_invoke,
        insn_stw_begin,
        insn_stw_end,
        insn_quit,
        insn_invalid,
} insn_code;

// proto
static bc_Heap* bc_new_heap();
static void delete_object(bc_VectorItem item);
// mutex
static void sem_v_signal(GAsyncQueue* q);
static void sem_p_wait(GAsyncQueue* q);

static insn_code insn_pop();
static void insn_push(insn_code code);
static void insn_push_stw(insn_code code);
static void insn_push_unit(insn_code code);
static void insn_flush();
static const char* insn_string(insn_code code);
static void write_insn_curr_code(insn_code code);
static void write_insn_last_code(insn_code code);
static void assert_last_code(insn_code code);

// gc
static gpointer gc_run(gpointer data);
static bool gc_insn_eval(insn_code code);
static void gc_insn_collect();
static void gc_insn_mark();
static void gc_insn_mark_barrier();
static void gc_insn_sweep();
static void gc_insn_full_gc();
static void gc_insn_safe_invoke();
static void gc_insn_stw_begin();
static void gc_insn_stw_end();

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
static void gc_trigger();
static void safe_invoke();
static bool gc_full();

static bc_Heap* gHeap = NULL;
static int gGCRuns = 0;

static GRecMutex gSTWScheduleMutex;
static GCond gSTWScheduleCond;
static gint gSTWSynqStack = 0;
static gint gSTWPollStack = 0;
static gint gSTWInterrupt = 0;
static gint gCurrInsnCode = 0;
static gint gLastInsnCode = 0;
static GRWLock gCurrInsnCodeRWLock;
static GRWLock gLastInsnCodeRWLock;
static GRecMutex gRQueueMutex;
static GAsyncQueue* gRunQueue;
static GAsyncQueue* gSubQueue;
static GAsyncQueue* gCheckQueue;
static GAsyncQueue* gSIBeginQueue;
static GAsyncQueue* gSIEndQueue;
static GThread* gGCThread = NULL;
static bool ggg = false;

#define REPORT_GC

#ifdef REPORT_GC
#define gcReportPath ("./report/gc.txt")
static FILE* gReportFP;
#endif

void bc_InitHeap() {
        assert(gHeap == NULL);
        gHeap = bc_new_heap();
        gRunQueue = g_async_queue_new();
        gSubQueue = g_async_queue_new();
        gCheckQueue = g_async_queue_new();
        gSIBeginQueue = g_async_queue_new();
        gSIEndQueue = g_async_queue_new();
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
        g_rec_mutex_lock(&gSTWScheduleMutex);
        g_rec_mutex_lock(&gRQueueMutex);
        //既存のタスクを全て終了する
        insn_flush();
        insn_push(insn_quit);
        //もし他のスレッドを待っているなら強制再開
        g_rw_lock_reader_lock(&gCurrInsnCodeRWLock);
        if (gCurrInsnCode == insn_stw_begin) {
                g_atomic_int_set(&gSTWInterrupt, 1);
                g_cond_signal(&gSTWScheduleCond);
        }
        g_rw_lock_reader_unlock(&gCurrInsnCodeRWLock);
        g_rec_mutex_unlock(&gRQueueMutex);
        g_rec_mutex_unlock(&gSTWScheduleMutex);

        g_thread_join(gGCThread);
        bc_DeleteCache(gHeap->Objects, delete_object);
        MEM_FREE(gHeap);
        gGCThread = NULL;
        gHeap = NULL;
        g_async_queue_unref(gRunQueue);
        gRunQueue = NULL;
        g_async_queue_unref(gSubQueue);
        gSubQueue = NULL;
        g_async_queue_unref(gCheckQueue);
        gCheckQueue = NULL;
        g_async_queue_unref(gSIBeginQueue);
        gSIBeginQueue = NULL;
        g_async_queue_unref(gSIEndQueue);
        gSIEndQueue = NULL;
#ifdef REPORT_GC
        //リポートファイルを閉じる
        fclose(gReportFP);
        gReportFP = NULL;
#endif
}

void bc_WakeupGC() {
        if (!ggg) {
                insn_push_stw(insn_collect);
                ggg = true;
        }
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
        insn_push_stw(insn_full_gc);
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
        g_rec_mutex_lock(&gSTWScheduleMutex);
        g_atomic_int_inc(&gSTWPollStack);
        g_rec_mutex_unlock(&gSTWScheduleMutex);
        gc_trigger();
        sem_p_wait(gCheckQueue);
}

bool bc_BeginSyncHeap() {
        g_rec_mutex_lock(&gSTWScheduleMutex);
        g_atomic_int_inc(&gSTWSynqStack);
        g_rec_mutex_unlock(&gSTWScheduleMutex);
        gc_trigger();
        return false;
}

void bc_EndSyncHeap() { g_atomic_int_dec_and_test(&gSTWSynqStack); }

void bc_BeginHeapSafeInvoke() {
#if BC_DEBUG
        assert(g_thread_self() != gGCThread);
#endif
        // insn_stw_beginを実行しているなら強制的に割り込む
        g_rw_lock_reader_lock(&gCurrInsnCodeRWLock);
        g_rec_mutex_lock(&gRQueueMutex);
        g_rec_mutex_lock(&gSTWScheduleMutex);
        insn_code tmp = gCurrInsnCode;
        if (gCurrInsnCode == insn_stw_begin) {
                //予約された全ての命令を破棄
                insn_flush();
                insn_push_unit(insn_safe_invoke);
                //割り込みフラグをtrueに
                g_atomic_int_set(&gSTWInterrupt, 1);
                //再開
                g_cond_signal(&gSTWScheduleCond);
        } else {
                insn_flush();
                insn_push_unit(insn_safe_invoke);
        }
        g_rec_mutex_unlock(&gSTWScheduleMutex);
        g_rec_mutex_unlock(&gRQueueMutex);
        g_rw_lock_reader_unlock(&gCurrInsnCodeRWLock);
        g_async_queue_pop(gSIBeginQueue);
}

void bc_EndHeapSafeInvoke() {
#if BC_DEBUG
        assert(g_thread_self() != gGCThread);
#endif
        g_async_queue_push(gSIEndQueue, GINT_TO_POINTER(1));
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

static void insn_push_stw(insn_code code) {
        g_rec_mutex_lock(&gRQueueMutex);
        insn_push(insn_stw_begin);
        insn_push(code);
        insn_push(insn_stw_end);
        g_rec_mutex_unlock(&gRQueueMutex);
}

static void insn_push_unit(insn_code code) {
        g_rec_mutex_lock(&gRQueueMutex);
        insn_push(code);
        g_rec_mutex_unlock(&gRQueueMutex);
}

static void insn_flush() {
        g_rec_mutex_lock(&gRQueueMutex);
        while (g_async_queue_length(gRunQueue) > 0) {
                g_async_queue_pop(gRunQueue);
        }
        g_rec_mutex_unlock(&gRQueueMutex);
}

static const char* insn_string(insn_code code) {
        switch (code) {
                case insn_collect:
                        return "collect";
                case insn_mark:
                        return "mark";
                case insn_mark_barrier:
                        return "barrier";
                case insn_sweep:
                        return "sweep";
                case insn_full_gc:
                        return "full-gc";
                case insn_safe_invoke:
                        return "safe-invoke";
                case insn_stw_begin:
                        return "stw-begin";
                case insn_stw_end:
                        return "stw-end";
                case insn_quit:
                        return "quit";
        }
        return "undefined";
}

static void write_insn_curr_code(insn_code code) {
        g_rw_lock_writer_lock(&gCurrInsnCodeRWLock);
        gCurrInsnCode = code;
        g_rw_lock_writer_unlock(&gCurrInsnCodeRWLock);
}

static void write_insn_last_code(insn_code code) {
        g_rw_lock_writer_lock(&gLastInsnCodeRWLock);
        gLastInsnCode = code;
        g_rw_lock_writer_unlock(&gLastInsnCodeRWLock);
}

static void assert_last_code(insn_code code) {
        g_rw_lock_reader_lock(&gLastInsnCodeRWLock);
        if (gLastInsnCode != code) {
                fprintf(stderr, "assersion failed. (value)%s != (expect)%s\n",
                        insn_string(gLastInsnCode), insn_string(code));
                abort();
        }
        g_rw_lock_reader_unlock(&gLastInsnCodeRWLock);
}

// gc

static gpointer gc_run(gpointer data) {
        while (gc_insn_eval(insn_pop())) {
                ;
        }
        return NULL;
}

static bool gc_insn_eval(insn_code code) {
        bool go = true;
        //同じ命令を連続して実行しないように
        g_rw_lock_reader_lock(&gLastInsnCodeRWLock);
        if (gLastInsnCode == code) {
                g_rw_lock_reader_unlock(&gLastInsnCodeRWLock);
                write_insn_last_code(insn_invalid);
                return go;
        }
        g_rw_lock_reader_unlock(&gLastInsnCodeRWLock);
        //各命令を実行
        write_insn_curr_code(code);
        // fprintf(stderr, "-    %s\n", insn_string(code));
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
                case insn_stw_begin:
                        gc_insn_stw_begin();
                        break;
                case insn_stw_end:
                        gc_insn_stw_end();
                        break;
                case insn_quit:
                        go = false;
                        break;
        }
        write_insn_last_code(code);
        return go;
}

static void gc_insn_collect() {
        assert_last_code(insn_stw_begin);
        gc_promotion();
        gc_collect_all_root();
        insn_push_unit(insn_mark);
}

static void gc_insn_mark() {
        assert_last_code(insn_stw_end);
        gc_mark();
        insn_push_stw(insn_mark_barrier);
}

static void gc_insn_mark_barrier() {
        assert_last_code(insn_stw_begin);
        gc_mark_wait();
        gc_mark_barrier();
        gc_sweep_prepare();
        insn_push_unit(insn_sweep);
}

static void gc_insn_sweep() {
        assert_last_code(insn_stw_end);
        gc_sweep();
        insn_push_stw(insn_collect);
}

static void gc_insn_full_gc() {
        gc_overwrite_mark(PAINT_UNMARKED_T);
        gc_reset_roots();
        gc_collect_all_root();
        gc_mark();
        gc_sweep();
        g_rec_mutex_lock(&gRunQueue);
        insn_flush();
        insn_push_stw(insn_collect);
        g_rec_mutex_unlock(&gRunQueue);
}

static void gc_insn_safe_invoke() {
        g_async_queue_push(gSIBeginQueue, GINT_TO_POINTER(1));
        g_async_queue_pop(gSIEndQueue);
}

static void gc_insn_stw_begin() {
        g_rec_mutex_lock(&gRQueueMutex);
        bool safeInvoke = false;
        //セーフインボークが予約されているか
        while (g_async_queue_length(gRunQueue) > 0) {
                gint code = g_async_queue_pop(gRunQueue);
                g_async_queue_push(gSubQueue, code);
                if (code == insn_safe_invoke) {
                        safeInvoke = true;
                        break;
                }
        }
        //予約ずみならそちらを優先
        if (safeInvoke) {
                while (g_async_queue_length(gSubQueue) > 0) {
                        g_async_queue_pop(gSubQueue);
                }
                insn_flush();
                insn_push(insn_safe_invoke);
                insn_push_stw(insn_collect);
                g_rec_mutex_unlock(&gRQueueMutex);
                return;
        } else {
                //予約さていないので戻す
                while (g_async_queue_length(gSubQueue) > 0) {
                        gint code = g_async_queue_pop(gSubQueue);
                        g_async_queue_push(gRunQueue, code);
                }
        }
        g_rec_mutex_unlock(&gRQueueMutex);
        g_rec_mutex_lock(&gSTWScheduleMutex);
        int asthn = bc_GetActiveScriptThreadCount();
        //全てのスレッドが揃うまでまつ
        while (((g_atomic_int_get(&gSTWSynqStack) +
                 g_atomic_int_get(&gSTWPollStack)) < asthn) &&
               g_atomic_int_get(&gSTWInterrupt) == 0) {
                g_cond_wait(&gSTWScheduleCond, &gSTWScheduleMutex);
        }
        //割り込みによって中断された
        if (g_atomic_int_get(&gSTWInterrupt) == 1) {
                g_atomic_int_set(&gSTWInterrupt, 0);
                gc_insn_stw_end();
        }
        g_rec_mutex_unlock(&gSTWScheduleMutex);
}

static void gc_insn_stw_end() {
        g_rec_mutex_lock(&gSTWScheduleMutex);
        while (g_atomic_int_get(&gSTWPollStack) > 0) {
                g_atomic_int_dec_and_test(&gSTWPollStack);
                sem_v_signal(gCheckQueue);
        }
        g_rec_mutex_unlock(&gSTWScheduleMutex);
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

static void gc_trigger() {
        gint sync = g_atomic_int_get(&gSTWSynqStack);
        gint poll = g_atomic_int_get(&gSTWPollStack);
        int all = bc_GetActiveScriptThreadCount();
        if ((sync + poll) == all) {
                g_rec_mutex_lock(&gSTWScheduleMutex);
                g_cond_signal(&gSTWScheduleCond);
                g_rec_mutex_unlock(&gSTWScheduleMutex);
        }
}
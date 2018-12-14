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
static void bc_heap_lock();
static void bc_heap_unlock();
static void bc_gc_lock();
static void bc_gc_unlock();

static bc_Heap* gHeap = NULL;
static GCond gGCWait;
static GRecMutex gGCMtx;
static GRecMutex gHeapMtx;
static GThread* gGCThread = NULL;
static bool gGCContinue = true;

void bc_InitHeap() {
        assert(gHeap == NULL);
        gHeap = bc_new_heap();
        gGCThread = g_thread_new("gc", gc_run, NULL);
}

void bc_DestroyHeap() {
        bc_CollectHeap(gHeap);
        gGCContinue = false;
        g_thread_join(gGCThread);
        bc_DeleteCache(gHeap->Objects, delete_object);
        MEM_FREE(gHeap);
        gGCThread = NULL;
        gHeap = NULL;
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
        bc_LockHeap();
        bc_StoreCache(self->Objects, obj);
        bc_UnlockHeap();
}

void bc_CollectHeap(bc_Heap* self) {
        if (self->CollectBlocking > 0) {
                return;
        }
        bc_gc_lock();
        g_cond_signal(&gGCWait);
        bc_gc_unlock();
}

void bc_IgnoreHeap(bc_Heap* self, bc_Object* o) {
        bc_heap_lock();
        bc_EraseCache(self->Objects, o);
        bc_heap_unlock();
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

void bc_LockHeap() { bc_heap_lock(); }

void bc_UnlockHeap() { bc_heap_unlock(); }

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
                g_cond_wait(&gGCWait, &gGCMtx);
                //ヒープを保護してルートを取得
                bc_heap_lock();
                gc_collect_all_root(self);
                bc_heap_unlock();
                //ルートを全てマーク
                gc_mark(self);
                //ライトバリアーを確認
                bc_heap_lock();
                gc_mark_barrier(self);
                bc_heap_unlock();
                //ライトバリアーを確認
                gc_sweep(self);
        }
        return NULL;
}

static void bc_heap_lock() { g_rec_mutex_lock(&gHeapMtx); }

static void bc_heap_unlock() { g_rec_mutex_unlock(&gHeapMtx); }

static void bc_gc_lock() { g_rec_mutex_lock(&gGCMtx); }

static void bc_gc_unlock() { g_rec_mutex_unlock(&gGCMtx); }

#include "frame.h"
#include "../env/field.h"
#include "../env/generic_type.h"
#include "../env/heap.h"
#include "../env/object.h"
#include "../env/script_context.h"
#include "../util/mem.h"
#include "defer_context.h"

// proto
static void delete_defctx(bc_VectorItem e);
static void remove_from_parent(bc_Frame* self);
static void mark_recursive(bc_Frame* self);
static void frame_mark_defer(bc_Frame* self);
static void collect_recursive(bc_Frame* self, bc_Cache* cache);
static void frame_cache_defer(bc_Frame* self, bc_Cache* cache);

bc_Frame* bc_NewFrame() {
        bc_Frame* ret = (bc_Frame*)MEM_MALLOC(sizeof(bc_Frame));
        ret->ValueStack = bc_NewVector();
        ret->VariableTable = bc_NewVector();
        ret->Parent = NULL;
        ret->Level = 0;
        ret->IsTerminate = false;
        ret->IsValidate = false;
        ret->NativeThrowPos = -1;
        ret->Exception = NULL;
        ret->Children = bc_NewVector();
        ret->DeferAt = 0;
        ret->DeferList = NULL;
        ret->TypeArgs = bc_NewVector();
        ret->Receiver = NULL;
        ret->Coroutine = NULL;
        ret->ObjectSize = sizeof(bc_Object);
        return ret;
}

bc_Frame* bc_SubFrame(bc_Frame* parent) {
        bc_Frame* ret = bc_NewFrame();
        ret->Parent = parent;
        ret->Level = parent->Level + 1;
        ret->ContextRef = parent->ContextRef;
        bc_PushVector(parent->Children, ret);
        return ret;
}

void bc_MarkAllFrame(bc_Frame* self) {
        //全ての子要素を巡回してマーキング
        mark_recursive(self);
}

void bc_CollectAllFrame(bc_Frame* self, bc_Cache* cache) {
        collect_recursive(self, cache);
}

bc_GenericType* bc_GetRuntimeReceiver(bc_Frame* self) {
        return bc_AtVector(self->VariableTable, 0);
}

bc_Vector* bc_GetRuntimeTypeArguments(bc_Frame* self) { return self->TypeArgs; }

void bc_DeleteFrame(bc_Frame* self) {
        remove_from_parent(self);
        bc_ClearVector(self->ValueStack);
        bc_ClearVector(self->VariableTable);
        bc_DeleteVector(self->ValueStack, bc_VectorDeleterOfNull);
        bc_DeleteVector(self->VariableTable, bc_VectorDeleterOfNull);
        bc_DeleteVector(self->Children, bc_VectorDeleterOfNull);
        bc_DeleteVector(self->TypeArgs, bc_VectorDeleterOfNull);
        bc_DeleteVector(self->DeferList, delete_defctx);
        bc_CheckSTWRequest();
        MEM_FREE(self);
}

bc_Frame* bc_GetRootFrame(bc_Frame* self) {
        return self->Parent != NULL ? bc_GetRootFrame(self->Parent)
                                    : self->Parent;
}

// private
static void delete_defctx(bc_VectorItem e) {
        bc_DeferContext* defctx = (bc_DeferContext*)e;
        bc_DeleteDeferContext(defctx);
}

static void remove_from_parent(bc_Frame* self) {
        if (self->Parent != NULL) {
                int idx = bc_FindVector(self->Parent->Children, self);
                bc_RemoveVector(self->Parent->Children, idx);
        }
}

static void mark_recursive(bc_Frame* self) {
        for (int i = 0; i < self->Children->Length; i++) {
                bc_Frame* e = (bc_Frame*)bc_AtVector(self->Children, i);
                mark_recursive(e);
        }
        for (int i = 0; i < self->ValueStack->Length; i++) {
                bc_Object* e = (bc_Object*)bc_AtVector(self->ValueStack, i);
                bc_MarkAllObject(e);
        }
        for (int i = 0; i < self->VariableTable->Length; i++) {
                bc_Object* e = (bc_Object*)bc_AtVector(self->VariableTable, i);
                bc_MarkAllObject(e);
        }
        // deferのために一時的に保存された領域
        frame_mark_defer(self);
        //例外をマークする
        bc_MarkAllObject(self->Exception);
}

static void frame_mark_defer(bc_Frame* self) {
        if (self->DeferList == NULL) {
                return;
        }
        for (int i = 0; i < self->DeferList->Length; i++) {
                bc_DeferContext* defctx = bc_AtVector(self->DeferList, i);
                bc_Vector* bind = defctx->VariableTable;
                for (int j = 0; j < bind->Length; j++) {
                        bc_Object* e = bc_AtVector(bind, j);
                        bc_MarkAllObject(e);
                }
        }
}

static void collect_recursive(bc_Frame* self, bc_Cache* cache) {
        for (int i = 0; i < self->Children->Length; i++) {
                bc_Frame* e = (bc_Frame*)bc_AtVector(self->Children, i);
                collect_recursive(e, cache);
        }
        for (int i = 0; i < self->ValueStack->Length; i++) {
                bc_Object* e = (bc_Object*)bc_AtVector(self->ValueStack, i);
                bc_AddRoot(e);
        }
        for (int i = 0; i < self->VariableTable->Length; i++) {
                bc_Object* e = (bc_Object*)bc_AtVector(self->VariableTable, i);
                bc_AddRoot(e);
        }
        // deferのために一時的に保存された領域
        frame_cache_defer(self, cache);
        //例外をマークする
        if (self->Exception != NULL) {
                bc_AddRoot(self->Exception);
        }
}

static void frame_cache_defer(bc_Frame* self, bc_Cache* cache) {
        if (self->DeferList == NULL) {
                return;
        }
        for (int i = 0; i < self->DeferList->Length; i++) {
                bc_DeferContext* defctx = bc_AtVector(self->DeferList, i);
                bc_Vector* bind = defctx->VariableTable;
                for (int j = 0; j < bind->Length; j++) {
                        bc_Object* e = bc_AtVector(bind, j);
                        bc_AddRoot(e);
                }
        }
}
#include "frame.h"
#include "../env/script_context.h"
#include "../env/object.h"
#include "../env/field.h"
#include "../env/heap.h"
#include "../util/mem.h"
#include "defer_context.h"

//proto
static void remove_from_parent(Frame* self);
static void frame_markStatic(field* item);
static void frame_markRecursive(Frame* self);
static void frame_mark_defer(Frame* self);
static void DeleteFrame_defctx(VectorItem e);

Frame* NewFrame() {
	Frame* ret = (Frame*)MEM_MALLOC(sizeof(Frame));
	ret->ValueStack = NewVector();
	ret->VariableTable = NewVector();
	ret->Parent = NULL;
	ret->Level = 0;
	ret->IsTerminate = false;
	ret->IsValidate = false;
	ret->NativeThrowPos = -1;
	ret->Exception = NULL;
	ret->Children = NewVector();
	ret->DeferAt = 0;
	ret->DeferList = NULL;
	ret->TypeArgs = NewVector();
	ret->Receiver = NULL;
	ret->Coroutine = NULL;
	return ret;
}

Frame* SubFrame(Frame* parent) {
	Frame* ret = NewFrame();
	ret->Parent = parent;
	ret->Level = parent->Level + 1;
	ret->ContextRef = parent->ContextRef;
	PushVector(parent->Children, ret);
	return ret;
}

void MarkAllFrame(Frame* self) {
	//全ての静的フィールドをマークする
	script_context* ctx = GetCurrentScriptContext();
	EachStaticScriptContext(ctx, frame_markStatic);
	//全ての子要素を巡回してマーキング
	frame_markRecursive(self);
}

void DeleteFrame(Frame* self) {
	remove_from_parent(self);
	ClearVector(self->ValueStack);
	ClearVector(self->VariableTable);
	CollectHeap(GetHeap());
	DeleteVector(self->ValueStack, VectorDeleterOfNull);
	DeleteVector(self->VariableTable, VectorDeleterOfNull);
	DeleteVector(self->Children, VectorDeleterOfNull);
	DeleteVector(self->TypeArgs, VectorDeleterOfNull);
	DeleteVector(self->DeferList, DeleteFrame_defctx);
	MEM_FREE(self);
}

Frame* GetRootFrame(Frame* self) {
	return self->Parent != NULL ? GetRootFrame(self->Parent) : self->Parent;
}

//private
static void remove_from_parent(Frame* self) {
	if (self->Parent != NULL) {
		int idx = FindVector(self->Parent->Children, self);
		RemoveVector(self->Parent->Children, idx);
	}
}

static void frame_markStatic(field* item) {
	//フィールドがintなどならここでマークしない
	//静的定数フィールドに初期値が割り当てられていない場合
	if(item->static_value != NULL &&
	   item->static_value->paint != PAINT_ONEXIT_T) {
		MarkAllObject(item->static_value);
	}
}

static void frame_markRecursive(Frame* self) {
	for (int i = 0; i < self->Children->Length; i++) {
		Frame* e = (Frame*)AtVector(self->Children, i);
		frame_markRecursive(e);
	}
	for (int i = 0; i < self->ValueStack->Length; i++) {
		object* e = (object*)AtVector(self->ValueStack, i);
		MarkAllObject(e);
	}
	for (int i = 0; i < self->VariableTable->Length; i++) {
		object* e = (object*)AtVector(self->VariableTable, i);
		MarkAllObject(e);
	}
	//deferのために一時的に保存された領域
	frame_mark_defer(self);
	//例外をマークする
	MarkAllObject(self->Exception);
}

static void frame_mark_defer(Frame* self) {
	if(self->DeferList == NULL) {
		return;
	}
	for(int i=0; i<self->DeferList->Length; i++) {
		DeferContext* defctx = AtVector(self->DeferList, i);
		Vector* bind = defctx->VariableTable;
		for(int j=0; j<bind->Length; j++) {
			object* e = AtVector(bind, j);
			MarkAllObject(e);
		}
	}
}
static void DeleteFrame_defctx(VectorItem e) {
	DeferContext* defctx = (DeferContext*)e;
	DeleteDeferContext(defctx);
}
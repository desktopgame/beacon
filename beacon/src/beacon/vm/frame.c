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
	ret->value_stack = NewVector();
	ret->ref_stack = NewVector();
	ret->parent = NULL;
	ret->level = 0;
	ret->terminate = false;
	ret->validate = false;
	ret->native_throw_pos = -1;
	ret->exception = NULL;
	ret->children_vec = NewVector();
	ret->defer_at = 0;
	ret->defer_vec = NULL;
	ret->type_args_vec = NewVector();
	ret->receiver = NULL;
	ret->coroutine = NULL;
	return ret;
}

Frame* SubFrame(Frame* parent) {
	Frame* ret = NewFrame();
	ret->parent = parent;
	ret->level = parent->level + 1;
	ret->context_ref = parent->context_ref;
	PushVector(parent->children_vec, ret);
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
	ClearVector(self->value_stack);
	ClearVector(self->ref_stack);
	CollectHeap(GetHeap());
	DeleteVector(self->value_stack, VectorDeleterOfNull);
	DeleteVector(self->ref_stack, VectorDeleterOfNull);
	DeleteVector(self->children_vec, VectorDeleterOfNull);
	DeleteVector(self->type_args_vec, VectorDeleterOfNull);
	DeleteVector(self->defer_vec, DeleteFrame_defctx);
	MEM_FREE(self);
}

Frame* GetRootFrame(Frame* self) {
	return self->parent != NULL ? GetRootFrame(self->parent) : self->parent;
}

//private
static void remove_from_parent(Frame* self) {
	if (self->parent != NULL) {
		int idx = FindVector(self->parent->children_vec, self);
		RemoveVector(self->parent->children_vec, idx);
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
	for (int i = 0; i < self->children_vec->Length; i++) {
		Frame* e = (Frame*)AtVector(self->children_vec, i);
		frame_markRecursive(e);
	}
	for (int i = 0; i < self->value_stack->Length; i++) {
		object* e = (object*)AtVector(self->value_stack, i);
		MarkAllObject(e);
	}
	for (int i = 0; i < self->ref_stack->Length; i++) {
		object* e = (object*)AtVector(self->ref_stack, i);
		MarkAllObject(e);
	}
	//deferのために一時的に保存された領域
	frame_mark_defer(self);
	//例外をマークする
	MarkAllObject(self->exception);
}

static void frame_mark_defer(Frame* self) {
	if(self->defer_vec == NULL) {
		return;
	}
	for(int i=0; i<self->defer_vec->Length; i++) {
		DeferContext* defctx = AtVector(self->defer_vec, i);
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
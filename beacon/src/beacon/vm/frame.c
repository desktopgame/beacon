#include "frame.h"
#include "../env/script_context.h"
#include "../env/object.h"
#include "../env/field.h"
#include "../env/heap.h"
#include "../util/mem.h"
#include "defer_context.h"

//proto
static void remove_from_parent(frame* self);
static void frame_markStatic(field* item);
static void frame_markRecursive(frame* self);
static void frame_mark_defer(frame* self);
static void frame_delete_defctx(VectorItem e);

frame * frame_new() {
	frame* ret = (frame*)MEM_MALLOC(sizeof(frame));
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

frame * frame_sub(frame * parent) {
	frame* ret = frame_new();
	ret->parent = parent;
	ret->level = parent->level + 1;
	ret->context_ref = parent->context_ref;
	PushVector(parent->children_vec, ret);
	return ret;
}

void frame_markall(frame * self) {
	//全ての静的フィールドをマークする
	script_context* ctx = script_context_get_current();
	script_context_static_each(ctx, frame_markStatic);
	//全ての子要素を巡回してマーキング
	frame_markRecursive(self);
}

void frame_delete(frame * self) {
	remove_from_parent(self);
	ClearVector(self->value_stack);
	ClearVector(self->ref_stack);
	heap_gc(heap_get());
	DeleteVector(self->value_stack, VectorDeleterOfNull);
	DeleteVector(self->ref_stack, VectorDeleterOfNull);
	DeleteVector(self->children_vec, VectorDeleterOfNull);
	DeleteVector(self->type_args_vec, VectorDeleterOfNull);
	DeleteVector(self->defer_vec, frame_delete_defctx);
	MEM_FREE(self);
}

frame* frame_root(frame* self) {
	return self->parent != NULL ? frame_root(self->parent) : self->parent;
}

//private
static void remove_from_parent(frame* self) {
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
		object_markall(item->static_value);
	}
}

static void frame_markRecursive(frame* self) {
	for (int i = 0; i < self->children_vec->length; i++) {
		frame* e = (frame*)AtVector(self->children_vec, i);
		frame_markRecursive(e);
	}
	for (int i = 0; i < self->value_stack->length; i++) {
		object* e = (object*)AtVector(self->value_stack, i);
		object_markall(e);
	}
	for (int i = 0; i < self->ref_stack->length; i++) {
		object* e = (object*)AtVector(self->ref_stack, i);
		object_markall(e);
	}
	//deferのために一時的に保存された領域
	frame_mark_defer(self);
	//例外をマークする
	object_markall(self->exception);
}

static void frame_mark_defer(frame* self) {
	if(self->defer_vec == NULL) {
		return;
	}
	for(int i=0; i<self->defer_vec->length; i++) {
		defer_context* defctx = AtVector(self->defer_vec, i);
		Vector* bind = defctx->variable_vec;
		for(int j=0; j<bind->length; j++) {
			object* e = AtVector(bind, j);
			object_markall(e);
		}
	}
}
static void frame_delete_defctx(VectorItem e) {
	defer_context* defctx = (defer_context*)e;
	defer_context_delete(defctx);
}
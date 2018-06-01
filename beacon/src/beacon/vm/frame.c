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

frame * frame_new() {
	frame* ret = (frame*)MEM_MALLOC(sizeof(frame));
	ret->value_stack = vector_new();
	ret->ref_stack = vector_new();
	ret->parent = NULL;
	ret->level = 0;
	ret->terminate = false;
	ret->validate = false;
	ret->native_throw_pos = -1;
	ret->exception = NULL;
	ret->children_vec = vector_new();
	ret->defer_at = 0;
	//ret->defer_vec = vector_new();
	ret->type_args_vec = vector_new();
	return ret;
}

frame * frame_sub(frame * parent) {
	frame* ret = frame_new();
	ret->parent = parent;
	ret->level = parent->level + 1;
	ret->context_ref = parent->context_ref;
	vector_push(parent->children_vec, ret);
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
	vector_clear(self->value_stack);
	vector_clear(self->ref_stack);
	heap_gc(heap_get());
	//これは使い回せないので、
	//VMを起動する前に毎回確保して、毎回捨てる
	//vector_delete(self->defer_vec, vector_deleter_null);
	vector_delete(self->value_stack, vector_deleter_null);
	vector_delete(self->ref_stack, vector_deleter_null);
	vector_delete(self->children_vec, vector_deleter_null);
	vector_delete(self->type_args_vec, vector_deleter_null);
	MEM_FREE(self);
}

//private

static void remove_from_parent(frame* self) {
	if (self->parent != NULL) {
		int idx = vector_find(self->parent->children_vec, self);
		vector_remove(self->parent->children_vec, idx);
	}
}

static void frame_markStatic(field* item) {
	object_markall(item->static_value);
}

static void frame_markRecursive(frame* self) {
	for (int i = 0; i < self->children_vec->length; i++) {
		frame* e = (frame*)vector_at(self->children_vec, i);
		frame_markRecursive(e);
	}
	for (int i = 0; i < self->value_stack->length; i++) {
		object* e = (object*)vector_at(self->value_stack, i);
		object_markall(e);
	}
	for (int i = 0; i < self->ref_stack->length; i++) {
		object* e = (object*)vector_at(self->ref_stack, i);
		object_markall(e);
	}
	for(int i=0; i<self->defer_vec->length; i++) {
		defer_context* defctx = vector_at(self->defer_vec, i);
		vector* bind = defctx->bind;
		for(int j=0; j<bind->length; j++) {
			object* e = vector_at(bind, j);
			object_markall(e);
		}
	}
	//例外をマークする
	object_markall(self->exception);
}
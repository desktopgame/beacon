#include "object.h"
#include "namespace.h"
#include "../util/string_buffer.h"
#include <stdlib.h>
#include "vtable.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "type_interface.h"
#include "script_context.h"
#include <assert.h>
#include "type_impl.h"
#include "../lib/beacon/lang/bc_array.h"
#include "heap.h"
#include "generic_type.h"
#include "../vm/yield_context.h"

//proto
static object* object_mallocImpl(object_tag type, const char* filename, int lineno);
static void object_delete_self(vector_item item);
static void object_mark_coroutine(object* self);
#define object_malloc(type) (object_mallocImpl(type, __FILE__, __LINE__))
//static object* object_malloc(object_tag type);
//static object* gObjectTrue = NULL;
//static object* gObjectFalse = NULL;
//static object* gObjectNull = NULL;
static int gObjectCount = 0;


object * object_int_malloc(int i, const char* filename, int lineno) {
	object* ret = object_mallocImpl(object_int_T, filename, lineno);
	ret->u.int_ = i;
	ret->gtype = GENERIC_INT;
	ret->vptr = type_vtable(TYPE_INT);
	return ret;
}

object* object_int_get(int i) {
	script_context* ctx = script_context_get_current();
	script_context_cache();
	if((i < -9) || i > 99) {
		return script_context_iintern(ctx, i);
		//return object_int_new(i);
	}
	if(i < 0) { return (object*)vector_at(ctx->neg_int_vec, (-i) - 1); }
	return (object*)vector_at(ctx->pos_int_vec, i);
}

object * object_double_malloc(double d, const char* filename, int lineno) {
	object* ret = object_mallocImpl(object_double_T, filename, lineno);
	ret->u.double_ = d;
	ret->gtype = GENERIC_DOUBLE;
	ret->vptr = type_vtable(TYPE_DOUBLE);
	return ret;
}

object* object_long_malloc(long l, const char* filename, int lineno) {
	object* ret = object_mallocImpl(object_long_T, filename, lineno);
	ret->u.long_ = l;
	ret->gtype = GENERIC_OBJECT;
	ret->vptr = type_vtable(TYPE_OBJECT);
	return ret;
}

object * object_char_malloc(char c, const char* filename, int lineno) {
	object* ret = object_mallocImpl(object_char_T, filename, lineno);
	ret->u.char_ = c;
	ret->gtype = GENERIC_CHAR;
	ret->vptr = type_vtable(TYPE_CHAR);
	return ret;
}

object * object_string_malloc(const char * s, const char* filename, int lineno) {
	object* ret = object_mallocImpl(object_string_T, filename, lineno);
	//ret->u.string_ = s;
	ret->u.field_vec = vector_new();
	ret->gtype = GENERIC_STRING;
	ret->vptr = type_vtable(TYPE_STRING);

	//配列を生成
	object* arr = object_ref_malloc(filename, lineno);
	//arr->tag = object_array_T;
	type* arrType = bc_array_type();
	type* strType = namespace_get_type(namespace_lang(), string_pool_intern("String"));
	arr->gtype = generic_type_new(arrType);
	arr->vptr = type_vtable(arrType);
	arr->tag = object_array_T;
	generic_type_addargs(arr->gtype, GENERIC_CHAR);
	//ボックス化
	const char* itr = s;
	string_buffer* sb = string_buffer_new();
	while ((*itr) != '\0') {
		char e = (*itr);
		vector_push(arr->native_slot_vec, object_char_malloc(e, filename, lineno));
		itr++;
		string_buffer_append(sb, e);
	}
	string_buffer_shrink(sb);
	//String#charArrayを埋める
	int temp = 0;
	class_find_field(strType->u.class_, string_pool_intern("charArray"), &temp);
	vector_assign(ret->u.field_vec, temp, arr);
	vector_item* test = vector_at(ret->u.field_vec, temp);
	assert(test != NULL);
	//Array#lengthを埋める
	temp = 0;
	class_find_field(arrType->u.class_, string_pool_intern("length"), &temp);
	vector_assign(arr->u.field_vec, temp, object_int_new(sb->length));
	//C形式の文字列でも保存
	vector_assign(ret->native_slot_vec, 0, sb);
	return ret;
}

object * object_ref_malloc(const char* filename, int lineno) {
	object* ret= object_mallocImpl(object_ref_T, filename, lineno);
	ret->u.field_vec = vector_malloc(filename, lineno);
	return ret;
}

object * object_bool_get(bool b) {
	return (b ? object_get_true() : object_get_false());
}

object * object_get_true() {
	script_context* ctx = script_context_get_current();
	if (ctx->oTrue == NULL) {
		ctx->oTrue = object_malloc(object_bool_T);
		ctx->oTrue->u.bool_ = true;
		ctx->oTrue->gtype = GENERIC_BOOL;
		ctx->oTrue->vptr = TYPE2CLASS(TYPE_BOOL)->vt;
		ctx->oTrue->paint = paint_onexit_T;
	}
	return ctx->oTrue;
}

object * object_get_false() {
	script_context* ctx = script_context_get_current();
	if (ctx->oFalse == NULL) {
		ctx->oFalse = object_malloc(object_bool_T);
		ctx->oFalse->u.bool_ = false;
		ctx->oFalse->gtype = GENERIC_BOOL;
		ctx->oFalse->vptr = TYPE2CLASS(TYPE_BOOL)->vt;
		ctx->oFalse->paint = paint_onexit_T;
	}
	return ctx->oFalse;
}

object * object_get_null() {
	script_context* ctx = script_context_get_current();
	if (ctx->oNull == NULL) {
		ctx->oNull = object_malloc(object_null_T);
		ctx->oNull->gtype = generic_type_new(TYPE_NULL);
		ctx->oNull->paint = paint_onexit_T;
	}
	return ctx->oNull;
}

void object_inc(object * self) {
	if (self->tag == object_int_T) {
		self->u.int_++;
	} else if (self->tag == object_double_T) {
		self->u.double_++;
	} else assert(false);
}

void object_dec(object * self) {
	if (self->tag == object_int_T) {
		self->u.int_--;
	} else if (self->tag == object_double_T) {
		self->u.double_--;
	} else  assert(false);
}

object* object_copy(object * self) {
	/*
	object* ret = NULL;
	if (self->tag == object_int_T) {
		ret = object_int_new(self->u.int_);
	} else if (self->tag == object_double_T) {
		ret = object_double_new(self->u.double_);
	} else if (self->tag == object_char_T) {
		ret = object_char_new(self->u.char_);
	} else {
		ret = self;
	}
	return ret;
	*/
	return self;
}

object* object_clone(object* self) {
	if(self->tag != object_array_T &&
	   self->tag != object_ref_T &&
	   self->tag != object_string_T) {
		   return object_copy(self);
	}
	object* ret = NULL;
	if(self->tag == object_ref_T) {
		ret = object_ref_new();
		ret->gtype = self->gtype;
		ret->vptr = self->vptr;
		ret->u.field_vec = self->u.field_vec;
	} else if(self->tag == object_array_T) {
		ret = object_ref_new();
		ret->gtype = self->gtype;
		ret->vptr = self->vptr;
		ret->native_slot_vec = self->native_slot_vec;
		ret->u.field_vec = self->u.field_vec;
	} else if(self->tag == object_string_T) {
		ret = object_ref_new();
		ret->gtype = self->gtype;
		ret->vptr = self->vptr;
		ret->native_slot_vec = self->native_slot_vec;
		ret->u.field_vec = self->u.field_vec;
	}
	return ret;
}

void object_paintall(object* self, object_paint paint) {
	//field#static_valueは
	//実際に修飾子が static でないときは NULL
	if (self == NULL) {
		return;
	}
	if (self->paint == paint) {
		return;
	}
	if (self->paint != paint_onexit_T) {
		self->paint = paint;
	}
	//フィールドを全てマーク
	if (self->tag == object_string_T ||
		self->tag == object_ref_T) {
		for (int i = 0; i < self->u.field_vec->length; i++) {
			object* e = (object*)vector_at(self->u.field_vec, i);
			object_paintall(e, paint);
		}
	}
	//配列型ならスロットも全てマーク
	type* arrayType = bc_array_type();
	if (self->tag == object_ref_T &&
		self->gtype->core_type == arrayType) {
		for (int i = 0; i < self->native_slot_vec->length; i++) {
			object* e = (object*)vector_at(self->native_slot_vec, i);
			object_paintall(e, paint);
		}
	}
	//コルーチンならその中身をマークする
	object_mark_coroutine(self);
}

void object_markall(object * self) {
	object_paintall(self, paint_marked_T);
}

int object_count() {
	return gObjectCount;
}

void object_print(object * self) {
	if (self->tag == object_int_T) {
		printf("Int: %d", self->u.int_);
	} else if (self->tag == object_double_T) {
		printf("Double: %lf", self->u.double_);
	} else if (self->tag == object_string_T) {
		string_buffer* sb = (string_buffer*)vector_at(self->native_slot_vec, 0);
		printf("String: %s", sb->text);
	} else if (self->tag == object_bool_T) {
		printf("Bool: %s", (self == object_get_true() ? "true" : "false"));
	} else if (self->tag == object_null_T) {
		printf("Ref: Null");
	} else if (self->tag == object_ref_T) {
		printf("Ref: ");
		generic_type_print(self->gtype);
	}
}

void object_delete(object * self) {
	gObjectCount--;
	if(self->is_coroutine) {
		yield_context* yctx = vector_at(self->native_slot_vec, 0);
		vector_remove(self->native_slot_vec, 0);
		yield_context_delete(yctx);
	}
	if (self->tag == object_string_T) {
		string_buffer* sb = vector_at(self->native_slot_vec, 0);
		vector_remove(self->native_slot_vec, 0);
		string_buffer_delete(sb);
	}
	if (self->tag == object_string_T ||
		self->tag == object_ref_T ||
		self->tag == object_array_T) {
		vector_delete(self->u.field_vec, vector_deleter_null);
	}
	vector_delete(self->native_slot_vec, vector_deleter_null);
	MEM_FREE(self);
}

void object_destroy(object* self) {
	if (self == NULL) {
		return;
	}
	type* tp = self->gtype->core_type;
	assert(self->paint == paint_onexit_T);
	if (self->tag == object_ref_T ||
	   self->tag == object_string_T ||
		self->tag == object_array_T) {
		vector_delete(self->u.field_vec, object_delete_self);
		self->u.field_vec = NULL;
	}
	//String#charArray
	if (self->tag == object_array_T) {
		vector_delete(self->u.field_vec, object_delete_self);
		vector_delete(self->native_slot_vec, object_delete_self);
		self->native_slot_vec = NULL;
		self->u.field_vec = NULL;
	}
	//io_printfln("delete object %s", type_name(obj->type));
	object_delete(self);
}

int object_obj2int(object* self) {
	assert(self->tag == object_int_T);
	return self->u.int_;
}

double object_obj2double(object* self) {
	assert(self->tag == object_double_T);
	return self->u.double_;
}

bool object_obj2bool(object* self) {
	assert(self->tag == object_bool_T);
	return self->u.bool_;
}

char object_obj2char(object* self) {
	assert(self->tag == object_char_T);
	return self->u.char_;
}

long object_obj2long(object* self) {
	assert(self->tag == object_long_T);
	return self->u.long_;
}

object* object_int2obj(int i) {
	return object_int_new(i);
}

object* object_double2obj(double d) {
	return object_double_new(d);
}

object* object_bool2obj(bool b) {
	return object_bool_get(b);
}

object* object_char2obj(char c) {
	return object_char_new(c);
}

object* object_long2obj(long l) {
	return object_long_new(l);
}

object* object_default(generic_type* gt) {
	object* a = object_get_null();
	if (gt->core_type == TYPE_INT) {
		a = object_int_get(0);
	} else if (gt->core_type == TYPE_DOUBLE) {
		a = object_double_new(0.0);
	} else if (gt->core_type == TYPE_BOOL) {
		a = object_bool_get(false);
	} else if (gt->core_type == TYPE_CHAR) {
		a = object_char_new('\0');
	}
	return a;
}

const char* object_name(object* self) {
	const char* name = "NULL";
	if(self->gtype != NULL && self->gtype->core_type != NULL) {
		name = string_pool_ref2str(type_full_name(self->gtype->core_type));
	}
	return name;
}

//private
static object* object_mallocImpl(object_tag type, const char* filename, int lineno) {
	object* ret = (object*)mem_malloc(sizeof(object), filename, lineno);
	ret->is_coroutine = false;
	ret->gtype = NULL;
	ret->paint = paint_unmarked_T;
	ret->tag = type;
	ret->vptr = NULL;
	if (type == object_string_T ||
		type == object_array_T ||
		type == object_ref_T) {
		ret->native_slot_vec = vector_malloc(filename, lineno);
	} else {
		ret->native_slot_vec = NULL;
	}
	heap_add(heap_get(), ret);
	gObjectCount++;
	return ret;
}

static void object_delete_self(vector_item item) {
	object* e = (object*)item;
	object_destroy(e);
}

static void object_mark_coroutine(object* self) {
	if(!self->is_coroutine) {
		return;
	}
	//コルーチンの現在の値
	yield_context* yctx = vector_at(self->native_slot_vec, 0);
	object_markall(yctx->stock_obj);
	object_markall(yctx->source_obj);
	//コルーチンに渡された引数
	for(int i=0; i<yctx->parameter_vec->length; i++) {
		object_markall(vector_at(yctx->parameter_vec, i));
	}
}
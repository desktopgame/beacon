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
#include "TYPE_IMPL.h"
#include "../lib/beacon/lang/bc_array.h"
#include "heap.h"
#include "generic_type.h"
#include "../vm/yield_context.h"

//proto
static object* object_mallocImpl(object_tag type, const char* filename, int lineno);
static void object_delete_self(VectorItem item);
static void object_mark_coroutine(object* self);
#define object_malloc(type) (object_mallocImpl(type, __FILE__, __LINE__))
//static object* object_malloc(object_tag type);
//static object* gObjectTrue = NULL;
//static object* gObjectFalse = NULL;
//static object* gObjectNull = NULL;
static int gObjectCount = 0;


object * object_int_malloc(int i, const char* filename, int lineno) {
	object* ret = object_mallocImpl(OBJECT_INT_T, filename, lineno);
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
	if(i < 0) { return (object*)AtVector(ctx->neg_int_vec, (-i) - 1); }
	return (object*)AtVector(ctx->pos_int_vec, i);
}

object * object_double_malloc(double d, const char* filename, int lineno) {
	object* ret = object_mallocImpl(OBJECT_DOUBLE_T, filename, lineno);
	ret->u.double_ = d;
	ret->gtype = GENERIC_DOUBLE;
	ret->vptr = type_vtable(TYPE_DOUBLE);
	return ret;
}

object* object_long_malloc(long l, const char* filename, int lineno) {
	object* ret = object_mallocImpl(OBJECT_LONG_T, filename, lineno);
	ret->u.long_ = l;
	ret->gtype = GENERIC_OBJECT;
	ret->vptr = type_vtable(TYPE_OBJECT);
	return ret;
}

object * object_char_malloc(char c, const char* filename, int lineno) {
	object* ret = object_mallocImpl(OBJECT_CHAR_T, filename, lineno);
	ret->u.char_ = c;
	ret->gtype = GENERIC_CHAR;
	ret->vptr = type_vtable(TYPE_CHAR);
	return ret;
}

object * object_string_malloc(const char * s, const char* filename, int lineno) {
	object* ret = object_mallocImpl(OBJECT_STRING_T, filename, lineno);
	//ret->u.string_ = s;
	ret->u.field_vec = NewVector();
	ret->gtype = GENERIC_STRING;
	ret->vptr = type_vtable(TYPE_STRING);

	//配列を生成
	object* arr = object_ref_malloc(filename, lineno);
	//arr->tag = OBJECT_ARRAY_T;
	type* arrType = bc_array_type();
	type* strType = namespace_get_type(namespace_lang(), InternString("String"));
	arr->gtype = generic_type_new(arrType);
	arr->vptr = type_vtable(arrType);
	arr->tag = OBJECT_ARRAY_T;
	generic_type_addargs(arr->gtype, GENERIC_CHAR);
	//ボックス化
	const char* itr = s;
	string_buffer* sb = NewBuffer();
	while ((*itr) != '\0') {
		char e = (*itr);
		PushVector(arr->native_slot_vec, object_char_malloc(e, filename, lineno));
		itr++;
		AppendBuffer(sb, e);
	}
	ShrinkBuffer(sb);
	//String#charArrayを埋める
	int temp = 0;
	class_find_field(strType->u.class_, InternString("charArray"), &temp);
	AssignVector(ret->u.field_vec, temp, arr);
	VectorItem* test = AtVector(ret->u.field_vec, temp);
	assert(test != NULL);
	//Array#lengthを埋める
	temp = 0;
	class_find_field(arrType->u.class_, InternString("length"), &temp);
	AssignVector(arr->u.field_vec, temp, object_int_new(sb->length));
	//C形式の文字列でも保存
	AssignVector(ret->native_slot_vec, 0, sb);
	return ret;
}

object * object_ref_malloc(const char* filename, int lineno) {
	object* ret= object_mallocImpl(OBJECT_REF_T, filename, lineno);
	ret->u.field_vec = MallocVector(filename, lineno);
	return ret;
}

object * object_bool_get(bool b) {
	return (b ? object_get_true() : object_get_false());
}

object * object_get_true() {
	script_context* ctx = script_context_get_current();
	if (ctx->true_obj == NULL) {
		ctx->true_obj = object_malloc(OBJECT_BOOL_T);
		ctx->true_obj->u.bool_ = true;
		ctx->true_obj->gtype = GENERIC_BOOL;
		ctx->true_obj->vptr = TYPE2CLASS(TYPE_BOOL)->vt;
		ctx->true_obj->paint = PAINT_ONEXIT_T;
	}
	return ctx->true_obj;
}

object * object_get_false() {
	script_context* ctx = script_context_get_current();
	if (ctx->false_obj == NULL) {
		ctx->false_obj = object_malloc(OBJECT_BOOL_T);
		ctx->false_obj->u.bool_ = false;
		ctx->false_obj->gtype = GENERIC_BOOL;
		ctx->false_obj->vptr = TYPE2CLASS(TYPE_BOOL)->vt;
		ctx->false_obj->paint = PAINT_ONEXIT_T;
	}
	return ctx->false_obj;
}

object * object_get_null() {
	script_context* ctx = script_context_get_current();
	if (ctx->null_obj == NULL) {
		ctx->null_obj = object_malloc(OBJECT_NULL_T);
		ctx->null_obj->gtype = generic_type_new(TYPE_NULL);
		ctx->null_obj->paint = PAINT_ONEXIT_T;
	}
	return ctx->null_obj;
}

void object_inc(object * self) {
	if (self->tag == OBJECT_INT_T) {
		self->u.int_++;
	} else if (self->tag == OBJECT_DOUBLE_T) {
		self->u.double_++;
	} else assert(false);
}

void object_dec(object * self) {
	if (self->tag == OBJECT_INT_T) {
		self->u.int_--;
	} else if (self->tag == OBJECT_DOUBLE_T) {
		self->u.double_--;
	} else  assert(false);
}

object* object_copy(object * self) {
	/*
	object* ret = NULL;
	if (self->tag == OBJECT_INT_T) {
		ret = object_int_new(self->u.int_);
	} else if (self->tag == OBJECT_DOUBLE_T) {
		ret = object_double_new(self->u.double_);
	} else if (self->tag == OBJECT_CHAR_T) {
		ret = object_char_new(self->u.char_);
	} else {
		ret = self;
	}
	return ret;
	*/
	return self;
}

object* object_clone(object* self) {
	if(self->tag != OBJECT_ARRAY_T &&
	   self->tag != OBJECT_REF_T &&
	   self->tag != OBJECT_STRING_T) {
		   return object_copy(self);
	}
	object* ret = NULL;
	if(self->tag == OBJECT_REF_T ||
	   self->tag == OBJECT_ARRAY_T ||
	   self->tag == OBJECT_STRING_T) {
		ret = object_mallocImpl(OBJECT_INT_T, __FILE__, __LINE__);
		ret->tag = self->tag;
		ret->gtype = self->gtype;
		ret->vptr = self->vptr;
		ret->native_slot_vec  = self->native_slot_vec;
		ret->u.field_vec = self->u.field_vec;
	}
	ret->is_clone = true;
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
	if (self->paint != PAINT_ONEXIT_T) {
		self->paint = paint;
	}
	//フィールドを全てマーク
	if (self->tag == OBJECT_STRING_T ||
		self->tag == OBJECT_REF_T ||
		self->tag == OBJECT_ARRAY_T) {
		for (int i = 0; i < self->u.field_vec->length; i++) {
			object* e = (object*)AtVector(self->u.field_vec, i);
			object_paintall(e, paint);
		}
	}
	//配列型ならスロットも全てマーク
	type* arrayType = bc_array_type();
	if (self->gtype->core_type == arrayType) {
		for (int i = 0; i < self->native_slot_vec->length; i++) {
			object* e = (object*)AtVector(self->native_slot_vec, i);
			object_paintall(e, paint);
		}
	}
	//コルーチンならその中身をマークする
	object_mark_coroutine(self);
}

void object_markall(object * self) {
	object_paintall(self, PAINT_MARKED_T);
}

int object_count() {
	return gObjectCount;
}

void object_print(object * self) {
	if (self->tag == OBJECT_INT_T) {
		printf("Int: %d", self->u.int_);
	} else if (self->tag == OBJECT_DOUBLE_T) {
		printf("Double: %lf", self->u.double_);
	} else if (self->tag == OBJECT_STRING_T) {
		string_buffer* sb = (string_buffer*)AtVector(self->native_slot_vec, 0);
		printf("String: %s", sb->text);
	} else if (self->tag == OBJECT_BOOL_T) {
		printf("Bool: %s", (self == object_get_true() ? "true" : "false"));
	} else if (self->tag == OBJECT_NULL_T) {
		printf("Ref: Null");
	} else if (self->tag == OBJECT_REF_T) {
		printf("Ref: ");
		generic_type_print(self->gtype);
	}
}

void object_delete(object * self) {
	gObjectCount--;
	if(self->is_clone) {
		MEM_FREE(self);
		return;
	}
	if(self->is_coroutine) {
		yield_context* yctx = AtVector(self->native_slot_vec, 0);
		RemoveVector(self->native_slot_vec, 0);
		DeleteYieldContext(yctx);
	}
	if (self->tag == OBJECT_STRING_T) {
		string_buffer* sb = AtVector(self->native_slot_vec, 0);
		RemoveVector(self->native_slot_vec, 0);
		DeleteBuffer(sb);
	}
	if (self->tag == OBJECT_STRING_T ||
		self->tag == OBJECT_REF_T ||
		self->tag == OBJECT_ARRAY_T) {
		DeleteVector(self->u.field_vec, VectorDeleterOfNull);
	}
	DeleteVector(self->native_slot_vec, VectorDeleterOfNull);
	MEM_FREE(self);
}

void object_destroy(object* self) {
	if (self == NULL) {
		return;
	}
	type* tp = self->gtype->core_type;
	assert(self->paint == PAINT_ONEXIT_T);
	if (self->tag == OBJECT_REF_T ||
	   self->tag == OBJECT_STRING_T ||
		self->tag == OBJECT_ARRAY_T) {
		DeleteVector(self->u.field_vec, object_delete_self);
		self->u.field_vec = NULL;
	}
	//String#charArray
	if (self->tag == OBJECT_ARRAY_T) {
		DeleteVector(self->u.field_vec, object_delete_self);
		DeleteVector(self->native_slot_vec, object_delete_self);
		self->native_slot_vec = NULL;
		self->u.field_vec = NULL;
	}
	//Printfln("delete object %s", type_name(obj->type));
	object_delete(self);
}

int object_obj2int(object* self) {
	assert(self->tag == OBJECT_INT_T);
	return self->u.int_;
}

double object_obj2double(object* self) {
	assert(self->tag == OBJECT_DOUBLE_T);
	return self->u.double_;
}

bool object_obj2bool(object* self) {
	assert(self->tag == OBJECT_BOOL_T);
	return self->u.bool_;
}

char object_obj2char(object* self) {
	assert(self->tag == OBJECT_CHAR_T);
	return self->u.char_;
}

long object_obj2long(object* self) {
	assert(self->tag == OBJECT_LONG_T);
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
		name = Ref2Str(type_full_name(self->gtype->core_type));
	}
	return name;
}

//private
static object* object_mallocImpl(object_tag type, const char* filename, int lineno) {
	object* ret = (object*)mem_malloc(sizeof(object), filename, lineno);
	ret->is_coroutine = false;
	ret->gtype = NULL;
	ret->paint = PAINT_UNMARKED_T;
	ret->tag = type;
	ret->vptr = NULL;
	ret->is_clone = false;
	if (type == OBJECT_STRING_T ||
		type == OBJECT_ARRAY_T ||
		type == OBJECT_REF_T) {
		ret->native_slot_vec = MallocVector(filename, lineno);
	} else {
		ret->native_slot_vec = NULL;
	}
	AddHeap(GetHeap(), ret);
	gObjectCount++;
	return ret;
}

static void object_delete_self(VectorItem item) {
	object* e = (object*)item;
	object_destroy(e);
}

static void object_mark_coroutine(object* self) {
	if(!self->is_coroutine) {
		return;
	}
	//コルーチンの現在の値
	yield_context* yctx = AtVector(self->native_slot_vec, 0);
	object_markall(yctx->stock_obj);
	object_markall(yctx->source_obj);
	//コルーチンに渡された引数
	for(int i=0; i<yctx->parameter_vec->length; i++) {
		object_markall(AtVector(yctx->parameter_vec, i));
	}
}
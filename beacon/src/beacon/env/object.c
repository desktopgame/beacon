#include "object.h"
#include "namespace.h"
#include "../util/string_buffer.h"
#include <stdlib.h>
#include "vtable.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "type_interface.h"
#include <assert.h>
#include "type_impl.h"
#include "../lib/signal/lang/sg_array.h"
#include "heap.h"
#include "../lib/signal/lang/sg_array.h"
#include "../util/logger.h"
#include "generic_type.h"

//proto
static object* object_malloc(object_tag type);
static object* gObjectTrue = NULL;
static object* gObjectFalse = NULL;
static object* gObjectNull = NULL;
static int gObjectCount = 0;


object * object_int_new(int i) {
	object* ret = object_malloc(object_int);
	ret->u.int_ = i;
	ret->gtype = GEN_INT;
	ret->vptr = type_vtable(CL_INT);
	return ret;
}

object * object_double_new(double d) {
	object* ret = object_malloc(object_double);
	ret->u.double_ = d;
	ret->gtype = GEN_DOUBLE;
	ret->vptr = type_vtable(CL_DOUBLE);
	return ret;
}

object * object_char_new(char c) {
	object* ret = object_malloc(object_char);
	ret->u.char_ = c;
	ret->gtype = GEN_CHAR;
	ret->vptr = type_vtable(CL_CHAR);
	return ret;
}

object * object_string_new(const char * s) {
	object* ret = object_malloc(object_string);
	//ret->u.string_ = s;
	ret->u.field_vec = vector_new();
	ret->gtype = GEN_STRING;
	ret->vptr = type_vtable(CL_STRING);

	//配列を生成
	object* arr = object_ref_new();
	type* arrType = sg_array_class();
	type* strType = namespace_get_type(namespace_lang(), "String");
	arr->gtype = generic_type_make(arrType);
	arr->vptr = type_vtable(arrType);
	//ボックス化
	char* itr = s;
	string_buffer* sb = string_buffer_new();
	while ((*itr) != '\0') {
		char e = (*itr);
		vector_push(arr->native_slot_vec, object_char_new(e));
		itr++;
		string_buffer_append(sb, e);
	}
	string_buffer_shrink(sb);
	//String#charArrayを埋める
	int temp = 0;
	class_find_field(strType->u.class_, "charArray", &temp);
	vector_assign(ret->u.field_vec, temp, arr);
	vector_item* test = vector_at(ret->u.field_vec, temp);
	assert(test != NULL);
	//Array#lengthを埋める
	temp = 0;
	class_find_field(arrType->u.class_, "length", &temp);
	vector_assign(arr->u.field_vec, temp, object_int_new(sb->length));
	//C形式の文字列でも保存
	vector_assign(ret->native_slot_vec, 0, sb);
	return ret;
}

object * object_ref_new() {
	object* ret= object_malloc(object_ref);
	ret->u.field_vec = vector_new();
	return ret;
}

object * object_bool_get(bool b) {
	return (b ? object_get_true() : object_get_false());
}

object * object_get_true() {
	if (gObjectTrue == NULL) {
		gObjectTrue = object_malloc(object_bool);
		gObjectTrue->u.bool_ = !false;
		gObjectTrue->gtype = GEN_BOOL;
	}
	return gObjectTrue;
}

object * object_get_false() {
	if (gObjectFalse == NULL) {
		gObjectFalse = object_malloc(object_bool);
		gObjectFalse->u.bool_ = false;
		gObjectFalse->gtype = GEN_BOOL;
	}
	return gObjectFalse;
}

object * object_get_null() {
	if (gObjectNull == NULL) {
		gObjectNull = object_malloc(object_null);
		gObjectNull->gtype = generic_type_new(CL_NULL);
	}
	return gObjectNull;
}

void object_inc(object * self) {
	if (self->tag == object_int) {
		self->u.int_++;
	} else if (self->tag == object_double) {
		self->u.double_++;
	} else assert(false);
}

void object_dec(object * self) {
	if (self->tag == object_int) {
		self->u.int_--;
	} else if (self->tag == object_double) {
		self->u.double_--;
	} else  assert(false);
}

object* object_copy(object * self) {
	object* ret = NULL;
	if (self->tag == object_int) {
		ret = object_int_new(self->u.int_);
	} else if (self->tag == object_double) {
		ret = object_double_new(self->u.double_);
	} else if (self->tag == object_char) {
		ret = object_char_new(self->u.char_);
	} else {
		ret = self;
	}
	return ret;
}

object * object_copy_s(object * self) {
	assert(self->tag != object_ref);
	return object_copy(self);
}

void object_markall(object * self) {
	//field#static_valueは
	//実際に修飾子が static でないときは NULL
	if (self == NULL) {
		return;
	}
	if (self->paint == paint_marked) {
		return;
	}
	if (self->paint != paint_onexit) {
		self->paint = paint_marked;
	}
	//フィールドを全てマーク
	if (self->tag == object_string ||
		self->tag == object_ref) {
		for (int i = 0; i < self->u.field_vec->length; i++) {
			object* e = (object*)vector_at(self->u.field_vec, i);
			object_markall(e);
		}
	}
	//配列型ならスロットも全てマーク
	type* arrayType = sg_array_class();
	if (self->tag == object_ref &&
		self->gtype->core_type == arrayType) {
		for (int i = 0; i < self->native_slot_vec->length; i++) {
			object* e = (object*)vector_at(self->native_slot_vec, i);
			object_markall(e);
		}
	}
}

int object_count() {
	return gObjectCount;
}

void object_print(object * self) {
	if (self->tag == object_int) {
		text_printf("Int: %d", self->u.int_);
	} else if (self->tag == object_double) {
		text_printf("Double: %d", self->u.double_);
	} else if (self->tag == object_string) {
		string_buffer* sb = (string_buffer*)vector_at(self->native_slot_vec, 0);
		text_printf("String: %s", sb->text);
	} else if (self->tag == object_bool) {
		text_printf("Bool: %s", (self == object_get_true() ? "true" : "false"));
	} else if (self->tag == object_null) {
		text_printf("Ref: Null");
	} else if (self->tag == object_ref) {
		text_printf("Ref: ");
		generic_type_print(self->gtype);
	}
}

void object_delete(object * self) {
	gObjectCount--;
	//sg_info(__FILE__, __LINE__, "deleted object %s", type_name(self->type));
	if (self->tag == object_string) {
		string_buffer* sb = vector_at(self->native_slot_vec, 0);
		vector_remove(self->native_slot_vec, 0);
		string_buffer_delete(sb);
	}
	if (self->tag == object_string ||
		self->tag == object_ref) {
		vector_delete(self->u.field_vec, vector_deleter_null);
	}
	vector_delete(self->native_slot_vec, vector_deleter_null);
	MEM_FREE(self);
}

//private
static object* object_malloc(object_tag type) {
	object* ret = (object*)MEM_MALLOC(sizeof(object));
	ret->gtype = NULL;
	ret->paint = paint_unmarked;
	ret->tag = type;
	ret->vptr = NULL;
	ret->native_slot_vec = vector_new();
	heap_add(heap_get(), ret);
	gObjectCount++;
	return ret;
}
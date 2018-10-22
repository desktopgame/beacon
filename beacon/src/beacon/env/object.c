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
static void DeleteObject_self(VectorItem item);
static void object_mark_coroutine(object* self);
#define object_malloc(type) (object_mallocImpl(type, __FILE__, __LINE__))
//static object* object_malloc(object_tag type);
//static object* gObjectTrue = NULL;
//static object* gObjectFalse = NULL;
//static object* gObjectNull = NULL;
static int gObjectCount = 0;


object * MallocIntObject(int i, const char* filename, int lineno) {
	object* ret = object_mallocImpl(OBJECT_INT_T, filename, lineno);
	ret->u.int_ = i;
	ret->gtype = GENERIC_INT;
	ret->vptr = GetVTableType(TYPE_INT);
	return ret;
}

object* GetIntObject(int i) {
	script_context* ctx = GetCurrentScriptContext();
	CacheScriptContext();
	if((i < -9) || i > 99) {
		return IInternScriptContext(ctx, i);
		//return object_int_new(i);
	}
	if(i < 0) { return (object*)AtVector(ctx->neg_int_vec, (-i) - 1); }
	return (object*)AtVector(ctx->pos_int_vec, i);
}

object * MallocDoubleObject(double d, const char* filename, int lineno) {
	object* ret = object_mallocImpl(OBJECT_DOUBLE_T, filename, lineno);
	ret->u.double_ = d;
	ret->gtype = GENERIC_DOUBLE;
	ret->vptr = GetVTableType(TYPE_DOUBLE);
	return ret;
}

object* MallocLongObject(long l, const char* filename, int lineno) {
	object* ret = object_mallocImpl(OBJECT_LONG_T, filename, lineno);
	ret->u.long_ = l;
	ret->gtype = GENERIC_OBJECT;
	ret->vptr = GetVTableType(TYPE_OBJECT);
	return ret;
}

object * MallocCharObject(char c, const char* filename, int lineno) {
	object* ret = object_mallocImpl(OBJECT_CHAR_T, filename, lineno);
	ret->u.char_ = c;
	ret->gtype = GENERIC_CHAR;
	ret->vptr = GetVTableType(TYPE_CHAR);
	return ret;
}

object * MallocStringObject(const char * s, const char* filename, int lineno) {
	object* ret = object_mallocImpl(OBJECT_STRING_T, filename, lineno);
	//ret->u.string_ = s;
	ret->u.field_vec = NewVector();
	ret->gtype = GENERIC_STRING;
	ret->vptr = GetVTableType(TYPE_STRING);

	//配列を生成
	object* arr = MallocRefObject(filename, lineno);
	//arr->tag = OBJECT_ARRAY_T;
	type* arrType = GetBCArrayType();
	type* strType = FindTypeFromNamespace(GetLangNamespace(), InternString("String"));
	arr->gtype = generic_NewType(arrType);
	arr->vptr = GetVTableType(arrType);
	arr->tag = OBJECT_ARRAY_T;
	AddArgsGenericType(arr->gtype, GENERIC_CHAR);
	//ボックス化
	const char* itr = s;
	Buffer* sb = NewBuffer();
	while ((*itr) != '\0') {
		char e = (*itr);
		PushVector(arr->native_slot_vec, MallocCharObject(e, filename, lineno));
		itr++;
		AppendBuffer(sb, e);
	}
	ShrinkBuffer(sb);
	//String#charArrayを埋める
	int temp = 0;
	FindFieldClass(strType->u.class_, InternString("charArray"), &temp);
	AssignVector(ret->u.field_vec, temp, arr);
	VectorItem* test = AtVector(ret->u.field_vec, temp);
	assert(test != NULL);
	//Array#lengthを埋める
	temp = 0;
	FindFieldClass(arrType->u.class_, InternString("length"), &temp);
	AssignVector(arr->u.field_vec, temp, object_int_new(sb->Length));
	//C形式の文字列でも保存
	AssignVector(ret->native_slot_vec, 0, sb);
	return ret;
}

object * MallocRefObject(const char* filename, int lineno) {
	object* ret= object_mallocImpl(OBJECT_REF_T, filename, lineno);
	ret->u.field_vec = MallocVector(filename, lineno);
	return ret;
}

object * GetBoolObject(bool b) {
	return (b ? GetTrueObject() : GetFalseObject());
}

object * GetTrueObject() {
	script_context* ctx = GetCurrentScriptContext();
	if (ctx->true_obj == NULL) {
		ctx->true_obj = object_malloc(OBJECT_BOOL_T);
		ctx->true_obj->u.bool_ = true;
		ctx->true_obj->gtype = GENERIC_BOOL;
		ctx->true_obj->vptr = TYPE2CLASS(TYPE_BOOL)->vt;
		ctx->true_obj->paint = PAINT_ONEXIT_T;
	}
	return ctx->true_obj;
}

object * GetFalseObject() {
	script_context* ctx = GetCurrentScriptContext();
	if (ctx->false_obj == NULL) {
		ctx->false_obj = object_malloc(OBJECT_BOOL_T);
		ctx->false_obj->u.bool_ = false;
		ctx->false_obj->gtype = GENERIC_BOOL;
		ctx->false_obj->vptr = TYPE2CLASS(TYPE_BOOL)->vt;
		ctx->false_obj->paint = PAINT_ONEXIT_T;
	}
	return ctx->false_obj;
}

object * GetNullObject() {
	script_context* ctx = GetCurrentScriptContext();
	if (ctx->null_obj == NULL) {
		ctx->null_obj = object_malloc(OBJECT_NULL_T);
		ctx->null_obj->gtype = generic_NewType(TYPE_NULL);
		ctx->null_obj->paint = PAINT_ONEXIT_T;
	}
	return ctx->null_obj;
}

void IncObject(object * self) {
	if (self->tag == OBJECT_INT_T) {
		self->u.int_++;
	} else if (self->tag == OBJECT_DOUBLE_T) {
		self->u.double_++;
	} else assert(false);
}

void DecObject(object * self) {
	if (self->tag == OBJECT_INT_T) {
		self->u.int_--;
	} else if (self->tag == OBJECT_DOUBLE_T) {
		self->u.double_--;
	} else  assert(false);
}

object* CopyObject(object * self) {
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

object* CloneObject(object* self) {
	if(self->tag != OBJECT_ARRAY_T &&
	   self->tag != OBJECT_REF_T &&
	   self->tag != OBJECT_STRING_T) {
		   return CopyObject(self);
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

void PaintAllObject(object* self, object_paint paint) {
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
		for (int i = 0; i < self->u.field_vec->Length; i++) {
			object* e = (object*)AtVector(self->u.field_vec, i);
			PaintAllObject(e, paint);
		}
	}
	//配列型ならスロットも全てマーク
	type* arrayType = GetBCArrayType();
	if (self->gtype->core_type == arrayType) {
		for (int i = 0; i < self->native_slot_vec->Length; i++) {
			object* e = (object*)AtVector(self->native_slot_vec, i);
			PaintAllObject(e, paint);
		}
	}
	//コルーチンならその中身をマークする
	object_mark_coroutine(self);
}

void MarkAllObject(object * self) {
	PaintAllObject(self, PAINT_MARKED_T);
}

int CountActiveObject() {
	return gObjectCount;
}

void PrintObject(object * self) {
	if (self->tag == OBJECT_INT_T) {
		printf("Int: %d", self->u.int_);
	} else if (self->tag == OBJECT_DOUBLE_T) {
		printf("Double: %lf", self->u.double_);
	} else if (self->tag == OBJECT_STRING_T) {
		Buffer* sb = (Buffer*)AtVector(self->native_slot_vec, 0);
		printf("String: %s", sb->Text);
	} else if (self->tag == OBJECT_BOOL_T) {
		printf("Bool: %s", (self == GetTrueObject() ? "true" : "false"));
	} else if (self->tag == OBJECT_NULL_T) {
		printf("Ref: Null");
	} else if (self->tag == OBJECT_REF_T) {
		printf("Ref: ");
		PrintGenericType(self->gtype);
	}
}

void DeleteObject(object * self) {
	gObjectCount--;
	if(self->is_clone) {
		MEM_FREE(self);
		return;
	}
	if(self->is_coroutine) {
		YieldContext* yctx = AtVector(self->native_slot_vec, 0);
		RemoveVector(self->native_slot_vec, 0);
		DeleteYieldContext(yctx);
	}
	if (self->tag == OBJECT_STRING_T) {
		Buffer* sb = AtVector(self->native_slot_vec, 0);
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

void DestroyObject(object* self) {
	if (self == NULL) {
		return;
	}
	type* tp = self->gtype->core_type;
	assert(self->paint == PAINT_ONEXIT_T);
	if (self->tag == OBJECT_REF_T ||
	   self->tag == OBJECT_STRING_T ||
		self->tag == OBJECT_ARRAY_T) {
		DeleteVector(self->u.field_vec, DeleteObject_self);
		self->u.field_vec = NULL;
	}
	//String#charArray
	if (self->tag == OBJECT_ARRAY_T) {
		DeleteVector(self->u.field_vec, DeleteObject_self);
		DeleteVector(self->native_slot_vec, DeleteObject_self);
		self->native_slot_vec = NULL;
		self->u.field_vec = NULL;
	}
	//Printfln("delete object %s", GetTypeName(obj->type));
	DeleteObject(self);
}

int ObjectToInt(object* self) {
	assert(self->tag == OBJECT_INT_T);
	return self->u.int_;
}

double ObjectToDouble(object* self) {
	assert(self->tag == OBJECT_DOUBLE_T);
	return self->u.double_;
}

bool ObjectToBool(object* self) {
	assert(self->tag == OBJECT_BOOL_T);
	return self->u.bool_;
}

char ObjectToChar(object* self) {
	assert(self->tag == OBJECT_CHAR_T);
	return self->u.char_;
}

long ObjectToLong(object* self) {
	assert(self->tag == OBJECT_LONG_T);
	return self->u.long_;
}

object* IntToObject(int i) {
	return object_int_new(i);
}

object* DoubleToObject(double d) {
	return object_double_new(d);
}

object* BoolToObject(bool b) {
	return GetBoolObject(b);
}

object* CharToObject(char c) {
	return object_char_new(c);
}

object* LongToObject(long l) {
	return object_long_new(l);
}

object* GetDefaultObject(generic_type* gt) {
	object* a = GetNullObject();
	if (gt->core_type == TYPE_INT) {
		a = GetIntObject(0);
	} else if (gt->core_type == TYPE_DOUBLE) {
		a = object_double_new(0.0);
	} else if (gt->core_type == TYPE_BOOL) {
		a = GetBoolObject(false);
	} else if (gt->core_type == TYPE_CHAR) {
		a = object_char_new('\0');
	}
	return a;
}

const char* GetObjectName(object* self) {
	const char* name = "NULL";
	if(self->gtype != NULL && self->gtype->core_type != NULL) {
		name = Ref2Str(GetTypeFullName(self->gtype->core_type));
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

static void DeleteObject_self(VectorItem item) {
	object* e = (object*)item;
	DestroyObject(e);
}

static void object_mark_coroutine(object* self) {
	if(!self->is_coroutine) {
		return;
	}
	//コルーチンの現在の値
	YieldContext* yctx = AtVector(self->native_slot_vec, 0);
	MarkAllObject(yctx->Stock);
	MarkAllObject(yctx->Source);
	//コルーチンに渡された引数
	for(int i=0; i<yctx->Parameters->Length; i++) {
		MarkAllObject(AtVector(yctx->Parameters, i));
	}
}
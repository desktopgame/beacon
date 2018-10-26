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
static Object* Object_mallocImpl(ObjectTag type, const char* filename, int lineno);
static void DeleteObject_self(VectorItem item);
static void Object_mark_coroutine(Object* self);
#define Object_malloc(type) (Object_mallocImpl(type, __FILE__, __LINE__))
//static Object* Object_malloc(ObjectTag type);
//static Object* gObjectTrue = NULL;
//static Object* gObjectFalse = NULL;
//static Object* gObjectNull = NULL;
static int gObjectCount = 0;


Object * MallocIntObject(int i, const char* filename, int lineno) {
	Object* ret = Object_mallocImpl(OBJECT_INT_T, filename, lineno);
	ret->u.int_ = i;
	ret->gtype = GENERIC_INT;
	ret->vptr = GetVTableType(TYPE_INT);
	return ret;
}

Object* GetIntObject(int i) {
	ScriptContext* ctx = GetCurrentScriptContext();
	CacheScriptContext();
	if((i < -9) || i > 99) {
		return IInternScriptContext(ctx, i);
		//return Object_int_new(i);
	}
	if(i < 0) { return (Object*)AtVector(ctx->NegativeIntegerCacheList, (-i) - 1); }
	return (Object*)AtVector(ctx->PositiveIntegerCacheList, i);
}

Object * MallocDoubleObject(double d, const char* filename, int lineno) {
	Object* ret = Object_mallocImpl(OBJECT_DOUBLE_T, filename, lineno);
	ret->u.double_ = d;
	ret->gtype = GENERIC_DOUBLE;
	ret->vptr = GetVTableType(TYPE_DOUBLE);
	return ret;
}

Object* MallocLongObject(long l, const char* filename, int lineno) {
	Object* ret = Object_mallocImpl(OBJECT_LONG_T, filename, lineno);
	ret->u.long_ = l;
	ret->gtype = GENERIC_OBJECT;
	ret->vptr = GetVTableType(TYPE_OBJECT);
	return ret;
}

Object * MallocCharObject(char c, const char* filename, int lineno) {
	Object* ret = Object_mallocImpl(OBJECT_CHAR_T, filename, lineno);
	ret->u.char_ = c;
	ret->gtype = GENERIC_CHAR;
	ret->vptr = GetVTableType(TYPE_CHAR);
	return ret;
}

Object * MallocStringObject(const char * s, const char* filename, int lineno) {
	Object* ret = Object_mallocImpl(OBJECT_STRING_T, filename, lineno);
	//ret->u.string_ = s;
	ret->u.field_vec = NewVector();
	ret->gtype = GENERIC_STRING;
	ret->vptr = GetVTableType(TYPE_STRING);

	//配列を生成
	Object* arr = MallocRefObject(filename, lineno);
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
	AssignVector(arr->u.field_vec, temp, Object_int_new(sb->Length));
	//C形式の文字列でも保存
	AssignVector(ret->native_slot_vec, 0, sb);
	return ret;
}

Object * MallocRefObject(const char* filename, int lineno) {
	Object* ret= Object_mallocImpl(OBJECT_REF_T, filename, lineno);
	ret->u.field_vec = MallocVector(filename, lineno);
	return ret;
}

Object * GetBoolObject(bool b) {
	return (b ? GetTrueObject() : GetFalseObject());
}

Object * GetTrueObject() {
	ScriptContext* ctx = GetCurrentScriptContext();
	if (ctx->True == NULL) {
		ctx->True = Object_malloc(OBJECT_BOOL_T);
		ctx->True->u.bool_ = true;
		ctx->True->gtype = GENERIC_BOOL;
		ctx->True->vptr = TYPE2CLASS(TYPE_BOOL)->vt;
		ctx->True->paint = PAINT_ONEXIT_T;
	}
	return ctx->True;
}

Object * GetFalseObject() {
	ScriptContext* ctx = GetCurrentScriptContext();
	if (ctx->False == NULL) {
		ctx->False = Object_malloc(OBJECT_BOOL_T);
		ctx->False->u.bool_ = false;
		ctx->False->gtype = GENERIC_BOOL;
		ctx->False->vptr = TYPE2CLASS(TYPE_BOOL)->vt;
		ctx->False->paint = PAINT_ONEXIT_T;
	}
	return ctx->False;
}

Object * GetNullObject() {
	ScriptContext* ctx = GetCurrentScriptContext();
	if (ctx->Null == NULL) {
		ctx->Null = Object_malloc(OBJECT_NULL_T);
		ctx->Null->gtype = generic_NewType(TYPE_NULL);
		ctx->Null->paint = PAINT_ONEXIT_T;
	}
	return ctx->Null;
}

void IncObject(Object * self) {
	if (self->tag == OBJECT_INT_T) {
		self->u.int_++;
	} else if (self->tag == OBJECT_DOUBLE_T) {
		self->u.double_++;
	} else assert(false);
}

void DecObject(Object * self) {
	if (self->tag == OBJECT_INT_T) {
		self->u.int_--;
	} else if (self->tag == OBJECT_DOUBLE_T) {
		self->u.double_--;
	} else  assert(false);
}

Object* CopyObject(Object * self) {
	/*
	Object* ret = NULL;
	if (self->tag == OBJECT_INT_T) {
		ret = Object_int_new(self->u.int_);
	} else if (self->tag == OBJECT_DOUBLE_T) {
		ret = Object_double_new(self->u.double_);
	} else if (self->tag == OBJECT_CHAR_T) {
		ret = Object_char_new(self->u.char_);
	} else {
		ret = self;
	}
	return ret;
	*/
	return self;
}

Object* CloneObject(Object* self) {
	if(self->tag != OBJECT_ARRAY_T &&
	   self->tag != OBJECT_REF_T &&
	   self->tag != OBJECT_STRING_T) {
		   return CopyObject(self);
	}
	Object* ret = NULL;
	if(self->tag == OBJECT_REF_T ||
	   self->tag == OBJECT_ARRAY_T ||
	   self->tag == OBJECT_STRING_T) {
		ret = Object_mallocImpl(OBJECT_INT_T, __FILE__, __LINE__);
		ret->tag = self->tag;
		ret->gtype = self->gtype;
		ret->vptr = self->vptr;
		ret->native_slot_vec  = self->native_slot_vec;
		ret->u.field_vec = self->u.field_vec;
	}
	ret->is_clone = true;
	return ret;
}

void PaintAllObject(Object* self, ObjectPaint paint) {
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
			Object* e = (Object*)AtVector(self->u.field_vec, i);
			PaintAllObject(e, paint);
		}
	}
	//配列型ならスロットも全てマーク
	type* arrayType = GetBCArrayType();
	if (self->gtype->core_type == arrayType) {
		for (int i = 0; i < self->native_slot_vec->Length; i++) {
			Object* e = (Object*)AtVector(self->native_slot_vec, i);
			PaintAllObject(e, paint);
		}
	}
	//コルーチンならその中身をマークする
	Object_mark_coroutine(self);
}

void MarkAllObject(Object * self) {
	PaintAllObject(self, PAINT_MARKED_T);
}

int CountActiveObject() {
	return gObjectCount;
}

void PrintObject(Object * self) {
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

void DeleteObject(Object * self) {
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

void DestroyObject(Object* self) {
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
	//Printfln("delete Object %s", GetTypeName(obj->type));
	DeleteObject(self);
}

int ObjectToInt(Object* self) {
	assert(self->tag == OBJECT_INT_T);
	return self->u.int_;
}

double ObjectToDouble(Object* self) {
	assert(self->tag == OBJECT_DOUBLE_T);
	return self->u.double_;
}

bool ObjectToBool(Object* self) {
	assert(self->tag == OBJECT_BOOL_T);
	return self->u.bool_;
}

char ObjectToChar(Object* self) {
	assert(self->tag == OBJECT_CHAR_T);
	return self->u.char_;
}

long ObjectToLong(Object* self) {
	assert(self->tag == OBJECT_LONG_T);
	return self->u.long_;
}

Object* IntToObject(int i) {
	return Object_int_new(i);
}

Object* DoubleToObject(double d) {
	return Object_double_new(d);
}

Object* BoolToObject(bool b) {
	return GetBoolObject(b);
}

Object* CharToObject(char c) {
	return Object_char_new(c);
}

Object* LongToObject(long l) {
	return Object_long_new(l);
}

Object* GetDefaultObject(generic_type* gt) {
	Object* a = GetNullObject();
	if (gt->core_type == TYPE_INT) {
		a = GetIntObject(0);
	} else if (gt->core_type == TYPE_DOUBLE) {
		a = Object_double_new(0.0);
	} else if (gt->core_type == TYPE_BOOL) {
		a = GetBoolObject(false);
	} else if (gt->core_type == TYPE_CHAR) {
		a = Object_char_new('\0');
	}
	return a;
}

const char* GetObjectName(Object* self) {
	const char* name = "NULL";
	if(self->gtype != NULL && self->gtype->core_type != NULL) {
		name = Ref2Str(GetTypeFullName(self->gtype->core_type));
	}
	return name;
}

//private
static Object* Object_mallocImpl(ObjectTag type, const char* filename, int lineno) {
	Object* ret = (Object*)mem_malloc(sizeof(Object), filename, lineno);
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
	Object* e = (Object*)item;
	DestroyObject(e);
}

static void Object_mark_coroutine(Object* self) {
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
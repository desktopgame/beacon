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
	ret->GType = GENERIC_INT;
	ret->VPtr = GetVTableType(TYPE_INT);
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
	ret->GType = GENERIC_DOUBLE;
	ret->VPtr = GetVTableType(TYPE_DOUBLE);
	return ret;
}

Object* MallocLongObject(long l, const char* filename, int lineno) {
	Object* ret = Object_mallocImpl(OBJECT_LONG_T, filename, lineno);
	ret->u.long_ = l;
	ret->GType = GENERIC_OBJECT;
	ret->VPtr = GetVTableType(TYPE_OBJECT);
	return ret;
}

Object * MallocCharObject(char c, const char* filename, int lineno) {
	Object* ret = Object_mallocImpl(OBJECT_CHAR_T, filename, lineno);
	ret->u.char_ = c;
	ret->GType = GENERIC_CHAR;
	ret->VPtr = GetVTableType(TYPE_CHAR);
	return ret;
}

Object * MallocStringObject(const char * s, const char* filename, int lineno) {
	Object* ret = Object_mallocImpl(OBJECT_STRING_T, filename, lineno);
	//ret->u.string_ = s;
	ret->u.field_vec = NewVector();
	ret->GType = GENERIC_STRING;
	ret->VPtr = GetVTableType(TYPE_STRING);

	//配列を生成
	Object* arr = MallocRefObject(filename, lineno);
	//arr->Tag = OBJECT_ARRAY_T;
	Type* arrType = GetBCArrayType();
	Type* strType = FindTypeFromNamespace(GetLangNamespace(), InternString("String"));
	arr->GType = NewGenericType(arrType);
	arr->VPtr = GetVTableType(arrType);
	arr->Tag = OBJECT_ARRAY_T;
	AddArgsGenericType(arr->GType, GENERIC_CHAR);
	//ボックス化
	const char* itr = s;
	Buffer* sb = NewBuffer();
	while ((*itr) != '\0') {
		char e = (*itr);
		PushVector(arr->NativeSlotVec, MallocCharObject(e, filename, lineno));
		itr++;
		AppendBuffer(sb, e);
	}
	ShrinkBuffer(sb);
	//String#charArrayを埋める
	int temp = 0;
	FindFieldClass(strType->Kind.Class, InternString("charArray"), &temp);
	AssignVector(ret->u.field_vec, temp, arr);
	VectorItem* test = AtVector(ret->u.field_vec, temp);
	assert(test != NULL);
	//Array#lengthを埋める
	temp = 0;
	FindFieldClass(arrType->Kind.Class, InternString("length"), &temp);
	AssignVector(arr->u.field_vec, temp, Object_int_new(sb->Length));
	//C形式の文字列でも保存
	AssignVector(ret->NativeSlotVec, 0, sb);
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
		ctx->True->GType = GENERIC_BOOL;
		ctx->True->VPtr = TYPE2CLASS(TYPE_BOOL)->VT;
		ctx->True->Paint = PAINT_ONEXIT_T;
	}
	return ctx->True;
}

Object * GetFalseObject() {
	ScriptContext* ctx = GetCurrentScriptContext();
	if (ctx->False == NULL) {
		ctx->False = Object_malloc(OBJECT_BOOL_T);
		ctx->False->u.bool_ = false;
		ctx->False->GType = GENERIC_BOOL;
		ctx->False->VPtr = TYPE2CLASS(TYPE_BOOL)->VT;
		ctx->False->Paint = PAINT_ONEXIT_T;
	}
	return ctx->False;
}

Object * GetNullObject() {
	ScriptContext* ctx = GetCurrentScriptContext();
	if (ctx->Null == NULL) {
		ctx->Null = Object_malloc(OBJECT_NULL_T);
		ctx->Null->GType = NewGenericType(TYPE_NULL);
		ctx->Null->Paint = PAINT_ONEXIT_T;
	}
	return ctx->Null;
}

void IncObject(Object * self) {
	if (self->Tag == OBJECT_INT_T) {
		self->u.int_++;
	} else if (self->Tag == OBJECT_DOUBLE_T) {
		self->u.double_++;
	} else assert(false);
}

void DecObject(Object * self) {
	if (self->Tag == OBJECT_INT_T) {
		self->u.int_--;
	} else if (self->Tag == OBJECT_DOUBLE_T) {
		self->u.double_--;
	} else  assert(false);
}

Object* CopyObject(Object * self) {
	/*
	Object* ret = NULL;
	if (self->Tag == OBJECT_INT_T) {
		ret = Object_int_new(self->u.int_);
	} else if (self->Tag == OBJECT_DOUBLE_T) {
		ret = Object_double_new(self->u.double_);
	} else if (self->Tag == OBJECT_CHAR_T) {
		ret = Object_char_new(self->u.char_);
	} else {
		ret = self;
	}
	return ret;
	*/
	return self;
}

Object* CloneObject(Object* self) {
	if(self->Tag != OBJECT_ARRAY_T &&
	   self->Tag != OBJECT_REF_T &&
	   self->Tag != OBJECT_STRING_T) {
		   return CopyObject(self);
	}
	Object* ret = NULL;
	if(self->Tag == OBJECT_REF_T ||
	   self->Tag == OBJECT_ARRAY_T ||
	   self->Tag == OBJECT_STRING_T) {
		ret = Object_mallocImpl(OBJECT_INT_T, __FILE__, __LINE__);
		ret->Tag = self->Tag;
		ret->GType = self->GType;
		ret->VPtr = self->VPtr;
		ret->NativeSlotVec  = self->NativeSlotVec;
		ret->u.field_vec = self->u.field_vec;
	}
	ret->IsClone = true;
	return ret;
}

void PaintAllObject(Object* self, ObjectPaint paint) {
	//field#static_valueは
	//実際に修飾子が static でないときは NULL
	if (self == NULL) {
		return;
	}
	if (self->Paint == paint) {
		return;
	}
	if (self->Paint != PAINT_ONEXIT_T) {
		self->Paint = paint;
	}
	//フィールドを全てマーク
	if (self->Tag == OBJECT_STRING_T ||
		self->Tag == OBJECT_REF_T ||
		self->Tag == OBJECT_ARRAY_T) {
		for (int i = 0; i < self->u.field_vec->Length; i++) {
			Object* e = (Object*)AtVector(self->u.field_vec, i);
			PaintAllObject(e, paint);
		}
	}
	//配列型ならスロットも全てマーク
	Type* arrayType = GetBCArrayType();
	if (self->GType->CoreType == arrayType) {
		for (int i = 0; i < self->NativeSlotVec->Length; i++) {
			Object* e = (Object*)AtVector(self->NativeSlotVec, i);
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
	if (self->Tag == OBJECT_INT_T) {
		printf("Int: %d", self->u.int_);
	} else if (self->Tag == OBJECT_DOUBLE_T) {
		printf("Double: %lf", self->u.double_);
	} else if (self->Tag == OBJECT_STRING_T) {
		Buffer* sb = (Buffer*)AtVector(self->NativeSlotVec, 0);
		printf("String: %s", sb->Text);
	} else if (self->Tag == OBJECT_BOOL_T) {
		printf("Bool: %s", (self == GetTrueObject() ? "true" : "false"));
	} else if (self->Tag == OBJECT_NULL_T) {
		printf("Ref: Null");
	} else if (self->Tag == OBJECT_REF_T) {
		printf("Ref: ");
		PrintGenericType(self->GType);
	}
}

void DeleteObject(Object * self) {
	gObjectCount--;
	if(self->IsClone) {
		MEM_FREE(self);
		return;
	}
	if(self->IsCoroutine) {
		YieldContext* yctx = AtVector(self->NativeSlotVec, 0);
		RemoveVector(self->NativeSlotVec, 0);
		DeleteYieldContext(yctx);
	}
	if (self->Tag == OBJECT_STRING_T) {
		Buffer* sb = AtVector(self->NativeSlotVec, 0);
		RemoveVector(self->NativeSlotVec, 0);
		DeleteBuffer(sb);
	}
	if (self->Tag == OBJECT_STRING_T ||
		self->Tag == OBJECT_REF_T ||
		self->Tag == OBJECT_ARRAY_T) {
		DeleteVector(self->u.field_vec, VectorDeleterOfNull);
	}
	DeleteVector(self->NativeSlotVec, VectorDeleterOfNull);
	MEM_FREE(self);
}

void DestroyObject(Object* self) {
	if (self == NULL) {
		return;
	}
	Type* tp = self->GType->CoreType;
	assert(self->Paint == PAINT_ONEXIT_T);
	if (self->Tag == OBJECT_REF_T ||
	   self->Tag == OBJECT_STRING_T ||
		self->Tag == OBJECT_ARRAY_T) {
		DeleteVector(self->u.field_vec, DeleteObject_self);
		self->u.field_vec = NULL;
	}
	//String#charArray
	if (self->Tag == OBJECT_ARRAY_T) {
		DeleteVector(self->u.field_vec, DeleteObject_self);
		DeleteVector(self->NativeSlotVec, DeleteObject_self);
		self->NativeSlotVec = NULL;
		self->u.field_vec = NULL;
	}
	//Printfln("delete Object %s", GetTypeName(obj->type));
	DeleteObject(self);
}

int ObjectToInt(Object* self) {
	assert(self->Tag == OBJECT_INT_T);
	return self->u.int_;
}

double ObjectToDouble(Object* self) {
	assert(self->Tag == OBJECT_DOUBLE_T);
	return self->u.double_;
}

bool ObjectToBool(Object* self) {
	assert(self->Tag == OBJECT_BOOL_T);
	return self->u.bool_;
}

char ObjectToChar(Object* self) {
	assert(self->Tag == OBJECT_CHAR_T);
	return self->u.char_;
}

long ObjectToLong(Object* self) {
	assert(self->Tag == OBJECT_LONG_T);
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

Object* GetDefaultObject(GenericType* gt) {
	Object* a = GetNullObject();
	if (gt->CoreType == TYPE_INT) {
		a = GetIntObject(0);
	} else if (gt->CoreType == TYPE_DOUBLE) {
		a = Object_double_new(0.0);
	} else if (gt->CoreType == TYPE_BOOL) {
		a = GetBoolObject(false);
	} else if (gt->CoreType == TYPE_CHAR) {
		a = Object_char_new('\0');
	}
	return a;
}

const char* GetObjectName(Object* self) {
	const char* name = "NULL";
	if(self->GType != NULL && self->GType->CoreType != NULL) {
		name = Ref2Str(GetTypeFullName(self->GType->CoreType));
	}
	return name;
}

//private
static Object* Object_mallocImpl(ObjectTag type, const char* filename, int lineno) {
	Object* ret = (Object*)mem_malloc(sizeof(Object), filename, lineno);
	ret->IsCoroutine = false;
	ret->GType = NULL;
	ret->Paint = PAINT_UNMARKED_T;
	ret->Tag = type;
	ret->VPtr = NULL;
	ret->IsClone = false;
	if (type == OBJECT_STRING_T ||
		type == OBJECT_ARRAY_T ||
		type == OBJECT_REF_T) {
		ret->NativeSlotVec = MallocVector(filename, lineno);
	} else {
		ret->NativeSlotVec = NULL;
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
	if(!self->IsCoroutine) {
		return;
	}
	//コルーチンの現在の値
	YieldContext* yctx = AtVector(self->NativeSlotVec, 0);
	MarkAllObject(yctx->Stock);
	MarkAllObject(yctx->Source);
	//コルーチンに渡された引数
	for(int i=0; i<yctx->Parameters->Length; i++) {
		MarkAllObject(AtVector(yctx->Parameters, i));
	}
}
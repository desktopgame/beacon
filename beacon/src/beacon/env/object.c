#include "object.h"
#include "namespace.h"
#include "../util/string_buffer.h"
#include <stdlib.h>
#include <string.h>
#include "vtable.h"
#include "generic_type.h"
#include "type_interface.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "type_interface.h"
#include "script_context.h"
#include <assert.h>
#include "TYPE_IMPL.h"
#include "heap.h"
#include "generic_type.h"
#include "../vm/yield_context.h"
#include "coroutine.h"
#include "../lib/bc_library_interface.h"

//proto
static void delete_self(VectorItem item);
static void mark_coroutine(Object* self);
//static Object* Object_malloc(ObjectTag type);
//static Object* gObjectTrue = NULL;
//static Object* gObjectFalse = NULL;
//static Object* gObjectNull = NULL;
static int gObjectCount = 0;

void* HandleObjectMessage(Object* self, ObjectMessage msg, int argc, ObjectMessageArgument argv[]) {
	#if DEBUG
	assert(self->GType != NULL);
	const char* name = Ref2Str(GetTypeName(self->GType->CoreType));
	#endif
	switch(msg) {
		case OBJECT_MSG_NONE:
			break;
		case OBJECT_MSG_PRINT:
			printf("%p", self);
			break;
		case OBJECT_MSG_DELETE:
			DeleteVector(self->Fields, VectorDeleterOfNull);
			MEM_FREE(self);
			break;
		case OBJECT_MSG_DESTROY:
			DeleteVector(self->Fields, delete_self);
			self->Fields = NULL;
			DeleteObject(self);
			break;
		case OBJECT_MSG_MARKALL:
		{
			assert(argc == 1);
			ObjectPaint paint = argv[0].Int;
			for (int i = 0; i < self->Fields->Length; i++) {
				Object* e = (Object*)AtVector(self->Fields, i);
				PaintAllObject(e, paint);
			}
			break;
		}
		case OBJECT_MSG_CLONE:
		{
			/*
			if(self->Tag != OBJECT_ARRAY_T &&
				self->Tag != OBJECT_REF_T &&
	   			self->Tag != OBJECT_STRING_T) {
		   		return CopyObject(self);
			}
			*/
			Object* ret = NewObject(sizeof(Object));
			ret->GType = self->GType;
			ret->VPtr = self->VPtr;
			//ret->NativeSlotVec  = self->NativeSlotVec;
			ret->Fields = self->Fields;
			//ret->u.field_vec = self->u.field_vec;
			ret->Flags = ret->Flags | OBJECT_FLG_CLONE;
			return ret;
		}
	}
	return NULL;
}

void* NewObject(size_t object_size) {
	if(object_size < sizeof(Object)) {
		return NULL;
	}
	void* mem = MEM_MALLOC(object_size);
	memset(mem, 0, object_size);
	Object* ret = mem;
	ret->OnMessage = HandleObjectMessage;
	//ret->NativeSlotVec = NULL;
	ret->GType = GENERIC_NULL;
	ret->Paint = PAINT_UNMARKED_T;
	ret->VPtr = GENERIC_NULL->CoreType->Kind.Class->VT;
	ret->Fields = NewVector();
	ret->Flags = OBJECT_FLG_NONE;
	AddHeap(GetHeap(), ret);
	gObjectCount++;
	return mem;
}

void* ConstructObject(size_t object_size, GenericType* gtype) {
	assert(gtype != NULL);
	void* mem = NewObject(object_size);
	Object* obj = mem;
	obj->GType = gtype;
	obj->VPtr = GetVTableType(gtype->CoreType);
	return mem;
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

Object * GetBoolObject(bool b) {
	return (b ? GetTrueObject() : GetFalseObject());
}

Object * GetTrueObject() {
	ScriptContext* ctx = GetCurrentScriptContext();
	if (ctx->True == NULL) {
		ctx->True = (Object*)NewBool(true);
		ctx->True->Paint = PAINT_ONEXIT_T;
	}
	return ctx->True;
}

Object * GetFalseObject() {
	ScriptContext* ctx = GetCurrentScriptContext();
	if (ctx->False == NULL) {
		ctx->False = (Object*)NewBool(false);
		ctx->False->Paint = PAINT_ONEXIT_T;
	}
	return ctx->False;
}

Object * GetNullObject() {
	ScriptContext* ctx = GetCurrentScriptContext();
	if (ctx->Null == NULL) {
		ctx->Null = NewObject(sizeof(Object));
		ctx->Null->GType = NewGenericType(TYPE_NULL);
		ctx->Null->VPtr = GetVTableType(TYPE_NULL);
		ctx->Null->Paint = PAINT_ONEXIT_T;
	}
	return ctx->Null;
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
	void* ret = self->OnMessage(self, OBJECT_MSG_CLONE, 0, NULL);
	assert(ret != NULL);
	return (Object*)ret;
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
	#if DEBUG
	//printf("%s\n", Ref2Str(GetTypeName(self->GType->CoreType)));
	#endif
	assert(self->OnMessage != NULL);
	ObjectMessageArgument argv[] = {paint};
	self->OnMessage(self, OBJECT_MSG_MARKALL, 1, argv);
	//コルーチンならその中身をマークする
	mark_coroutine(self);
}

void MarkAllObject(Object * self) {
	PaintAllObject(self, PAINT_MARKED_T);
}

int CountActiveObject() {
	return gObjectCount;
}

void PrintObject(Object * self) {
	self->OnMessage(self, OBJECT_MSG_PRINT, 0, NULL);
	/*
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
	*/
}

void DeleteObject(Object * self) {
	gObjectCount--;
	if((self->Flags & OBJECT_FLG_CLONE) > 0) {
		MEM_FREE(self);
		return;
	}
	if((self->Flags & OBJECT_FLG_COROUTINE) > 0) {
		Coroutine* cor = (Coroutine*)self;
		YieldContext* yctx = cor->Context;
		DeleteYieldContext(yctx);
		cor->Context = NULL;
	}
	self->OnMessage(self, OBJECT_MSG_DELETE, 0, NULL);
}

void DestroyObject(Object* self) {
	if (self == NULL) {
		return;
	}
	assert(self->Paint == PAINT_ONEXIT_T);
	self->OnMessage(self, OBJECT_MSG_DESTROY, 0, NULL);
}

int ObjectToInt(Object* self) {
	assert(IsIntValue(self));
	return ((Integer*)self)->Value;
}

double ObjectToDouble(Object* self) {
	assert(IsDoubleValue(self));
	return ((Double*)self)->Value;
}

bool ObjectToBool(Object* self) {
	assert(IsBoolValue(self));
	return ((Bool*)self)->Value;
}

char ObjectToChar(Object* self) {
	assert(IsCharValue(self));
	return ((Char*)self)->Value;
}

long ObjectToLong(Object* self) {
	//assert(self->Tag == OBJECT_LONG_T);
	return ((Long*)self)->Value;
}

Object* IntToObject(int i) {
	return (Object*)NewInteger(i);
}

Object* DoubleToObject(double d) {
	return (Object*)NewDouble(d);
}

Object* BoolToObject(bool b) {
	return GetBoolObject(b);
}

Object* CharToObject(char c) {
	return (Object*)NewChar(c);
}

Object* LongToObject(long l) {
	return (Object*)NewLong(l);
}

Object* GetDefaultObject(GenericType* gt) {
	Object* a = GetNullObject();
	if (gt->CoreType == TYPE_INT) {
		a = GetIntObject(0);
	} else if (gt->CoreType == TYPE_DOUBLE) {
		a = (Object*)NewDouble(0.0);
	} else if (gt->CoreType == TYPE_BOOL) {
		a = GetBoolObject(false);
	} else if (gt->CoreType == TYPE_CHAR) {
		a = (Object*)NewChar('\0');
	}
	assert(a->GType != NULL);
	return a;
}

bool IsCharValue(Object* self) {
	return self->GType->CoreType == TYPE_CHAR;
}

bool IsBoolValue(Object* self) {
	return self->GType->CoreType == TYPE_BOOL;
}

bool IsIntValue(Object* self) {
	return self->GType->CoreType == TYPE_INT;
}

bool IsDoubleValue(Object* self) {
	return self->GType->CoreType == TYPE_DOUBLE;
}

bool IsStringValue(Object* self) {
	return self->GType->CoreType == TYPE_STRING;
}

bool IsNullValue(Object* self) {
	return self->GType->CoreType == TYPE_NULL;
}

const char* GetObjectName(Object* self) {
	const char* name = "NULL";
	if(self->GType != NULL && self->GType->CoreType != NULL) {
		name = Ref2Str(GetTypeFullName(self->GType->CoreType));
	}
	return name;
}

//private
static void delete_self(VectorItem item) {
	Object* e = (Object*)item;
	DestroyObject(e);
}

static void mark_coroutine(Object* self) {
	if(!((self->Flags & OBJECT_FLG_COROUTINE) > 0)) {
		return;
	}
	//コルーチンの現在の値
	Coroutine* cor = (Coroutine*)self;
	YieldContext* yctx = cor->Context;
	MarkAllObject(yctx->Stock);
	MarkAllObject(yctx->Source);
	//コルーチンに渡された引数
	for(int i=0; i<yctx->Parameters->Length; i++) {
		MarkAllObject(AtVector(yctx->Parameters, i));
	}
}
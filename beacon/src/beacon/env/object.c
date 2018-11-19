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
static void mark_coroutine(bc_Object* self);
//static Object* Object_malloc(ObjectTag type);
//static Object* gObjectTrue = NULL;
//static Object* gObjectFalse = NULL;
//static Object* gObjectNull = NULL;
static int gObjectCount = 0;

void* bc_HandleObjectMessage(bc_Object* self, bc_ObjectMessage msg, int argc, bc_ObjectMessageArgument argv[]) {
	#if DEBUG
	assert(self->GType != NULL);
	const char* name = Ref2Str(bc_GetTypeName(self->GType->CoreType));
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
			bc_DeleteObject(self);
			break;
		case OBJECT_MSG_MARKALL:
		{
			assert(argc == 1);
			bc_ObjectPaint paint = argv[0].Int;
			for (int i = 0; i < self->Fields->Length; i++) {
				bc_Object* e = (bc_Object*)AtVector(self->Fields, i);
				bc_PaintAllObject(e, paint);
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
			bc_Object* ret = bc_NewObject(sizeof(bc_Object));
			DeleteVector(ret->Fields, VectorDeleterOfNull);
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

void* bc_NewObject(size_t object_size) {
	if(object_size < sizeof(bc_Object)) {
		return NULL;
	}
	void* mem = MEM_MALLOC(object_size);
	memset(mem, 0, object_size);
	bc_Object* ret = mem;
	ret->OnMessage = bc_HandleObjectMessage;
	//ret->NativeSlotVec = NULL;
	ret->GType = BC_GENERIC_NULL;
	ret->Paint = PAINT_UNMARKED_T;
	ret->VPtr = BC_GENERIC_NULL->CoreType->Kind.Class->VT;
	ret->Fields = NewVector();
	ret->Flags = OBJECT_FLG_NONE;
	bc_AddHeap(bc_GetHeap(), ret);
	gObjectCount++;
	return mem;
}

void* bc_ConstructObject(size_t object_size, bc_GenericType* gtype) {
	assert(gtype != NULL);
	void* mem = bc_NewObject(object_size);
	bc_Object* obj = mem;
	obj->GType = gtype;
	obj->VPtr = bc_GetVTableType(gtype->CoreType);
	return mem;
}

bc_Object* bc_GetIntObject(int i) {
	bc_ScriptContext* ctx = bc_GetCurrentScriptContext();
	bc_CacheScriptContext();
	if((i < -9) || i > 99) {
		return bc_IInternScriptContext(ctx, i);
		//return Object_int_new(i);
	}
	if(i < 0) { return (bc_Object*)AtVector(ctx->NegativeIntegerCacheList, (-i) - 1); }
	return (bc_Object*)AtVector(ctx->PositiveIntegerCacheList, i);
}

bc_Object * bc_GetBoolObject(bool b) {
	return (b ? bc_GetTrueObject() : bc_GetFalseObject());
}

bc_Object * bc_GetTrueObject() {
	bc_ScriptContext* ctx = bc_GetCurrentScriptContext();
	if (ctx->True == NULL) {
		ctx->True = (bc_Object*)NewBool(true);
		ctx->True->Paint = PAINT_ONEXIT_T;
	}
	return ctx->True;
}

bc_Object * bc_GetFalseObject() {
	bc_ScriptContext* ctx = bc_GetCurrentScriptContext();
	if (ctx->False == NULL) {
		ctx->False = (bc_Object*)NewBool(false);
		ctx->False->Paint = PAINT_ONEXIT_T;
	}
	return ctx->False;
}

bc_Object * bc_GetNullObject() {
	bc_ScriptContext* ctx = bc_GetCurrentScriptContext();
	if (ctx->Null == NULL) {
		ctx->Null = bc_NewObject(sizeof(bc_Object));
		ctx->Null->GType = bc_NewGenericType(BC_TYPE_NULL);
		ctx->Null->VPtr = bc_GetVTableType(BC_TYPE_NULL);
		ctx->Null->Paint = PAINT_ONEXIT_T;
	}
	return ctx->Null;
}

bc_Object* bc_CopyObject(bc_Object * self) {
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

bc_Object* bc_CloneObject(bc_Object* self) {
	void* ret = self->OnMessage(self, OBJECT_MSG_CLONE, 0, NULL);
	assert(ret != NULL);
	return (bc_Object*)ret;
}

void bc_PaintAllObject(bc_Object* self, bc_ObjectPaint paint) {
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
	bc_ObjectMessageArgument argv[] = {paint};
	self->OnMessage(self, OBJECT_MSG_MARKALL, 1, argv);
	//コルーチンならその中身をマークする
	mark_coroutine(self);
}

void bc_MarkAllObject(bc_Object * self) {
	bc_PaintAllObject(self, PAINT_MARKED_T);
}

int bc_CountActiveObject() {
	return gObjectCount;
}

void bc_PrintObject(bc_Object * self) {
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

void bc_DeleteObject(bc_Object * self) {
	gObjectCount--;
	if((self->Flags & OBJECT_FLG_CLONE) > 0) {
		MEM_FREE(self);
		return;
	}
	if((self->Flags & OBJECT_FLG_COROUTINE) > 0) {
		bc_Coroutine* cor = (bc_Coroutine*)self;
		YieldContext* yctx = cor->Context;
		DeleteYieldContext(yctx);
		cor->Context = NULL;
	}
	self->OnMessage(self, OBJECT_MSG_DELETE, 0, NULL);
}

void bc_DestroyObject(bc_Object* self) {
	if (self == NULL) {
		return;
	}
	assert(self->Paint == PAINT_ONEXIT_T);
	self->OnMessage(self, OBJECT_MSG_DESTROY, 0, NULL);
}

int bc_ObjectToInt(bc_Object* self) {
	assert(bc_IsIntValue(self));
	return ((Integer*)self)->Value;
}

double bc_ObjectToDouble(bc_Object* self) {
	assert(bc_IsDoubleValue(self));
	return ((Double*)self)->Value;
}

bool bc_ObjectToBool(bc_Object* self) {
	assert(bc_IsBoolValue(self));
	return ((Bool*)self)->Value;
}

char bc_ObjectToChar(bc_Object* self) {
	assert(bc_IsCharValue(self));
	return ((Char*)self)->Value;
}

long bc_ObjectToLong(bc_Object* self) {
	//assert(self->Tag == OBJECT_LONG_T);
	return ((Long*)self)->Value;
}

bc_Object* bc_IntToObject(int i) {
	return (bc_Object*)NewInteger(i);
}

bc_Object* bc_DoubleToObject(double d) {
	return (bc_Object*)NewDouble(d);
}

bc_Object* bc_BoolToObject(bool b) {
	return bc_GetBoolObject(b);
}

bc_Object* bc_CharToObject(char c) {
	return (bc_Object*)NewChar(c);
}

bc_Object* bc_LongToObject(long l) {
	return (bc_Object*)NewLong(l);
}

bc_Object* bc_GetDefaultObject(bc_GenericType* gt) {
	bc_Object* a = bc_GetNullObject();
	if (gt->CoreType == BC_TYPE_INT) {
		a = bc_GetIntObject(0);
	} else if (gt->CoreType == BC_TYPE_DOUBLE) {
		a = (bc_Object*)NewDouble(0.0);
	} else if (gt->CoreType == BC_TYPE_BOOL) {
		a = bc_GetBoolObject(false);
	} else if (gt->CoreType == BC_TYPE_CHAR) {
		a = (bc_Object*)NewChar('\0');
	}
	assert(a->GType != NULL);
	return a;
}

bool bc_IsCharValue(bc_Object* self) {
	return self->GType->CoreType == BC_TYPE_CHAR;
}

bool bc_IsBoolValue(bc_Object* self) {
	return self->GType->CoreType == BC_TYPE_BOOL;
}

bool bc_IsIntValue(bc_Object* self) {
	return self->GType->CoreType == BC_TYPE_INT;
}

bool bc_IsDoubleValue(bc_Object* self) {
	return self->GType->CoreType == BC_TYPE_DOUBLE;
}

bool bc_IsStringValue(bc_Object* self) {
	return self->GType->CoreType == BC_TYPE_STRING;
}

bool bc_IsNullValue(bc_Object* self) {
	return self->GType->CoreType == BC_TYPE_NULL;
}

const char* bc_GetObjectName(bc_Object* self) {
	const char* name = "NULL";
	if(self->GType != NULL && self->GType->CoreType != NULL) {
		name = Ref2Str(bc_GetTypeFullName(self->GType->CoreType));
	}
	return name;
}

//private
static void delete_self(VectorItem item) {
	bc_Object* e = (bc_Object*)item;
	bc_DestroyObject(e);
}

static void mark_coroutine(bc_Object* self) {
	if(!((self->Flags & OBJECT_FLG_COROUTINE) > 0)) {
		return;
	}
	//コルーチンの現在の値
	bc_Coroutine* cor = (bc_Coroutine*)self;
	YieldContext* yctx = cor->Context;
	bc_MarkAllObject(yctx->Stock);
	bc_MarkAllObject(yctx->Source);
	//コルーチンに渡された引数
	for(int i=0; i<yctx->Parameters->Length; i++) {
		bc_MarkAllObject(AtVector(yctx->Parameters, i));
	}
}
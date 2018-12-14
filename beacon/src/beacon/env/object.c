#include "object.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/bc_library_interface.h"
#include "../util/mem.h"
#include "../util/string_buffer.h"
#include "../util/text.h"
#include "../vm/yield_context.h"
#include "TYPE_IMPL.h"
#include "coroutine.h"
#include "generic_type.h"
#include "heap.h"
#include "namespace.h"
#include "script_context.h"
#include "type_interface.h"
#include "vtable.h"

// proto
static void delete_self(bc_VectorItem item);
static void mark_coroutine(bc_Object* self);
// static Object* Object_malloc(ObjectTag type);
// static Object* gObjectTrue = NULL;
// static Object* gObjectFalse = NULL;
// static Object* gObjectNull = NULL;
static int gObjectCount = 0;

void* bc_HandleObjectMessage(bc_Object* self, bc_ObjectMessage msg, int argc,
                             bc_ObjectMessageArgument argv[]) {
#if DEBUG
        assert(self->GType != NULL);
        const char* name = bc_Ref2Str(bc_GetTypeName(self->GType->CoreType));
#endif
        switch (msg) {
                case OBJECT_MSG_NONE:
                        break;
                case OBJECT_MSG_PRINT:
                        printf("%p", self);
                        break;
                case OBJECT_MSG_DELETE:
                        bc_DeleteVector(self->Fields, bc_VectorDeleterOfNull);
                        MEM_FREE(self);
                        break;
                case OBJECT_MSG_DESTROY:
                        bc_DeleteVector(self->Fields, delete_self);
                        self->Fields = NULL;
                        bc_DeleteObject(self);
                        break;
                case OBJECT_MSG_MARKALL: {
                        assert(argc == 1);
                        bc_ObjectPaint paint = argv[0].Int;
                        for (int i = 0; i < self->Fields->Length; i++) {
                                bc_Object* e =
                                    (bc_Object*)bc_AtVector(self->Fields, i);
                                bc_PaintAllObject(e, paint);
                        }
                        break;
                }
                case OBJECT_MSG_CLONE: {
                        /*
                        if(self->Tag != OBJECT_ARRAY_T &&
                                self->Tag != OBJECT_REF_T &&
                                self->Tag != OBJECT_STRING_T) {
                                return CopyObject(self);
                        }
                        */
                        bc_Object* ret = bc_NewObject(NULL, sizeof(bc_Object));
                        bc_DeleteVector(ret->Fields, bc_VectorDeleterOfNull);
                        ret->GType = self->GType;
                        ret->VPtr = self->VPtr;
                        // ret->NativeSlotVec  = self->NativeSlotVec;
                        ret->Fields = self->Fields;
                        // ret->u.field_vec = self->u.field_vec;
                        ret->Flags = ret->Flags | OBJECT_FLG_CLONE;
                        return ret;
                }
        }
        return NULL;
}

void* bc_NewObject(bc_ScriptContext* sctx, size_t object_size) {
        if (object_size < sizeof(bc_Object)) {
                return NULL;
        }
        bc_LockHeap();
        void* mem = MEM_MALLOC(object_size);
        bc_GenericType* nullgt = bc_GetNullTypeNamespace(sctx)->GenericSelf;
        memset(mem, 0, object_size);
        bc_Object* ret = mem;
        ret->OnMessage = bc_HandleObjectMessage;
        // ret->NativeSlotVec = NULL;
        ret->GType = nullgt;
        ret->Paint = PAINT_UNMARKED_T;
        ret->VPtr = nullgt->CoreType->Kind.Class->VT;
        ret->Fields = bc_NewVector();
        ret->Flags = OBJECT_FLG_NONE;
        ret->Update = false;
        bc_AddHeap(bc_GetHeap(), ret);
        gObjectCount++;
        bc_UnlockHeap();
        return mem;
}

void* bc_ConstructObject(bc_ScriptContext* sctx, size_t object_size,
                         bc_GenericType* gtype) {
        assert(gtype != NULL);
        void* mem = bc_NewObject(sctx, object_size);
        bc_Object* obj = mem;
        obj->GType = gtype;
        obj->VPtr = bc_GetVTableType(gtype->CoreType);
        return mem;
}

bc_Object* bc_GetIntObject(int i) {
        bc_ScriptContext* ctx = bc_GetCurrentScriptContext();
        bc_CacheScriptContext();
        if ((i < -9) || i > 99) {
                return bc_IInternScriptContext(ctx, i);
                // return Object_int_new(i);
        }
        if (i < 0) {
                return (bc_Object*)bc_AtVector(ctx->NegativeIntegerCacheList,
                                               (-i) - 1);
        }
        return (bc_Object*)bc_AtVector(ctx->PositiveIntegerCacheList, i);
}

bc_Object* bc_GetBoolObject(bool b) {
        return (b ? bc_GetTrueObject() : bc_GetFalseObject());
}

bc_Object* bc_GetTrueObject() {
        bc_ScriptContext* ctx = bc_GetCurrentScriptContext();
        return bc_GetUniqueTrueObject(ctx);
}

bc_Object* bc_GetFalseObject() {
        bc_ScriptContext* ctx = bc_GetCurrentScriptContext();
        return bc_GetUniqueFalseObject(ctx);
}

bc_Object* bc_GetNullObject() {
        bc_ScriptContext* ctx = bc_GetCurrentScriptContext();
        return bc_GetUniqueNullObject(ctx);
}

bc_Object* bc_GetUniqueTrueObject(bc_ScriptContext* sctx) {
        if (sctx->True == NULL) {
                sctx->True = (bc_Object*)bc_NewBool(sctx, true);
                sctx->True->Paint = PAINT_ONEXIT_T;
        }
        return sctx->True;
}

bc_Object* bc_GetUniqueFalseObject(bc_ScriptContext* sctx) {
        if (sctx->False == NULL) {
                sctx->False = (bc_Object*)bc_NewBool(sctx, false);
                sctx->False->Paint = PAINT_ONEXIT_T;
        }
        return sctx->False;
}

bc_Object* bc_GetUniqueNullObject(bc_ScriptContext* sctx) {
        if (sctx->Null == NULL) {
                sctx->Null = bc_NewObject(sctx, sizeof(bc_Object));
                sctx->Null->GType = bc_NewGenericType(BC_TYPE_NULL);
                sctx->Null->VPtr = bc_GetVTableType(BC_TYPE_NULL);
                sctx->Null->Paint = PAINT_ONEXIT_T;
        }
        return sctx->Null;
}

bc_Object* bc_CopyObject(bc_Object* self) {
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
        // field#static_valueは
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
// printf("%s\n", Ref2Str(GetTypeName(self->GType->CoreType)));
#endif
        assert(self->OnMessage != NULL);
        bc_ObjectMessageArgument argv[] = {paint};
        self->OnMessage(self, OBJECT_MSG_MARKALL, 1, argv);
        //コルーチンならその中身をマークする
        mark_coroutine(self);
}

void bc_MarkAllObject(bc_Object* self) {
        bc_PaintAllObject(self, PAINT_MARKED_T);
}

int bc_CountActiveObject() { return gObjectCount; }

void bc_PrintObject(bc_Object* self) {
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
                printf("Bool: %s", (self == GetTrueObject() ? "true" :
        "false")); } else if (self->Tag == OBJECT_NULL_T) { printf("Ref: Null");
        } else if (self->Tag == OBJECT_REF_T) {
                printf("Ref: ");
                PrintGenericType(self->GType);
        }
        */
}

void bc_DeleteObject(bc_Object* self) {
        gObjectCount--;
        if ((self->Flags & OBJECT_FLG_CLONE) > 0) {
                MEM_FREE(self);
                return;
        }
        if ((self->Flags & OBJECT_FLG_COROUTINE) > 0) {
                bc_Coroutine* cor = (bc_Coroutine*)self;
                bc_YieldContext* yctx = cor->Context;
                bc_DeleteYieldContext(yctx);
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
        return ((bc_Integer*)self)->Value;
}

double bc_ObjectToDouble(bc_Object* self) {
        assert(bc_IsDoubleValue(self));
        return ((bc_Double*)self)->Value;
}

bool bc_ObjectToBool(bc_Object* self) {
        assert(bc_IsBoolValue(self));
        return ((bc_Bool*)self)->Value;
}

char bc_ObjectToChar(bc_Object* self) {
        assert(bc_IsCharValue(self));
        return ((bc_Char*)self)->Value;
}

long bc_ObjectToLong(bc_Object* self) {
        // assert(self->Tag == OBJECT_LONG_T);
        return ((bc_Long*)self)->Value;
}

bc_Object* bc_IntToObject(int i) { return (bc_Object*)bc_NewInteger(i); }

bc_Object* bc_DoubleToObject(double d) { return (bc_Object*)bc_NewDouble(d); }

bc_Object* bc_BoolToObject(bool b) { return bc_GetBoolObject(b); }

bc_Object* bc_CharToObject(char c) { return (bc_Object*)bc_NewChar(c); }

bc_Object* bc_LongToObject(long l) { return (bc_Object*)bc_NewLong(l); }

bc_Object* bc_GetDefaultObject(bc_GenericType* gt) {
        bc_Object* a = bc_GetNullObject();
        if (gt->CoreType == BC_TYPE_INT) {
                a = bc_GetIntObject(0);
        } else if (gt->CoreType == BC_TYPE_DOUBLE) {
                a = (bc_Object*)bc_NewDouble(0.0);
        } else if (gt->CoreType == BC_TYPE_BOOL) {
                a = bc_GetBoolObject(false);
        } else if (gt->CoreType == BC_TYPE_CHAR) {
                a = (bc_Object*)bc_NewChar('\0');
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
        if (self->GType != NULL && self->GType->CoreType != NULL) {
                name = bc_Ref2Str(bc_GetTypeFullName(self->GType->CoreType));
        }
        return name;
}

// private
static void delete_self(bc_VectorItem item) {
        bc_Object* e = (bc_Object*)item;
        bc_DestroyObject(e);
}

static void mark_coroutine(bc_Object* self) {
        if (!((self->Flags & OBJECT_FLG_COROUTINE) > 0)) {
                return;
        }
        //コルーチンの現在の値
        bc_Coroutine* cor = (bc_Coroutine*)self;
        bc_YieldContext* yctx = cor->Context;
        bc_MarkAllObject(yctx->Stock);
        bc_MarkAllObject(yctx->Source);
        //コルーチンに渡された引数
        for (int i = 0; i < yctx->Parameters->Length; i++) {
                bc_MarkAllObject(bc_AtVector(yctx->Parameters, i));
        }
}
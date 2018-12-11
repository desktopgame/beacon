#include "long.h"
#include "../../bc_library_interface.h"
// proto
static void bc_long_nativeInit(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env);
static void bc_long_nativeEquals(bc_Method* parent, bc_Frame* fr,
                                 bc_Enviroment* env);
static void bc_long_nativeAdd(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env);
static void bc_long_nativeSub(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env);
static void bc_long_nativeMul(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env);
static void bc_long_nativeDiv(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env);
static void bc_long_nativeMod(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env);
static void bc_long_nativeLShift(bc_Method* parent, bc_Frame* fr,
                                 bc_Enviroment* env);
static void bc_long_nativeRShift(bc_Method* parent, bc_Frame* fr,
                                 bc_Enviroment* env);
static void bc_long_nativeGT(bc_Method* parent, bc_Frame* fr,
                             bc_Enviroment* env);
static void bc_long_nativeGE(bc_Method* parent, bc_Frame* fr,
                             bc_Enviroment* env);
static void bc_long_nativeLT(bc_Method* parent, bc_Frame* fr,
                             bc_Enviroment* env);
static void bc_long_nativeLE(bc_Method* parent, bc_Frame* fr,
                             bc_Enviroment* env);
static void bc_long_nativeBitOr(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env);
static void bc_long_nativeBitAnd(bc_Method* parent, bc_Frame* fr,
                                 bc_Enviroment* env);
static void bc_long_nativeEQ(bc_Method* parent, bc_Frame* fr,
                             bc_Enviroment* env);

bc_Object* bc_NewLong(long value) {
        bc_Long* ret =
            bc_ConstructObject(NULL, sizeof(bc_Long), BC_GENERIC_OBJECT);
        ret->Value = value;
        return (bc_Object*)ret;
}

void bc_InitLong() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        bc_Type* longType = bc_NewPreloadClass(bc_InternString("Long"));
        bc_Class* longClass = BC_TYPE2CLASS(longType);
        longType->AllocSize = sizeof(bc_Long);
        bc_AddTypeNamespace(lang, longType);
        bc_DefineNativeMethodClass(longClass, "nativeInit", bc_long_nativeInit);
        bc_DefineNativeMethodClass(longClass, "nativeEquals",
                                   bc_long_nativeEquals);
        bc_DefineNativeMethodClass(longClass, "nativeAdd", bc_long_nativeAdd);
        bc_DefineNativeMethodClass(longClass, "nativeSub", bc_long_nativeSub);
        bc_DefineNativeMethodClass(longClass, "nativeMul", bc_long_nativeMul);
        bc_DefineNativeMethodClass(longClass, "nativeDiv", bc_long_nativeDiv);
        bc_DefineNativeMethodClass(longClass, "nativeMod", bc_long_nativeMod);
        bc_DefineNativeMethodClass(longClass, "nativeLShift",
                                   bc_long_nativeLShift);
        bc_DefineNativeMethodClass(longClass, "nativeRShift",
                                   bc_long_nativeRShift);
        bc_DefineNativeMethodClass(longClass, "nativeGT", bc_long_nativeGT);
        bc_DefineNativeMethodClass(longClass, "nativeGE", bc_long_nativeGE);
        bc_DefineNativeMethodClass(longClass, "nativeLT", bc_long_nativeLT);
        bc_DefineNativeMethodClass(longClass, "nativeLE", bc_long_nativeLE);
        bc_DefineNativeMethodClass(longClass, "nativeBitOr",
                                   bc_long_nativeBitOr);
        bc_DefineNativeMethodClass(longClass, "nativeBitAnd",
                                   bc_long_nativeBitAnd);
        bc_DefineNativeMethodClass(longClass, "nativeEQ", bc_long_nativeEQ);
}

bc_Type* bc_GetLongType() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        return bc_FindTypeFromNamespace(lang, bc_InternString("Long"));
}
// private
#define LONG_VALUE(obj) (((bc_Long*)obj)->Value)
static void bc_long_nativeInit(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* i = bc_AtVector(fr->VariableTable, 1);

        LONG_VALUE(self) = LONG_VALUE(i);
        // self->Tag = OBJECT_INT_T;
}

static void bc_long_nativeEquals(bc_Method* parent, bc_Frame* fr,
                                 bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* i = bc_AtVector(fr->VariableTable, 1);
        bc_PushVector(fr->ValueStack, bc_BoolToObject(bc_ObjectToLong(self) ==
                                                      bc_ObjectToLong(i)));
}

static void bc_long_nativeAdd(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewLong(LONG_VALUE(self) + LONG_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_long_nativeSub(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewLong(LONG_VALUE(self) - LONG_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_long_nativeMul(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewLong(LONG_VALUE(self) * LONG_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_long_nativeDiv(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewLong(LONG_VALUE(self) / LONG_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_long_nativeMod(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewLong(LONG_VALUE(self) % LONG_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_long_nativeLShift(bc_Method* parent, bc_Frame* fr,
                                 bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewLong(LONG_VALUE(self) << LONG_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_long_nativeRShift(bc_Method* parent, bc_Frame* fr,
                                 bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewLong(LONG_VALUE(self) >> LONG_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_long_nativeGT(bc_Method* parent, bc_Frame* fr,
                             bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret = bc_GetBoolObject(LONG_VALUE(self) > LONG_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_long_nativeGE(bc_Method* parent, bc_Frame* fr,
                             bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret = bc_GetBoolObject(LONG_VALUE(self) >= LONG_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_long_nativeLT(bc_Method* parent, bc_Frame* fr,
                             bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret = bc_GetBoolObject(LONG_VALUE(self) < LONG_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_long_nativeLE(bc_Method* parent, bc_Frame* fr,
                             bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret = bc_GetBoolObject(LONG_VALUE(self) <= LONG_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_long_nativeBitOr(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewLong(LONG_VALUE(self) | LONG_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_long_nativeBitAnd(bc_Method* parent, bc_Frame* fr,
                                 bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewLong(LONG_VALUE(self) & LONG_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_long_nativeEQ(bc_Method* parent, bc_Frame* fr,
                             bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret = bc_GetBoolObject(LONG_VALUE(self) == LONG_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}
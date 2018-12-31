#include "../../bc_library_impl.h"
#include "../../bc_library_interface.h"
#include "int.h"

// proto
static void bc_short_nativeInit(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env);
static void bc_short_nativeEquals(bc_Method* parent, bc_Frame* fr,
                                  bc_Enviroment* env);
static void bc_short_nativeAdd(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env);
static void bc_short_nativeSub(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env);
static void bc_short_nativeMul(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env);
static void bc_short_nativeDiv(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env);
static void bc_short_nativeMod(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env);
static void bc_short_nativeLShift(bc_Method* parent, bc_Frame* fr,
                                  bc_Enviroment* env);
static void bc_short_nativeRShift(bc_Method* parent, bc_Frame* fr,
                                  bc_Enviroment* env);
static void bc_short_nativeGT(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env);
static void bc_short_nativeGE(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env);
static void bc_short_nativeLT(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env);
static void bc_short_nativeLE(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env);
static void bc_short_nativeBitOr(bc_Method* parent, bc_Frame* fr,
                                 bc_Enviroment* env);
static void bc_short_nativeBitAnd(bc_Method* parent, bc_Frame* fr,
                                  bc_Enviroment* env);
static void bc_short_nativeEQ(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env);

bc_Object* bc_NewShort(short value) {
        bc_Short* s =
            bc_ConstructObject(NULL, sizeof(bc_Short), BC_GENERIC_SHORT);
        s->Value = value;
        return (bc_Object*)s;
}

void bc_InitShort() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        bc_Type* shortType = bc_NewPreloadClass(bc_InternString("Short"));
        bc_Class* shortClass = BC_TYPE2CLASS(shortType);
        shortType->AllocSize = sizeof(bc_Short);
        bc_AddTypeNamespace(lang, shortType);
        bc_DefineNativeMethodClass(shortClass, "nativeInit",
                                   bc_short_nativeInit);
        bc_DefineNativeMethodClass(shortClass, "nativeEquals",
                                   bc_short_nativeEquals);
        bc_DefineNativeMethodClass(shortClass, "nativeAdd", bc_short_nativeAdd);
        bc_DefineNativeMethodClass(shortClass, "nativeSub", bc_short_nativeSub);
        bc_DefineNativeMethodClass(shortClass, "nativeMul", bc_short_nativeMul);
        bc_DefineNativeMethodClass(shortClass, "nativeDiv", bc_short_nativeDiv);
        bc_DefineNativeMethodClass(shortClass, "nativeMod", bc_short_nativeMod);
        bc_DefineNativeMethodClass(shortClass, "nativeLShift",
                                   bc_short_nativeLShift);
        bc_DefineNativeMethodClass(shortClass, "nativeRShift",
                                   bc_short_nativeRShift);
        bc_DefineNativeMethodClass(shortClass, "nativeGT", bc_short_nativeGT);
        bc_DefineNativeMethodClass(shortClass, "nativeGE", bc_short_nativeGE);
        bc_DefineNativeMethodClass(shortClass, "nativeLT", bc_short_nativeLT);
        bc_DefineNativeMethodClass(shortClass, "nativeLE", bc_short_nativeLE);
        bc_DefineNativeMethodClass(shortClass, "nativeBitOr",
                                   bc_short_nativeBitOr);
        bc_DefineNativeMethodClass(shortClass, "nativeBitAnd",
                                   bc_short_nativeBitAnd);
        bc_DefineNativeMethodClass(shortClass, "nativeEQ", bc_short_nativeEQ);
}

bc_Type* bc_GetShortType() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        return bc_FindTypeFromNamespace(lang, bc_InternString("Short"));
}
// private
#define SHORT_VALUE(obj) (((bc_Short*)obj)->Value)
static void bc_short_nativeInit(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* i = bc_AtVector(fr->VariableTable, 1);

        SHORT_VALUE(self) = SHORT_VALUE(i);
        // self->Tag = OBJECT_INT_T;
}

static void bc_short_nativeEquals(bc_Method* parent, bc_Frame* fr,
                                  bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* i = bc_AtVector(fr->VariableTable, 1);
        bc_PushVector(fr->ValueStack, bc_BoolToObject(bc_ObjectToShort(self) ==
                                                      bc_ObjectToShort(i)));
}

static void bc_short_nativeAdd(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewShort(SHORT_VALUE(self) + SHORT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_short_nativeSub(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewShort(SHORT_VALUE(self) - SHORT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_short_nativeMul(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewShort(SHORT_VALUE(self) * SHORT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_short_nativeDiv(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewShort(SHORT_VALUE(self) / SHORT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_short_nativeMod(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewShort(SHORT_VALUE(self) % SHORT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_short_nativeLShift(bc_Method* parent, bc_Frame* fr,
                                  bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewShort(SHORT_VALUE(self) << SHORT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_short_nativeRShift(bc_Method* parent, bc_Frame* fr,
                                  bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewShort(SHORT_VALUE(self) >> SHORT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_short_nativeGT(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret = bc_GetBoolObject(SHORT_VALUE(self) > SHORT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_short_nativeGE(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret = bc_GetBoolObject(SHORT_VALUE(self) >= SHORT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_short_nativeLT(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret = bc_GetBoolObject(SHORT_VALUE(self) < SHORT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_short_nativeLE(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret = bc_GetBoolObject(SHORT_VALUE(self) <= SHORT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_short_nativeBitOr(bc_Method* parent, bc_Frame* fr,
                                 bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewShort(SHORT_VALUE(self) | SHORT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_short_nativeBitAnd(bc_Method* parent, bc_Frame* fr,
                                  bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewShort(SHORT_VALUE(self) & SHORT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_short_nativeEQ(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret = bc_GetBoolObject(SHORT_VALUE(self) == SHORT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}
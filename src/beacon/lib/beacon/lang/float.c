#include "float.h"
#include "../../bc_library_impl.h"
#include "../../bc_library_interface.h"

// proto
static void bc_float_nativeInit(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env);
static void bc_float_nativeEquals(bc_Method* parent, bc_Frame* fr,
                                  bc_Enviroment* env);
static void bc_float_nativeAdd(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env);
static void bc_float_nativeSub(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env);
static void bc_float_nativeMul(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env);
static void bc_float_nativeDiv(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env);
static void bc_float_nativeGT(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env);
static void bc_float_nativeGE(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env);
static void bc_float_nativeLT(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env);
static void bc_float_nativeLE(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env);
static void bc_float_nativeEQ(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env);
static void bc_float_nativeToString(bc_Method* parent, bc_Frame* fr,
                                    bc_Enviroment* env);

bc_Object* bc_NewFloat(float value) {
        bc_Float* ret =
            bc_ConstructObject(NULL, sizeof(bc_Float), BC_GENERIC_FLOAT);
        ret->Value = value;
        return (bc_Object*)ret;
}

void bc_InitFloat() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        bc_Type* floatType = bc_NewPreloadClass(bc_InternString("Float"));
        bc_Class* floatClass = BC_TYPE2CLASS(floatType);
        floatType->AllocSize = sizeof(bc_Float);
        bc_AddTypeNamespace(lang, floatType);
        bc_DefineNativeMethodClass(floatClass, "nativeInit",
                                   bc_float_nativeInit);
        bc_DefineNativeMethodClass(floatClass, "nativeEquals",
                                   bc_float_nativeEquals);
        bc_DefineNativeMethodClass(floatClass, "nativeAdd", bc_float_nativeAdd);
        bc_DefineNativeMethodClass(floatClass, "nativeSub", bc_float_nativeSub);
        bc_DefineNativeMethodClass(floatClass, "nativeMul", bc_float_nativeMul);
        bc_DefineNativeMethodClass(floatClass, "nativeDiv", bc_float_nativeDiv);
        bc_DefineNativeMethodClass(floatClass, "nativeGT", bc_float_nativeGT);
        bc_DefineNativeMethodClass(floatClass, "nativeGE", bc_float_nativeGE);
        bc_DefineNativeMethodClass(floatClass, "nativeLT", bc_float_nativeLT);
        bc_DefineNativeMethodClass(floatClass, "nativeLE", bc_float_nativeLE);
        bc_DefineNativeMethodClass(floatClass, "nativeEQ", bc_float_nativeEQ);
        bc_DefineNativeMethodClass(floatClass, "nativeToString",
                                   bc_float_nativeToString);
}

bc_Type* bc_GetFloatType() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        return bc_FindTypeFromNamespace(lang, bc_InternString("Float"));
}
// private
#define FLOAT_VALUE(obj) (((bc_Float*)obj)->Value)
static void bc_float_nativeInit(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* d = bc_AtVector(fr->VariableTable, 1);

        FLOAT_VALUE(self) = FLOAT_VALUE(d);
        // self->Tag = OBJECT_DOUBLE_T;
}

static void bc_float_nativeEquals(bc_Method* parent, bc_Frame* fr,
                                  bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* d = bc_AtVector(fr->VariableTable, 1);
        bc_PushVector(fr->ValueStack, bc_BoolToObject(bc_ObjectToFloat(self) ==
                                                      bc_ObjectToFloat(d)));
}

static void bc_float_nativeAdd(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewFloat(FLOAT_VALUE(self) + FLOAT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_float_nativeSub(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewFloat(FLOAT_VALUE(self) - FLOAT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_float_nativeMul(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewFloat(FLOAT_VALUE(self) * FLOAT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_float_nativeDiv(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewFloat(FLOAT_VALUE(self) / FLOAT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_float_nativeGT(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret = bc_GetBoolObject(FLOAT_VALUE(self) > FLOAT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_float_nativeGE(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret = bc_GetBoolObject(FLOAT_VALUE(self) >= FLOAT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_float_nativeLT(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret = bc_GetBoolObject(FLOAT_VALUE(self) < FLOAT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_float_nativeLE(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret = bc_GetBoolObject(FLOAT_VALUE(self) <= FLOAT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_float_nativeEQ(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret = bc_GetBoolObject(FLOAT_VALUE(self) == FLOAT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_float_nativeToString(bc_Method* parent, bc_Frame* fr,
                                    bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        float f = FLOAT_VALUE(self);
        char block[16] = {0};
        sprintf(block, "%f", f);
        bc_PushVector(fr->ValueStack, bc_NewString(block));
}
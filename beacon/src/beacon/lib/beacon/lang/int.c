#include "int.h"
#include "../../bc_library_impl.h"
#include "../../bc_library_interface.h"

// proto
static void bc_int_nativeInit(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env);
static void bc_int_nativeEquals(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env);
static void bc_int_nativeAdd(bc_Method* parent, bc_Frame* fr,
                             bc_Enviroment* env);
static void bc_int_nativeSub(bc_Method* parent, bc_Frame* fr,
                             bc_Enviroment* env);
static void bc_int_nativeMul(bc_Method* parent, bc_Frame* fr,
                             bc_Enviroment* env);
static void bc_int_nativeDiv(bc_Method* parent, bc_Frame* fr,
                             bc_Enviroment* env);
static void bc_int_nativeMod(bc_Method* parent, bc_Frame* fr,
                             bc_Enviroment* env);
static void bc_int_nativeLShift(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env);
static void bc_int_nativeRShift(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env);
static void bc_int_nativeGT(bc_Method* parent, bc_Frame* fr,
                            bc_Enviroment* env);
static void bc_int_nativeGE(bc_Method* parent, bc_Frame* fr,
                            bc_Enviroment* env);
static void bc_int_nativeLT(bc_Method* parent, bc_Frame* fr,
                            bc_Enviroment* env);
static void bc_int_nativeLE(bc_Method* parent, bc_Frame* fr,
                            bc_Enviroment* env);
static void bc_int_nativeBitOr(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env);
static void bc_int_nativeBitAnd(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env);
static void bc_int_nativeEQ(bc_Method* parent, bc_Frame* fr,
                            bc_Enviroment* env);
static void bc_int_nativeToChar(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env);

bc_Object* bc_NewInteger(int value) {
        bc_Integer* i = bc_ConstructObject(sizeof(bc_Integer), BC_GENERIC_INT);
        i->Value = value;
        return (bc_Object*)i;
}

void bc_InitInt() {
        bc_Namespace* lang = bc_GetLangNamespace();
        bc_Type* intType = bc_NewPreloadClass(bc_InternString("Int"));
        bc_Class* intClass = BC_TYPE2CLASS(intType);
        intType->AllocSize = sizeof(bc_Integer);
        bc_AddTypeNamespace(lang, intType);
        bc_DefineNativeMethodClass(intClass, "nativeInit", bc_int_nativeInit);
        bc_DefineNativeMethodClass(intClass, "nativeEquals",
                                   bc_int_nativeEquals);
        bc_DefineNativeMethodClass(intClass, "nativeAdd", bc_int_nativeAdd);
        bc_DefineNativeMethodClass(intClass, "nativeSub", bc_int_nativeSub);
        bc_DefineNativeMethodClass(intClass, "nativeMul", bc_int_nativeMul);
        bc_DefineNativeMethodClass(intClass, "nativeDiv", bc_int_nativeDiv);
        bc_DefineNativeMethodClass(intClass, "nativeMod", bc_int_nativeMod);
        bc_DefineNativeMethodClass(intClass, "nativeLShift",
                                   bc_int_nativeLShift);
        bc_DefineNativeMethodClass(intClass, "nativeRShift",
                                   bc_int_nativeRShift);
        bc_DefineNativeMethodClass(intClass, "nativeGT", bc_int_nativeGT);
        bc_DefineNativeMethodClass(intClass, "nativeGE", bc_int_nativeGE);
        bc_DefineNativeMethodClass(intClass, "nativeLT", bc_int_nativeLT);
        bc_DefineNativeMethodClass(intClass, "nativeLE", bc_int_nativeLE);
        bc_DefineNativeMethodClass(intClass, "nativeBitOr", bc_int_nativeBitOr);
        bc_DefineNativeMethodClass(intClass, "nativeBitAnd",
                                   bc_int_nativeBitAnd);
        bc_DefineNativeMethodClass(intClass, "nativeEQ", bc_int_nativeEQ);
        bc_DefineNativeMethodClass(intClass, "nativeToChar",
                                   bc_int_nativeToChar);
}

bc_Type* bc_GetIntType() {
        bc_Namespace* lang = bc_GetLangNamespace();
        return bc_FindTypeFromNamespace(lang, bc_InternString("Int"));
}
// private
#define INT_VALUE(obj) (((bc_Integer*)obj)->Value)
static void bc_int_nativeInit(bc_Method* parent, bc_Frame* fr,
                              bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* i = bc_AtVector(fr->VariableTable, 1);

        INT_VALUE(self) = INT_VALUE(i);
        // self->Tag = OBJECT_INT_T;
}

static void bc_int_nativeEquals(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* i = bc_AtVector(fr->VariableTable, 1);
        bc_PushVector(fr->ValueStack, bc_BoolToObject(bc_ObjectToInt(self) ==
                                                      bc_ObjectToInt(i)));
}

static void bc_int_nativeAdd(bc_Method* parent, bc_Frame* fr,
                             bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewInteger(INT_VALUE(self) + INT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeSub(bc_Method* parent, bc_Frame* fr,
                             bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewInteger(INT_VALUE(self) - INT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeMul(bc_Method* parent, bc_Frame* fr,
                             bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewInteger(INT_VALUE(self) * INT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeDiv(bc_Method* parent, bc_Frame* fr,
                             bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewInteger(INT_VALUE(self) / INT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeMod(bc_Method* parent, bc_Frame* fr,
                             bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewInteger(INT_VALUE(self) % INT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeLShift(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewInteger(INT_VALUE(self) << INT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeRShift(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewInteger(INT_VALUE(self) >> INT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeGT(bc_Method* parent, bc_Frame* fr,
                            bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret = bc_GetBoolObject(INT_VALUE(self) > INT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeGE(bc_Method* parent, bc_Frame* fr,
                            bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret = bc_GetBoolObject(INT_VALUE(self) >= INT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeLT(bc_Method* parent, bc_Frame* fr,
                            bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret = bc_GetBoolObject(INT_VALUE(self) < INT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeLE(bc_Method* parent, bc_Frame* fr,
                            bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret = bc_GetBoolObject(INT_VALUE(self) <= INT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeBitOr(bc_Method* parent, bc_Frame* fr,
                               bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewInteger(INT_VALUE(self) | INT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeBitAnd(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret =
            (bc_Object*)bc_NewInteger(INT_VALUE(self) & INT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeEQ(bc_Method* parent, bc_Frame* fr,
                            bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_Object* a = bc_AtVector(fr->VariableTable, 1);
        bc_Object* ret = bc_GetBoolObject(INT_VALUE(self) == INT_VALUE(a));
        bc_PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeToChar(bc_Method* parent, bc_Frame* fr,
                                bc_Enviroment* env) {
        bc_Object* self = bc_AtVector(fr->VariableTable, 0);
        bc_PushVector(fr->ValueStack, bc_NewChar(INT_VALUE(self)));
}
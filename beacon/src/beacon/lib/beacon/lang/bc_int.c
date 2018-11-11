#include "bc_int.h"
#include "../../bc_library_interface.h"
#include "../../bc_library_impl.h"

//proto
static void bc_int_nativeInit(Method* parent, Frame* fr, Enviroment* env);
static void bc_int_nativeEquals(Method* parent, Frame* fr, Enviroment* env);
static void bc_int_nativeAdd(Method* parent, Frame* fr, Enviroment* env);
static void bc_int_nativeSub(Method* parent, Frame* fr, Enviroment* env);
static void bc_int_nativeMul(Method* parent, Frame* fr, Enviroment* env);
static void bc_int_nativeDiv(Method* parent, Frame* fr, Enviroment* env);
static void bc_int_nativeMod(Method* parent, Frame* fr, Enviroment* env);
static void bc_int_nativeLShift(Method* parent, Frame* fr, Enviroment* env);
static void bc_int_nativeRShift(Method* parent, Frame* fr, Enviroment* env);
static void bc_int_nativeGT(Method* parent, Frame* fr, Enviroment* env);
static void bc_int_nativeGE(Method* parent, Frame* fr, Enviroment* env);
static void bc_int_nativeLT(Method* parent, Frame* fr, Enviroment* env);
static void bc_int_nativeLE(Method* parent, Frame* fr, Enviroment* env);
static void bc_int_nativeBitOr(Method* parent, Frame* fr, Enviroment* env);
static void bc_int_nativeBitAnd(Method* parent, Frame* fr, Enviroment* env);
static void bc_int_nativeEQ(Method* parent, Frame* fr, Enviroment* env);
static void bc_int_nativeToChar(Method* parent, Frame* fr, Enviroment* env);

Integer* NewInteger(int value) {
	Integer* i = ConstructObject(sizeof(Integer), GENERIC_INT);
	i->Value = value;
	return i;
}

void InitBCInt() {
	Namespace* lang =  GetLangNamespace();
	Type* intType = NewPreloadClass(InternString("Int"));
	Class* intClass = TYPE2CLASS(intType);
	intType->AllocSize = sizeof(Integer);
	AddTypeNamespace(lang, intType);
	DefineNativeMethodClass(intClass, "nativeInit", bc_int_nativeInit);
	DefineNativeMethodClass(intClass, "nativeEquals", bc_int_nativeEquals);
	DefineNativeMethodClass(intClass, "nativeAdd", bc_int_nativeAdd);
	DefineNativeMethodClass(intClass, "nativeSub", bc_int_nativeSub);
	DefineNativeMethodClass(intClass, "nativeMul", bc_int_nativeMul);
	DefineNativeMethodClass(intClass, "nativeDiv", bc_int_nativeDiv);
	DefineNativeMethodClass(intClass, "nativeMod", bc_int_nativeMod);
	DefineNativeMethodClass(intClass, "nativeLShift", bc_int_nativeLShift);
	DefineNativeMethodClass(intClass, "nativeRShift", bc_int_nativeRShift);
	DefineNativeMethodClass(intClass, "nativeGT", bc_int_nativeGT);
	DefineNativeMethodClass(intClass, "nativeGE", bc_int_nativeGE);
	DefineNativeMethodClass(intClass, "nativeLT", bc_int_nativeLT);
	DefineNativeMethodClass(intClass, "nativeLE", bc_int_nativeLE);
	DefineNativeMethodClass(intClass, "nativeBitOr", bc_int_nativeBitOr);
	DefineNativeMethodClass(intClass, "nativeBitAnd", bc_int_nativeBitAnd);
	DefineNativeMethodClass(intClass, "nativeEQ", bc_int_nativeEQ);
	DefineNativeMethodClass(intClass, "nativeToChar", bc_int_nativeToChar);
}

Type* GetBCIntType() {
	Namespace* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Int"));
}
//private
#define INT_VALUE(obj) (((Integer*)obj)->Value)
static void bc_int_nativeInit(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* i = AtVector(fr->VariableTable, 1);

	INT_VALUE(self) = INT_VALUE(i);
	//self->Tag = OBJECT_INT_T;
}

static void bc_int_nativeEquals(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* i = AtVector(fr->VariableTable, 1);
	PushVector(fr->ValueStack, BOOL2OBJ(ObjectToInt(self) == ObjectToInt(i)));
}

static void bc_int_nativeAdd(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = (Object*)NewInteger(INT_VALUE(self) + INT_VALUE(a));
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeSub(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = (Object*)NewInteger(INT_VALUE(self) - INT_VALUE(a));
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeMul(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = (Object*)NewInteger(INT_VALUE(self) * INT_VALUE(a));
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeDiv(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = (Object*)NewInteger(INT_VALUE(self) / INT_VALUE(a));
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeMod(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = (Object*)NewInteger(INT_VALUE(self) % INT_VALUE(a));
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeLShift(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = (Object*)NewInteger(INT_VALUE(self) << INT_VALUE(a));
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeRShift(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = (Object*)NewInteger(INT_VALUE(self) >> INT_VALUE(a));
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeGT(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = GetBoolObject(INT_VALUE(self) > INT_VALUE(a));
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeGE(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = GetBoolObject(INT_VALUE(self) >= INT_VALUE(a));
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeLT(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = GetBoolObject(INT_VALUE(self) < INT_VALUE(a));
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeLE(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = GetBoolObject(INT_VALUE(self) <= INT_VALUE(a));
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeBitOr(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = (Object*)NewInteger(INT_VALUE(self) | INT_VALUE(a));
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeBitAnd(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = (Object*)NewInteger(INT_VALUE(self) & INT_VALUE(a));
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeEQ(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = GetBoolObject(INT_VALUE(self) == INT_VALUE(a));
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeToChar(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	PushVector(fr->ValueStack, NewChar(INT_VALUE(self)));
}
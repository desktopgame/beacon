#include "bc_int.h"
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

void InitBCInt() {
	Namespace* lang =  GetLangNamespace();
	type* intType = NewPreloadClass(InternString("Int"));
	class_* intClass = TYPE2CLASS(intType);
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

type* GetBCIntType() {
	Namespace* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Int"));
}
//private
static void bc_int_nativeInit(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* i = AtVector(fr->VariableTable, 1);

	self->u.int_ = i->u.int_;
	self->Tag = OBJECT_INT_T;
}

static void bc_int_nativeEquals(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* i = AtVector(fr->VariableTable, 1);
	PushVector(fr->ValueStack, BOOL2OBJ(OBJ2INT(self) == OBJ2INT(i)));
}

static void bc_int_nativeAdd(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = Object_int_new(self->u.int_ + a->u.int_);
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeSub(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = Object_int_new(self->u.int_ - a->u.int_);
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeMul(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = Object_int_new(self->u.int_ * a->u.int_);
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeDiv(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = Object_int_new(self->u.int_ / a->u.int_);
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeMod(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = Object_int_new(self->u.int_ % a->u.int_);
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeLShift(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = Object_int_new(self->u.int_ << a->u.int_);
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeRShift(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = Object_int_new(self->u.int_ >> a->u.int_);
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeGT(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = GetBoolObject(self->u.int_ > a->u.int_);
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeGE(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = GetBoolObject(self->u.int_ >= a->u.int_);
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeLT(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = GetBoolObject(self->u.int_ < a->u.int_);
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeLE(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = GetBoolObject(self->u.int_ <= a->u.int_);
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeBitOr(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = Object_int_new(self->u.int_ | a->u.int_);
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeBitAnd(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = Object_int_new(self->u.int_ & a->u.int_);
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeEQ(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* a = AtVector(fr->VariableTable, 1);
	Object* ret = GetBoolObject(self->u.int_ == a->u.int_);
	PushVector(fr->ValueStack, ret);
}

static void bc_int_nativeToChar(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	PushVector(fr->ValueStack, Object_char_new(self->u.int_));
}
#include "bc_double.h"
#include "../../bc_library_impl.h"

//proto
static void bc_double_nativeInit(Method* parent, Frame* fr, Enviroment* env);
static void bc_double_nativeEquals(Method* parent, Frame* fr, Enviroment* env);
static void bc_double_nativeAdd(Method* parent, Frame* fr, Enviroment* env);
static void bc_double_nativeSub(Method* parent, Frame* fr, Enviroment* env);
static void bc_double_nativeMul(Method* parent, Frame* fr, Enviroment* env);
static void bc_double_nativeDiv(Method* parent, Frame* fr, Enviroment* env);
static void bc_double_nativeGT(Method* parent, Frame* fr, Enviroment* env);
static void bc_double_nativeGE(Method* parent, Frame* fr, Enviroment* env);
static void bc_double_nativeLT(Method* parent, Frame* fr, Enviroment* env);
static void bc_double_nativeLE(Method* parent, Frame* fr, Enviroment* env);
static void bc_double_nativeEQ(Method* parent, Frame* fr, Enviroment* env);

void InitBCDouble() {
	Namespace* lang = GetLangNamespace();
	type* doubleType = NewPreloadClass(InternString("Double"));
	class_* doubleClass = TYPE2CLASS(doubleType);
	AddTypeNamespace(lang, doubleType);
	DefineNativeMethodClass(doubleClass, "nativeInit", bc_double_nativeInit);
	DefineNativeMethodClass(doubleClass, "nativeEquals", bc_double_nativeEquals);
	DefineNativeMethodClass(doubleClass, "nativeAdd", bc_double_nativeAdd);
	DefineNativeMethodClass(doubleClass, "nativeSub", bc_double_nativeSub);
	DefineNativeMethodClass(doubleClass, "nativeMul", bc_double_nativeMul);
	DefineNativeMethodClass(doubleClass, "nativeDiv", bc_double_nativeDiv);
	DefineNativeMethodClass(doubleClass, "nativeGT", bc_double_nativeGT);
	DefineNativeMethodClass(doubleClass, "nativeGE", bc_double_nativeGE);
	DefineNativeMethodClass(doubleClass, "nativeLT", bc_double_nativeLT);
	DefineNativeMethodClass(doubleClass, "nativeLE", bc_double_nativeLE);
	DefineNativeMethodClass(doubleClass, "nativeEQ", bc_double_nativeEQ);
}

type* GetBCDoubleType() {
	Namespace* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Double"));
}
//private
static void bc_double_nativeInit(Method* parent, Frame* fr, Enviroment* env) {
	object* self = AtVector(fr->VariableTable, 0);
	object* d = AtVector(fr->VariableTable, 1);

	self->u.double_ = d->u.double_;
	self->tag = OBJECT_DOUBLE_T;
}

static void bc_double_nativeEquals(Method* parent, Frame* fr, Enviroment* env) {
	object* self = AtVector(fr->VariableTable, 0);
	object* d = AtVector(fr->VariableTable, 1);
	PushVector(fr->ValueStack, BOOL2OBJ(OBJ2DOUBLE(self) == OBJ2DOUBLE(d)));
}

static void bc_double_nativeAdd(Method* parent, Frame* fr, Enviroment* env) {
	object* self = AtVector(fr->VariableTable, 0);
	object* a = AtVector(fr->VariableTable, 1);
	object* ret = object_double_new(self->u.double_ + a->u.double_);
	PushVector(fr->ValueStack, ret);
}

static void bc_double_nativeSub(Method* parent, Frame* fr, Enviroment* env) {
	object* self = AtVector(fr->VariableTable, 0);
	object* a = AtVector(fr->VariableTable, 1);
	object* ret = object_double_new(self->u.double_ - a->u.double_);
	PushVector(fr->ValueStack, ret);
}

static void bc_double_nativeMul(Method* parent, Frame* fr, Enviroment* env) {
	object* self = AtVector(fr->VariableTable, 0);
	object* a = AtVector(fr->VariableTable, 1);
	object* ret = object_double_new(self->u.double_ * a->u.double_);
	PushVector(fr->ValueStack, ret);
}

static void bc_double_nativeDiv(Method* parent, Frame* fr, Enviroment* env) {
	object* self = AtVector(fr->VariableTable, 0);
	object* a = AtVector(fr->VariableTable, 1);
	object* ret = object_double_new(self->u.double_ / a->u.double_);
	PushVector(fr->ValueStack, ret);
}

static void bc_double_nativeGT(Method* parent, Frame* fr, Enviroment* env) {
	object* self = AtVector(fr->VariableTable, 0);
	object* a = AtVector(fr->VariableTable, 1);
	object* ret = GetBoolObject(self->u.double_ > a->u.double_);
	PushVector(fr->ValueStack, ret);
}

static void bc_double_nativeGE(Method* parent, Frame* fr, Enviroment* env) {
	object* self = AtVector(fr->VariableTable, 0);
	object* a = AtVector(fr->VariableTable, 1);
	object* ret = GetBoolObject(self->u.double_ >= a->u.double_);
	PushVector(fr->ValueStack, ret);
}

static void bc_double_nativeLT(Method* parent, Frame* fr, Enviroment* env) {
	object* self = AtVector(fr->VariableTable, 0);
	object* a = AtVector(fr->VariableTable, 1);
	object* ret = GetBoolObject(self->u.double_ < a->u.double_);
	PushVector(fr->ValueStack, ret);
}

static void bc_double_nativeLE(Method* parent, Frame* fr, Enviroment* env) {
	object* self = AtVector(fr->VariableTable, 0);
	object* a = AtVector(fr->VariableTable, 1);
	object* ret = GetBoolObject(self->u.double_ <= a->u.double_);
	PushVector(fr->ValueStack, ret);
}

static void bc_double_nativeEQ(Method* parent, Frame* fr, Enviroment* env) {
	object* self = AtVector(fr->VariableTable, 0);
	object* a = AtVector(fr->VariableTable, 1);
	object* ret = GetBoolObject(self->u.double_ == a->u.double_);
	PushVector(fr->ValueStack, ret);
}
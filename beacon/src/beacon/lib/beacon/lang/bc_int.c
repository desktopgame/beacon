#include "bc_int.h"
#include "../../bc_library_impl.h"

//proto
static void bc_int_nativeInit(method* parent, frame* fr, enviroment* env);
static void bc_int_nativeEquals(method* parent, frame* fr, enviroment* env);
static void bc_int_nativeAdd(method* parent, frame* fr, enviroment* env);
static void bc_int_nativeSub(method* parent, frame* fr, enviroment* env);
static void bc_int_nativeMul(method* parent, frame* fr, enviroment* env);
static void bc_int_nativeDiv(method* parent, frame* fr, enviroment* env);
static void bc_int_nativeMod(method* parent, frame* fr, enviroment* env);
static void bc_int_nativeLShift(method* parent, frame* fr, enviroment* env);
static void bc_int_nativeRShift(method* parent, frame* fr, enviroment* env);
static void bc_int_nativeGT(method* parent, frame* fr, enviroment* env);
static void bc_int_nativeGE(method* parent, frame* fr, enviroment* env);
static void bc_int_nativeLT(method* parent, frame* fr, enviroment* env);
static void bc_int_nativeLE(method* parent, frame* fr, enviroment* env);
static void bc_int_nativeBitOr(method* parent, frame* fr, enviroment* env);
static void bc_int_nativeBitAnd(method* parent, frame* fr, enviroment* env);
static void bc_int_nativeEQ(method* parent, frame* fr, enviroment* env);
static void bc_int_nativeToChar(method* parent, frame* fr, enviroment* env);

void InitBCInt() {
	namespace_* lang =  GetLangNamespace();
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
	namespace_* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Int"));
}
//private
static void bc_int_nativeInit(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* i = AtVector(fr->ref_stack, 1);

	self->u.int_ = i->u.int_;
	self->tag = OBJECT_INT_T;
}

static void bc_int_nativeEquals(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* i = AtVector(fr->ref_stack, 1);
	PushVector(fr->value_stack, BOOL2OBJ(OBJ2INT(self) == OBJ2INT(i)));
}

static void bc_int_nativeAdd(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = object_int_new(self->u.int_ + a->u.int_);
	PushVector(fr->value_stack, ret);
}

static void bc_int_nativeSub(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = object_int_new(self->u.int_ - a->u.int_);
	PushVector(fr->value_stack, ret);
}

static void bc_int_nativeMul(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = object_int_new(self->u.int_ * a->u.int_);
	PushVector(fr->value_stack, ret);
}

static void bc_int_nativeDiv(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = object_int_new(self->u.int_ / a->u.int_);
	PushVector(fr->value_stack, ret);
}

static void bc_int_nativeMod(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = object_int_new(self->u.int_ % a->u.int_);
	PushVector(fr->value_stack, ret);
}

static void bc_int_nativeLShift(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = object_int_new(self->u.int_ << a->u.int_);
	PushVector(fr->value_stack, ret);
}

static void bc_int_nativeRShift(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = object_int_new(self->u.int_ >> a->u.int_);
	PushVector(fr->value_stack, ret);
}

static void bc_int_nativeGT(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = GetBoolObject(self->u.int_ > a->u.int_);
	PushVector(fr->value_stack, ret);
}

static void bc_int_nativeGE(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = GetBoolObject(self->u.int_ >= a->u.int_);
	PushVector(fr->value_stack, ret);
}

static void bc_int_nativeLT(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = GetBoolObject(self->u.int_ < a->u.int_);
	PushVector(fr->value_stack, ret);
}

static void bc_int_nativeLE(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = GetBoolObject(self->u.int_ <= a->u.int_);
	PushVector(fr->value_stack, ret);
}

static void bc_int_nativeBitOr(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = object_int_new(self->u.int_ | a->u.int_);
	PushVector(fr->value_stack, ret);
}

static void bc_int_nativeBitAnd(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = object_int_new(self->u.int_ & a->u.int_);
	PushVector(fr->value_stack, ret);
}

static void bc_int_nativeEQ(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = GetBoolObject(self->u.int_ == a->u.int_);
	PushVector(fr->value_stack, ret);
}

static void bc_int_nativeToChar(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	PushVector(fr->value_stack, object_char_new(self->u.int_));
}
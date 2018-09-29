#include "bc_double.h"
#include "../../bc_library_impl.h"

//proto
static void bc_double_nativeInit(method* parent, frame* fr, enviroment* env);
static void bc_double_nativeEquals(method* parent, frame* fr, enviroment* env);
static void bc_double_nativeAdd(method* parent, frame* fr, enviroment* env);
static void bc_double_nativeSub(method* parent, frame* fr, enviroment* env);
static void bc_double_nativeMul(method* parent, frame* fr, enviroment* env);
static void bc_double_nativeDiv(method* parent, frame* fr, enviroment* env);
static void bc_double_nativeGT(method* parent, frame* fr, enviroment* env);
static void bc_double_nativeGE(method* parent, frame* fr, enviroment* env);
static void bc_double_nativeLT(method* parent, frame* fr, enviroment* env);
static void bc_double_nativeLE(method* parent, frame* fr, enviroment* env);
static void bc_double_nativeEQ(method* parent, frame* fr, enviroment* env);

void bc_double_init() {
	namespace_* lang = namespace_lang();
	type* doubleType = class_new_preload(InternString("Double"));
	class_* doubleClass = TYPE2CLASS(doubleType);
	namespace_add_type(lang, doubleType);
	class_define_native_method(doubleClass, "nativeInit", bc_double_nativeInit);
	class_define_native_method(doubleClass, "nativeEquals", bc_double_nativeEquals);
	class_define_native_method(doubleClass, "nativeAdd", bc_double_nativeAdd);
	class_define_native_method(doubleClass, "nativeSub", bc_double_nativeSub);
	class_define_native_method(doubleClass, "nativeMul", bc_double_nativeMul);
	class_define_native_method(doubleClass, "nativeDiv", bc_double_nativeDiv);
	class_define_native_method(doubleClass, "nativeGT", bc_double_nativeGT);
	class_define_native_method(doubleClass, "nativeGE", bc_double_nativeGE);
	class_define_native_method(doubleClass, "nativeLT", bc_double_nativeLT);
	class_define_native_method(doubleClass, "nativeLE", bc_double_nativeLE);
	class_define_native_method(doubleClass, "nativeEQ", bc_double_nativeEQ);
}

type* bc_double_type() {
	namespace_* lang = namespace_lang();
	return namespace_get_type(lang, InternString("Double"));
}
//private
static void bc_double_nativeInit(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* d = AtVector(fr->ref_stack, 1);

	self->u.double_ = d->u.double_;
	self->tag = OBJECT_DOUBLE_T;
}

static void bc_double_nativeEquals(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* d = AtVector(fr->ref_stack, 1);
	PushVector(fr->value_stack, BOOL2OBJ(OBJ2DOUBLE(self) == OBJ2DOUBLE(d)));
}

static void bc_double_nativeAdd(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = object_double_new(self->u.double_ + a->u.double_);
	PushVector(fr->value_stack, ret);
}

static void bc_double_nativeSub(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = object_double_new(self->u.double_ - a->u.double_);
	PushVector(fr->value_stack, ret);
}

static void bc_double_nativeMul(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = object_double_new(self->u.double_ * a->u.double_);
	PushVector(fr->value_stack, ret);
}

static void bc_double_nativeDiv(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = object_double_new(self->u.double_ / a->u.double_);
	PushVector(fr->value_stack, ret);
}

static void bc_double_nativeGT(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = object_bool_get(self->u.double_ > a->u.double_);
	PushVector(fr->value_stack, ret);
}

static void bc_double_nativeGE(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = object_bool_get(self->u.double_ >= a->u.double_);
	PushVector(fr->value_stack, ret);
}

static void bc_double_nativeLT(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = object_bool_get(self->u.double_ < a->u.double_);
	PushVector(fr->value_stack, ret);
}

static void bc_double_nativeLE(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = object_bool_get(self->u.double_ <= a->u.double_);
	PushVector(fr->value_stack, ret);
}

static void bc_double_nativeEQ(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* a = AtVector(fr->ref_stack, 1);
	object* ret = object_bool_get(self->u.double_ == a->u.double_);
	PushVector(fr->value_stack, ret);
}
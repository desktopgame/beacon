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
static type* gIntT = NULL;

void bc_int_init() {
	namespace_* lang =  namespace_lang();
	type* intType = class_new_preload(string_pool_intern("Int"));
	class_* intClass = TYPE2CLASS(intType);
	namespace_add_type(lang, intType);
	class_define_native_method(intClass, "nativeInit", bc_int_nativeInit);
	class_define_native_method(intClass, "nativeEquals", bc_int_nativeEquals);
	class_define_native_method(intClass, "nativeAdd", bc_int_nativeAdd);
	class_define_native_method(intClass, "nativeSub", bc_int_nativeSub);
	class_define_native_method(intClass, "nativeMul", bc_int_nativeMul);
	class_define_native_method(intClass, "nativeDiv", bc_int_nativeDiv);
	class_define_native_method(intClass, "nativeMod", bc_int_nativeMod);
	class_define_native_method(intClass, "nativeLShift", bc_int_nativeLShift);
	class_define_native_method(intClass, "nativeRShift", bc_int_nativeRShift);
	class_define_native_method(intClass, "nativeGT", bc_int_nativeGT);
	class_define_native_method(intClass, "nativeGE", bc_int_nativeGE);
	class_define_native_method(intClass, "nativeLT", bc_int_nativeLT);
	class_define_native_method(intClass, "nativeLE", bc_int_nativeLE);
	class_define_native_method(intClass, "nativeBitOr", bc_int_nativeBitOr);
	class_define_native_method(intClass, "nativeBitAnd", bc_int_nativeBitAnd);
	class_define_native_method(intClass, "nativeEQ", bc_int_nativeEQ);
	gIntT = intType;
}

type* bc_int_type() {
	if(gIntT != NULL) return gIntT;
	namespace_* lang = namespace_lang();
	gIntT = namespace_get_type(lang, string_pool_intern("Int"));
	return gIntT;
}
//private
static void bc_int_nativeInit(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* i = vector_at(fr->ref_stack, 1);

	self->u.int_ = i->u.int_;
	self->tag = object_int;
}

static void bc_int_nativeEquals(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* i = vector_at(fr->ref_stack, 1);
	vector_push(fr->value_stack, BOOL2OBJ(OBJ2INT(self) == OBJ2INT(i)));
}

static void bc_int_nativeAdd(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* a = vector_at(fr->ref_stack, 1);
	object* ret = object_int_new(self->u.int_ + a->u.int_);
	vector_push(fr->value_stack, ret);
}

static void bc_int_nativeSub(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* a = vector_at(fr->ref_stack, 1);
	object* ret = object_int_new(self->u.int_ - a->u.int_);
	vector_push(fr->value_stack, ret);
}

static void bc_int_nativeMul(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* a = vector_at(fr->ref_stack, 1);
	object* ret = object_int_new(self->u.int_ * a->u.int_);
	vector_push(fr->value_stack, ret);
}

static void bc_int_nativeDiv(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* a = vector_at(fr->ref_stack, 1);
	object* ret = object_int_new(self->u.int_ / a->u.int_);
	vector_push(fr->value_stack, ret);
}

static void bc_int_nativeMod(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* a = vector_at(fr->ref_stack, 1);
	object* ret = object_int_new(self->u.int_ % a->u.int_);
	vector_push(fr->value_stack, ret);
}

static void bc_int_nativeLShift(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* a = vector_at(fr->ref_stack, 1);
	object* ret = object_int_new(self->u.int_ << a->u.int_);
	vector_push(fr->value_stack, ret);
}

static void bc_int_nativeRShift(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* a = vector_at(fr->ref_stack, 1);
	object* ret = object_int_new(self->u.int_ >> a->u.int_);
	vector_push(fr->value_stack, ret);
}

static void bc_int_nativeGT(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* a = vector_at(fr->ref_stack, 1);
	object* ret = object_bool_get(self->u.int_ > a->u.int_);
	vector_push(fr->value_stack, ret);
}

static void bc_int_nativeGE(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* a = vector_at(fr->ref_stack, 1);
	object* ret = object_bool_get(self->u.int_ >= a->u.int_);
	vector_push(fr->value_stack, ret);
}

static void bc_int_nativeLT(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* a = vector_at(fr->ref_stack, 1);
	object* ret = object_bool_get(self->u.int_ < a->u.int_);
	vector_push(fr->value_stack, ret);
}

static void bc_int_nativeLE(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* a = vector_at(fr->ref_stack, 1);
	object* ret = object_bool_get(self->u.int_ <= a->u.int_);
	vector_push(fr->value_stack, ret);
}

static void bc_int_nativeBitOr(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* a = vector_at(fr->ref_stack, 1);
	object* ret = object_int_new(self->u.int_ | a->u.int_);
	vector_push(fr->value_stack, ret);
}

static void bc_int_nativeBitAnd(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* a = vector_at(fr->ref_stack, 1);
	object* ret = object_int_new(self->u.int_ & a->u.int_);
	vector_push(fr->value_stack, ret);
}

static void bc_int_nativeEQ(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* a = vector_at(fr->ref_stack, 1);
	object* ret = object_bool_get(self->u.int_ == a->u.int_);
	vector_push(fr->value_stack, ret);
}
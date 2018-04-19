#include "sg_array.h"
#include "../../sg_library_impl.h"
#include "../../../env/field.h"
#include "../../../env/constructor.h"
#include "../../../env/exception.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include <assert.h>

//proto
static void sg_array_nativeInit(method* parent, vm* vm, enviroment* env);
static void sg_array_nativeSet(method* parent, vm* vm, enviroment* env);
static void sg_array_nativeGet(method* parent, vm* vm, enviroment* env);
static void sg_array_nativeCopy(method* parent, vm* vm, enviroment* env);

static type* gSgArrayType = NULL;

void sg_array_init() {
	namespace_* lang = namespace_lang();
	class_* arrayClass = class_new_preload("Array");
	namespace_add_type(lang, type_wrap_class(arrayClass));
	class_define_native_method(arrayClass, "nativeInit", sg_array_nativeInit);
	class_define_native_method(arrayClass, "nativeSet", sg_array_nativeSet);
	class_define_native_method(arrayClass, "nativeGet", sg_array_nativeGet);
	class_define_native_method(arrayClass, "nativeCopy", sg_array_nativeCopy);
}

type * sg_array_class() {
	namespace_* lang = namespace_lang();
	return namespace_get_type(lang, "Array");
	//if (gSgArrayType == NULL) {
	//	namespace_* lang = namespace_lang();
	//	gSgArrayType = namespace_get_type(lang, "Array");
	//}
	//return gSgArrayType;
}

object * sg_array_new(int length, vm * vmc) {
	type* arrayType = sg_array_class();
	object* ret = class_new_rinstance(arrayType->u.class_, vmc, 1, object_int_new(length));
//	class_
	return ret;
}

void sg_array_set(object * arr, int index, object * o) {
	vector_assign(arr->native_slot_vec, index, o);
}

object * sg_array_get(object * arr, int index) {
	return (object*)vector_at(arr->native_slot_vec, index);
}
//private
static void sg_array_nativeInit(method* parent, vm* vm, enviroment* env) {
	type* tp = parent->parent;
	//Array#lengthを取り出す
	int temp = 0;
	field* lengthField = class_find_field(tp->u.class_, "length", &temp);
	assert(lengthField != NULL && temp != -1);
	//対応する位置のオブジェクトを取り出す
	object* self = vector_at(vm->ref_stack, 0);
	object* lengthObj = vector_at(self->u.field_vec, temp);
	assert(lengthObj != NULL);
	//配列の長さだけ確保
	int len = lengthObj->u.int_;
	assert(len >= 0);
	for (int i = 0; i < len; i++) {
		vector_push(self->native_slot_vec, object_get_null());
	}
}

static void sg_array_nativeSet(method* parent, vm* vm, enviroment* env) {
	object* self = vector_pop(vm->value_stack);
	object* idx = vector_pop(vm->value_stack);
	object* val = vector_pop(vm->value_stack);
	assert(idx->tag == object_int);
	vector_assign(self->native_slot_vec, idx->u.int_, val);
}

static void sg_array_nativeGet(method* parent, vm* vm, enviroment* env) {
	object* self = vector_pop(vm->value_stack);
	object* idx = vector_pop(vm->value_stack);
	assert(idx->tag == object_int);
	object* ret = (object*)vector_at(self->native_slot_vec, idx->u.int_);
	//text_printfln("array get %d", idx->u.int_);
	vector_push(vm->value_stack, ret);
}

static void sg_array_nativeCopy(method* parent, vm* vm, enviroment* env) {
	object* src = vector_pop(vm->value_stack);
	object* srcOffset = vector_pop(vm->value_stack);
	object* dst = vector_pop(vm->value_stack);
	object* dstOffset = vector_pop(vm->value_stack);
	object* length = vector_pop(vm->value_stack);
	int srcLen = src->native_slot_vec->length;
	int dstLen = dst->native_slot_vec->length;
	int cpyLen = length->u.int_;
	//添え字がマイナス
	if (srcOffset->u.int_ < 0 ||
		dstOffset->u.int_ < 0) {
		vm_native_throw(vm, exception_new_simplef(vm, "index must be positive: %d - %d", srcOffset->u.int_, dstOffset->u.int_));
		return;
	}
	//添え字がはみ出している
	if ((srcOffset->u.int_ + cpyLen) > srcLen ||
		(dstOffset->u.int_ + cpyLen) > dstLen) {
		vm_native_throw(vm, exception_new_simplef(vm, "index must be less than size of array: %d - %d", srcOffset->u.int_, dstOffset->u.int_));
		return;
	}
	for (int i = srcOffset->u.int_;
			 i < (srcOffset->u.int_ + length->u.int_);
			 i++) {
		int a = (i - srcOffset->u.int_) + dstOffset->u.int_;
		vector_item e = vector_at(src->native_slot_vec, i);
		vector_assign(dst->native_slot_vec, a, e);
	}
}

#include "bc_array.h"
#include "../../bc_library_impl.h"
#include "../../../env/field.h"
#include "../../../env/constructor.h"
#include "../../../env/exception.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include <assert.h>

//proto
static void bc_array_nativeInit(method* parent, frame* fr, enviroment* env);
static void bc_array_nativeSet(method* parent, frame* fr, enviroment* env);
static void bc_array_nativeGet(method* parent, frame* fr, enviroment* env);
static void bc_array_nativeCopy(method* parent, frame* fr, enviroment* env);

static type* gSgArrayType = NULL;

void bc_array_init() {
	namespace_* lang = namespace_lang();
	class_* arrayClass = class_new_preload("Array");
	namespace_add_type(lang, type_wrap_class(arrayClass));
	class_define_native_method(arrayClass, "nativeInit", bc_array_nativeInit);
	class_define_native_method(arrayClass, "nativeSet", bc_array_nativeSet);
	class_define_native_method(arrayClass, "nativeGet", bc_array_nativeGet);
	class_define_native_method(arrayClass, "nativeCopy", bc_array_nativeCopy);
}

type * bc_array_class() {
	namespace_* lang = namespace_lang();
	return namespace_get_type(lang, "Array");
}

object * bc_array_new(int length, frame * fr) {
	type* arrayType = bc_array_class();
	object* ret = class_new_rinstance(arrayType->u.class_, fr, 1, object_int_new(length));
	return ret;
}

void bc_array_set(object * arr, int index, object * o) {
	vector_assign(arr->native_slot_vec, index, o);
}

object * bc_array_get(object * arr, int index) {
	return (object*)vector_at(arr->native_slot_vec, index);
}
//private
static void bc_array_nativeInit(method* parent, frame* fr, enviroment* env) {
	type* tp = parent->parent;
	//Array#lengthを取り出す
	int temp = 0;
	field* lengthField = class_find_field(tp->u.class_, "length", &temp);
	assert(lengthField != NULL && temp != -1);
	//対応する位置のオブジェクトを取り出す
	object* self = vector_at(fr->ref_stack, 0);
	object* lengthObj = vector_at(self->u.field_vec, temp);
	assert(lengthObj != NULL);
	//配列の長さだけ確保
	int len = lengthObj->u.int_;
	assert(len >= 0);
	for (int i = 0; i < len; i++) {
		vector_push(self->native_slot_vec, object_get_null());
	}
}

static void bc_array_nativeSet(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* idx = vector_at(fr->ref_stack, 1);
	object* val = vector_at(fr->ref_stack, 2);
	assert(idx->tag == object_int);
	vector_assign(self->native_slot_vec, idx->u.int_, val);
}

static void bc_array_nativeGet(method* parent, frame* fr, enviroment* env) {
	object* self = vector_at(fr->ref_stack, 0);
	object* idx = vector_at(fr->ref_stack, 1);
//	object* a = vector_at(vm->ref_stack, 2);
	assert(idx->tag == object_int);
	object* ret = (object*)vector_at(self->native_slot_vec, idx->u.int_);
	//text_printfln("array get %d", idx->u.int_);
	vector_push(fr->value_stack, ret);
}

static void bc_array_nativeCopy(method* parent, frame* fr, enviroment* env) {
	object* src = vector_at(fr->ref_stack, 1);
	object* srcOffset = vector_at(fr->ref_stack, 2);
	object* dst = vector_at(fr->ref_stack, 3);
	object* dstOffset = vector_at(fr->ref_stack, 4);
	object* length = vector_at(fr->ref_stack, 5);
	int srcLen = src->native_slot_vec->length;
	int dstLen = dst->native_slot_vec->length;
	int cpyLen = length->u.int_;
	//添え字がマイナス
	if (srcOffset->u.int_ < 0 ||
		dstOffset->u.int_ < 0) {
		vm_native_throw(fr, exception_new_simplef(fr, "index must be positive: %d - %d", srcOffset->u.int_, dstOffset->u.int_));
		return;
	}
	//添え字がはみ出している
	if ((srcOffset->u.int_ + cpyLen) > srcLen ||
		(dstOffset->u.int_ + cpyLen) > dstLen) {
		vm_native_throw(fr, exception_new_simplef(fr, "index must be less than size of array: %d - %d", srcOffset->u.int_, dstOffset->u.int_));
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

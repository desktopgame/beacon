#include "sg_array.h"
#include "../../sg_library_impl.h"
#include "../../../env/field.h"
#include "../../../env/constructor.h"
#include <assert.h>

//proto
static void sg_array_nativeInit(method* parent, vm* vm, enviroment* env);
static void sg_array_nativeSet(method* parent, vm* vm, enviroment* env);
static void sg_array_nativeGet(method* parent, vm* vm, enviroment* env);

void sg_array_init() {
	namespace_* lang = namespace_lang();
	class_* arrayClass = class_new_preload("Array");
	namespace_add_type(lang, type_wrap_class(arrayClass));
	class_define_native_method(arrayClass, "nativeInit", sg_array_nativeInit);
	class_define_native_method(arrayClass, "nativeSet", sg_array_nativeSet);
	class_define_native_method(arrayClass, "nativeGet", sg_array_nativeGet);
}

type * sg_array_class() {
	namespace_* lang = namespace_lang();
	return namespace_get_type(lang, "Array");
}

object * sg_array_new(int length, vm * vmc) {
	type* arrayType = sg_array_class();
	object* ret = class_new_rinstance(arrayType->u.class_, vmc, 1, object_int_new(length));
	return ret;
}

void sg_array_set(object * arr, int index, object * o) {
	vector_assign(arr->nativeSlotVec, index, o);
}

object * sg_array_get(object * arr, int index) {
	return (object*)vector_at(arr->nativeSlotVec, index);
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
		vector_push(self->nativeSlotVec, object_get_null());
	}
}

static void sg_array_nativeSet(method* parent, vm* vm, enviroment* env) {
	object* self = vector_pop(vm->value_stack);
	object* val = vector_pop(vm->value_stack);
	object* idx = vector_pop(vm->value_stack);
	assert(idx->tag == object_int);
	vector_assign(self->nativeSlotVec, idx->u.int_, val);
}

static void sg_array_nativeGet(method* parent, vm* vm, enviroment* env) {
	object* self = vector_pop(vm->value_stack);
	object* idx = vector_pop(vm->value_stack);
	assert(idx->tag == object_int);
	object* ret = vector_at(self->nativeSlotVec, idx->u.int_);
	vector_push(vm->value_stack, ret);
}

#include "bc_array.h"
#include "../../bc_library_impl.h"
#include "../../../env/field.h"
#include "../../../env/constructor.h"
#include "../../../env/exception.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include <assert.h>

//proto
static void bc_array_nativeInit(method* parent, Frame* fr, Enviroment* env);
static void bc_array_nativeSet(method* parent, Frame* fr, Enviroment* env);
static void bc_array_nativeGet(method* parent, Frame* fr, Enviroment* env);
static void bc_array_nativeCopy(method* parent, Frame* fr, Enviroment* env);

void InitBCArray() {
	namespace_* lang = GetLangNamespace();
	type* arrayType = NewPreloadClass(InternString("Array"));
	class_* arrayClass = TYPE2CLASS(arrayType);
	AddTypeNamespace(lang, arrayType);
	DefineNativeMethodClass(arrayClass, "nativeInit", bc_array_nativeInit);
	DefineNativeMethodClass(arrayClass, "nativeSet", bc_array_nativeSet);
	DefineNativeMethodClass(arrayClass, "nativeGet", bc_array_nativeGet);
	DefineNativeMethodClass(arrayClass, "nativeCopy", bc_array_nativeCopy);
}

type * GetBCArrayType() {
	namespace_* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Array"));
}

object * NewBCArray(struct generic_type* gtype, int length, Frame* fr) {
	type* arrayType = GetBCArrayType();

	Vector* args = NewVector();
	Vector* type_args = NewVector();
	PushVector(args, object_int_new(length));
	PushVector(type_args, gtype);
	object* ret = NewInstanceClass(arrayType->u.class_, fr, args,type_args);
	DeleteVector(args, VectorDeleterOfNull);
	DeleteVector(type_args, VectorDeleterOfNull);

	return ret;
}

void SetBCArray(object * arr, int index, object * o) {
	AssignVector(arr->native_slot_vec, index, o);
}

object * GetBCArray(object * arr, int index) {
	return (object*)AtVector(arr->native_slot_vec, index);
}

int GetLengthBCArray(object* arr) {
	//assert(arr->tag == OBJECT_ARRAY_T);
	return arr->native_slot_vec->Length;
}
//private
static void bc_array_nativeInit(method* parent, Frame* fr, Enviroment* env) {
	type* tp = parent->parent;
	//Array#lengthを取り出す
	int temp = 0;
	field* lengthField = FindFieldClass(tp->u.class_, InternString("length"), &temp);
	assert(lengthField != NULL && temp != -1);
	//対応する位置のオブジェクトを取り出す
	object* self = AtVector(fr->ref_stack, 0);
	object* lengthObj = AtVector(self->u.field_vec, temp);
	assert(lengthObj != NULL);
	generic_type* targ = AtVector(self->gtype->type_args_list, 0);
	//配列の長さだけ確保
	int len = lengthObj->u.int_;
	assert(len >= 0);
	for (int i = 0; i < len; i++) {
		object* oe = GetDefaultObject(targ);
		PushVector(self->native_slot_vec, oe);
	}
}

static void bc_array_nativeSet(method* parent, Frame* fr, Enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* idx = AtVector(fr->ref_stack, 1);
	object* val = AtVector(fr->ref_stack, 2);
	assert(idx->tag == OBJECT_INT_T);
	AssignVector(self->native_slot_vec, idx->u.int_, val);
}

static void bc_array_nativeGet(method* parent, Frame* fr, Enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	object* idx = AtVector(fr->ref_stack, 1);
//	object* a = AtVector(vm->ref_stack, 2);
	assert(idx->tag == OBJECT_INT_T);
	object* ret = (object*)AtVector(self->native_slot_vec, idx->u.int_);
	//Printfln("array get %d", idx->u.int_);
	PushVector(fr->value_stack, ret);
}

static void bc_array_nativeCopy(method* parent, Frame* fr, Enviroment* env) {
	object* src = AtVector(fr->ref_stack, 1);
	object* srcOffset = AtVector(fr->ref_stack, 2);
	object* dst = AtVector(fr->ref_stack, 3);
	object* dstOffset = AtVector(fr->ref_stack, 4);
	object* length = AtVector(fr->ref_stack, 5);
	int srcLen = src->native_slot_vec->Length;
	int dstLen = dst->native_slot_vec->Length;
	int cpyLen = length->u.int_;
	//添え字がマイナス
	if (srcOffset->u.int_ < 0 ||
		dstOffset->u.int_ < 0) {
		NativeThrowVM(fr, NewSimplefException(fr, "index must be positive: %d - %d", srcOffset->u.int_, dstOffset->u.int_));
		return;
	}
	//添え字がはみ出している
	if ((srcOffset->u.int_ + cpyLen) > srcLen ||
		(dstOffset->u.int_ + cpyLen) > dstLen) {
		NativeThrowVM(fr, NewSimplefException(fr, "index must be less than size of array: %d - %d", srcOffset->u.int_, dstOffset->u.int_));
		return;
	}
	for (int i = srcOffset->u.int_;
			 i < (srcOffset->u.int_ + length->u.int_);
			 i++) {
		int a = (i - srcOffset->u.int_) + dstOffset->u.int_;
		VectorItem e = AtVector(src->native_slot_vec, i);
		AssignVector(dst->native_slot_vec, a, e);
	}
}

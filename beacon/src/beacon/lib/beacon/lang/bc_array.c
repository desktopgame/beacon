#include "bc_array.h"
#include "../../bc_library_impl.h"
#include "../../../env/field.h"
#include "../../../env/constructor.h"
#include "../../../env/exception.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include <assert.h>

//proto
static void bc_array_nativeInit(Method* parent, Frame* fr, Enviroment* env);
static void bc_array_nativeSet(Method* parent, Frame* fr, Enviroment* env);
static void bc_array_nativeGet(Method* parent, Frame* fr, Enviroment* env);
static void bc_array_nativeCopy(Method* parent, Frame* fr, Enviroment* env);

void InitBCArray() {
	Namespace* lang = GetLangNamespace();
	type* arrayType = NewPreloadClass(InternString("Array"));
	class_* arrayClass = TYPE2CLASS(arrayType);
	AddTypeNamespace(lang, arrayType);
	DefineNativeMethodClass(arrayClass, "nativeInit", bc_array_nativeInit);
	DefineNativeMethodClass(arrayClass, "nativeSet", bc_array_nativeSet);
	DefineNativeMethodClass(arrayClass, "nativeGet", bc_array_nativeGet);
	DefineNativeMethodClass(arrayClass, "nativeCopy", bc_array_nativeCopy);
}

type * GetBCArrayType() {
	Namespace* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Array"));
}

Object * NewBCArray(struct GenericType* gtype, int length, Frame* fr) {
	type* arrayType = GetBCArrayType();

	Vector* args = NewVector();
	Vector* type_args = NewVector();
	PushVector(args, Object_int_new(length));
	PushVector(type_args, gtype);
	Object* ret = NewInstanceClass(arrayType->u.class_, fr, args,type_args);
	DeleteVector(args, VectorDeleterOfNull);
	DeleteVector(type_args, VectorDeleterOfNull);

	return ret;
}

void SetBCArray(Object * arr, int index, Object * o) {
	AssignVector(arr->NativeSlotVec, index, o);
}

Object * GetBCArray(Object * arr, int index) {
	return (Object*)AtVector(arr->NativeSlotVec, index);
}

int GetLengthBCArray(Object* arr) {
	//assert(arr->tag == OBJECT_ARRAY_T);
	return arr->NativeSlotVec->Length;
}
//private
static void bc_array_nativeInit(Method* parent, Frame* fr, Enviroment* env) {
	type* tp = parent->Parent;
	//Array#lengthを取り出す
	int temp = 0;
	Field* lengthField = FindFieldClass(tp->u.class_, InternString("length"), &temp);
	assert(lengthField != NULL && temp != -1);
	//対応する位置のオブジェクトを取り出す
	Object* self = AtVector(fr->VariableTable, 0);
	Object* lengthObj = AtVector(self->u.field_vec, temp);
	assert(lengthObj != NULL);
	GenericType* targ = AtVector(self->GType->TypeArgs, 0);
	//配列の長さだけ確保
	int len = lengthObj->u.int_;
	assert(len >= 0);
	for (int i = 0; i < len; i++) {
		Object* oe = GetDefaultObject(targ);
		PushVector(self->NativeSlotVec, oe);
	}
}

static void bc_array_nativeSet(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* idx = AtVector(fr->VariableTable, 1);
	Object* val = AtVector(fr->VariableTable, 2);
	assert(idx->Tag == OBJECT_INT_T);
	AssignVector(self->NativeSlotVec, idx->u.int_, val);
}

static void bc_array_nativeGet(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* idx = AtVector(fr->VariableTable, 1);
//	Object* a = AtVector(vm->VariableTable, 2);
	assert(idx->Tag == OBJECT_INT_T);
	Object* ret = (Object*)AtVector(self->NativeSlotVec, idx->u.int_);
	//Printfln("array get %d", idx->u.int_);
	PushVector(fr->ValueStack, ret);
}

static void bc_array_nativeCopy(Method* parent, Frame* fr, Enviroment* env) {
	Object* src = AtVector(fr->VariableTable, 1);
	Object* srcOffset = AtVector(fr->VariableTable, 2);
	Object* dst = AtVector(fr->VariableTable, 3);
	Object* dstOffset = AtVector(fr->VariableTable, 4);
	Object* length = AtVector(fr->VariableTable, 5);
	int srcLen = src->NativeSlotVec->Length;
	int dstLen = dst->NativeSlotVec->Length;
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
		VectorItem e = AtVector(src->NativeSlotVec, i);
		AssignVector(dst->NativeSlotVec, a, e);
	}
}

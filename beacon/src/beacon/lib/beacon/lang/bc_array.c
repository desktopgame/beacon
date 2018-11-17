#include "bc_array.h"
#include "../../bc_library_interface.h"
#include "../../bc_library_impl.h"
#include "../../../env/field.h"
#include "../../../env/constructor.h"
#include "../../../env/exception.h"
#include "../../../util/text.h"
#include "../../../util/mem.h"
#include "../../../env/generic_type.h"
#include <assert.h>

//proto
static void* handle_obj_message(Object* self, ObjectMessage msg, int argc, ObjectMessageArgument argv[]);
static void bc_array_nativeInit(Method* parent, Frame* fr, Enviroment* env);
static void bc_array_nativeSet(Method* parent, Frame* fr, Enviroment* env);
static void bc_array_nativeGet(Method* parent, Frame* fr, Enviroment* env);
static void bc_array_nativeCopy(Method* parent, Frame* fr, Enviroment* env);
static void delete_self(VectorItem item);

Object* NewArray(int size, GenericType* element_type) {
	//Array[T]を作成する
	GenericType* array_type = NewGenericType(GetArrayType());
	AddArgsGenericType(array_type, element_type);
	Array* ret = ConstructObject(sizeof(Array), array_type);
	ret->Super.OnMessage = handle_obj_message;
	ret->Elements = NewVector();
	for(int i=0; i<size; i++) {
		PushVector(ret->Elements,GetNullObject());
	}
	return (Object*)ret;
}

void InitArray() {
	Namespace* lang = GetLangNamespace();
	Type* arrayType = NewPreloadClass(InternString("Array"));
	Class* arrayClass = TYPE2CLASS(arrayType);
	arrayType->AllocSize = sizeof(Array);
	AddTypeNamespace(lang, arrayType);
	DefineNativeMethodClass(arrayClass, "nativeInit", bc_array_nativeInit);
	DefineNativeMethodClass(arrayClass, "nativeSet", bc_array_nativeSet);
	DefineNativeMethodClass(arrayClass, "nativeGet", bc_array_nativeGet);
	DefineNativeMethodClass(arrayClass, "nativeCopy", bc_array_nativeCopy);
}

Type* GetArrayType() {
	Namespace* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Array"));
}

Object * DynamicNewArray(struct GenericType* gtype, int length, Frame* fr) {
	Type* arrayType = GetArrayType();

	Vector* args = NewVector();
	Vector* type_args = NewVector();
	PushVector(args, NewInteger(length));
	PushVector(type_args, gtype);
	Object* ret = NewInstanceClass(arrayType->Kind.Class, fr, args,type_args);
	DeleteVector(args, VectorDeleterOfNull);
	DeleteVector(type_args, VectorDeleterOfNull);

	return ret;
}

#define ARRAY_VALUE(obj) (((Array*)obj)->Elements)
void SetElementAt(Object * arr, int index, Object * o) {
	AssignVector(ARRAY_VALUE(arr), index, o);
}

Object * GetElementAt(Object * arr, int index) {
	return (Object*)AtVector(ARRAY_VALUE(arr), index);
}

int GetArrayLength(Object* arr) {
	//assert(arr->tag == OBJECT_ARRAY_T);
	return ARRAY_VALUE(arr)->Length;
}
//private
static void* handle_obj_message(Object* self, ObjectMessage msg, int argc, ObjectMessageArgument argv[]) {
	if(msg == OBJECT_MSG_MARKALL) {
		assert(argc == 1);
		HandleObjectMessage(self, msg, argc, argv);
		Vector* values = ARRAY_VALUE(self);
		for(int i=0; i<values->Length; i++) {
			PaintAllObject((Object*)AtVector(values, i), argv[0].Int);
		}
		return NULL;
	} else if (msg == OBJECT_MSG_DELETE) {
		DeleteVector(self->Fields, VectorDeleterOfNull);
		DeleteVector(ARRAY_VALUE(self), VectorDeleterOfNull);
		MEM_FREE(self);
		return NULL;
	} else if(msg == OBJECT_MSG_DESTROY) {
		DeleteVector(self->Fields, delete_self);
		DeleteVector(ARRAY_VALUE(self), delete_self);
		self->Fields = NULL;
		ARRAY_VALUE(self) = NULL;
		DeleteObject(self);
		return NULL;
	} else if (msg == OBJECT_MSG_PRINT) {
		printf("Array:%d", ARRAY_VALUE(self)->Length);
		return NULL;
	} else {
		return HandleObjectMessage(self, msg, argc, argv);
	}
}

static void bc_array_nativeInit(Method* parent, Frame* fr, Enviroment* env) {
	Type* tp = parent->Parent;
	//Array#lengthを取り出す
	int temp = 0;
	Field* lengthField = FindFieldClass(tp->Kind.Class, InternString("length"), &temp);
	assert(lengthField != NULL && temp != -1);
	//対応する位置のオブジェクトを取り出す
	Array* self = (Array*)AtVector(fr->VariableTable, 0);
	Object* lengthObj = AtVector(self->Super.Fields, temp);
	self->Super.OnMessage = handle_obj_message;
	assert(lengthObj != NULL);
	assert(self->Elements == NULL);
	self->Elements = NewVector();
	GenericType* targ = AtVector(self->Super.GType->TypeArgs, 0);
	//配列の長さだけ確保
	int len = ObjectToInt(lengthObj);
	assert(len >= 0);
	for (int i = 0; i < len; i++) {
		Object* oe = GetDefaultObject(targ);
		PushVector(ARRAY_VALUE(self), oe);
	}
}

static void bc_array_nativeSet(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* idx = AtVector(fr->VariableTable, 1);
	Object* val = AtVector(fr->VariableTable, 2);
	assert(IsIntValue(idx));
	AssignVector(ARRAY_VALUE(self), ObjectToInt(idx), val);
}

static void bc_array_nativeGet(Method* parent, Frame* fr, Enviroment* env) {
	Object* self = AtVector(fr->VariableTable, 0);
	Object* idx = AtVector(fr->VariableTable, 1);
//	Object* a = AtVector(vm->VariableTable, 2);
	assert(IsIntValue(idx));
	Object* ret = (Object*)AtVector(ARRAY_VALUE(self), ObjectToInt(idx));
	//Printfln("array get %d", idx->u.int_);
	PushVector(fr->ValueStack, ret);
}

static void bc_array_nativeCopy(Method* parent, Frame* fr, Enviroment* env) {
	Object* src = AtVector(fr->VariableTable, 1);
	Object* srcOffset = AtVector(fr->VariableTable, 2);
	Object* dst = AtVector(fr->VariableTable, 3);
	Object* dstOffset = AtVector(fr->VariableTable, 4);
	Object* length = AtVector(fr->VariableTable, 5);
	int srcLen = ARRAY_VALUE(src)->Length;
	int dstLen = ARRAY_VALUE(dst)->Length;
	int cpyLen = ObjectToInt(length);
	//添え字がマイナス
	if (ObjectToInt(srcOffset) < 0 ||
		ObjectToInt(dstOffset) < 0) {
		NativeThrowVM(fr, NewSimplefException(fr, "index must be positive: %d - %d", ObjectToInt(srcOffset),ObjectToInt(dstOffset)));
		return;
	}
	//添え字がはみ出している
	if ((ObjectToInt(srcOffset) + cpyLen) > srcLen ||
		(ObjectToInt(dstOffset) + cpyLen) > dstLen) {
		NativeThrowVM(fr, NewSimplefException(fr, "index must be less than size of array: %d - %d", ObjectToInt(srcOffset), ObjectToInt(dstOffset)));
		return;
	}
	for (int i = ObjectToInt(srcOffset);
			 i < (ObjectToInt(srcOffset) + ObjectToInt(length));
			 i++) {
		int a = (i - ObjectToInt(srcOffset)) + ObjectToInt(dstOffset);
		VectorItem e = AtVector(ARRAY_VALUE(src), i);
		AssignVector(ARRAY_VALUE(dst), a, e);
	}
}

static void delete_self(VectorItem item) {
	Object* e = (Object*)item;
	DestroyObject(e);
}
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
static void* handle_obj_message(bc_Object* self, bc_ObjectMessage msg, int argc, bc_ObjectMessageArgument argv[]);
static void bc_array_nativeInit(bc_Method* parent, Frame* fr, Enviroment* env);
static void bc_array_nativeSet(bc_Method* parent, Frame* fr, Enviroment* env);
static void bc_array_nativeGet(bc_Method* parent, Frame* fr, Enviroment* env);
static void bc_array_nativeCopy(bc_Method* parent, Frame* fr, Enviroment* env);
static void delete_self(VectorItem item);

bc_Object* NewArray(int size, bc_GenericType* element_type) {
	//Array[T]を作成する
	bc_GenericType* array_type = bc_NewGenericType(GetArrayType());
	bc_AddArgsGenericType(array_type, element_type);
	Array* ret = bc_ConstructObject(sizeof(Array), array_type);
	ret->Super.OnMessage = handle_obj_message;
	ret->Elements = NewVector();
	for(int i=0; i<size; i++) {
		PushVector(ret->Elements,bc_GetNullObject());
	}
	return (bc_Object*)ret;
}

void InitArray() {
	bc_Namespace* lang = bc_GetLangNamespace();
	bc_Type* arrayType = bc_NewPreloadClass(InternString("Array"));
	bc_Class* arrayClass = BC_TYPE2CLASS(arrayType);
	arrayType->AllocSize = sizeof(Array);
	bc_AddTypeNamespace(lang, arrayType);
	bc_DefineNativeMethodClass(arrayClass, "nativeInit", bc_array_nativeInit);
	bc_DefineNativeMethodClass(arrayClass, "nativeSet", bc_array_nativeSet);
	bc_DefineNativeMethodClass(arrayClass, "nativeGet", bc_array_nativeGet);
	bc_DefineNativeMethodClass(arrayClass, "nativeCopy", bc_array_nativeCopy);
}

bc_Type* GetArrayType() {
	bc_Namespace* lang = bc_GetLangNamespace();
	return bc_FindTypeFromNamespace(lang, InternString("Array"));
}

bc_Object * DynamicNewArray(struct bc_GenericType* gtype, int length, Frame* fr) {
	bc_Type* arrayType = GetArrayType();

	Vector* args = NewVector();
	Vector* type_args = NewVector();
	PushVector(args, NewInteger(length));
	PushVector(type_args, gtype);
	bc_Object* ret = bc_NewInstanceClass(arrayType->Kind.Class, fr, args,type_args);
	DeleteVector(args, VectorDeleterOfNull);
	DeleteVector(type_args, VectorDeleterOfNull);

	return ret;
}

#define ARRAY_VALUE(obj) (((Array*)obj)->Elements)
void SetElementAt(bc_Object * arr, int index, bc_Object * o) {
	AssignVector(ARRAY_VALUE(arr), index, o);
}

bc_Object * GetElementAt(bc_Object * arr, int index) {
	return (bc_Object*)AtVector(ARRAY_VALUE(arr), index);
}

int GetArrayLength(bc_Object* arr) {
	//assert(arr->tag == OBJECT_ARRAY_T);
	return ARRAY_VALUE(arr)->Length;
}
//private
static void* handle_obj_message(bc_Object* self, bc_ObjectMessage msg, int argc, bc_ObjectMessageArgument argv[]) {
	if(msg == OBJECT_MSG_MARKALL) {
		assert(argc == 1);
		bc_HandleObjectMessage(self, msg, argc, argv);
		Vector* values = ARRAY_VALUE(self);
		for(int i=0; i<values->Length; i++) {
			bc_PaintAllObject((bc_Object*)AtVector(values, i), argv[0].Int);
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
		bc_DeleteObject(self);
		return NULL;
	} else if (msg == OBJECT_MSG_PRINT) {
		printf("Array:%d", ARRAY_VALUE(self)->Length);
		return NULL;
	} else {
		return bc_HandleObjectMessage(self, msg, argc, argv);
	}
}

static void bc_array_nativeInit(bc_Method* parent, Frame* fr, Enviroment* env) {
	bc_Type* tp = parent->Parent;
	//Array#lengthを取り出す
	int temp = 0;
	bc_Field* lengthField = bc_FindFieldClass(tp->Kind.Class, InternString("length"), &temp);
	assert(lengthField != NULL && temp != -1);
	//対応する位置のオブジェクトを取り出す
	Array* self = (Array*)AtVector(fr->VariableTable, 0);
	bc_Object* lengthObj = AtVector(self->Super.Fields, temp);
	self->Super.OnMessage = handle_obj_message;
	assert(lengthObj != NULL);
	assert(self->Elements == NULL);
	self->Elements = NewVector();
	bc_GenericType* targ = AtVector(self->Super.GType->TypeArgs, 0);
	//配列の長さだけ確保
	int len = bc_ObjectToInt(lengthObj);
	assert(len >= 0);
	for (int i = 0; i < len; i++) {
		bc_Object* oe = bc_GetDefaultObject(targ);
		PushVector(ARRAY_VALUE(self), oe);
	}
}

static void bc_array_nativeSet(bc_Method* parent, Frame* fr, Enviroment* env) {
	bc_Object* self = AtVector(fr->VariableTable, 0);
	bc_Object* idx = AtVector(fr->VariableTable, 1);
	bc_Object* val = AtVector(fr->VariableTable, 2);
	assert(bc_IsIntValue(idx));
	AssignVector(ARRAY_VALUE(self), bc_ObjectToInt(idx), val);
}

static void bc_array_nativeGet(bc_Method* parent, Frame* fr, Enviroment* env) {
	bc_Object* self = AtVector(fr->VariableTable, 0);
	bc_Object* idx = AtVector(fr->VariableTable, 1);
//	Object* a = AtVector(vm->VariableTable, 2);
	assert(bc_IsIntValue(idx));
	bc_Object* ret = (bc_Object*)AtVector(ARRAY_VALUE(self), bc_ObjectToInt(idx));
	//bc_Printfln("array get %d", idx->u.int_);
	PushVector(fr->ValueStack, ret);
}

static void bc_array_nativeCopy(bc_Method* parent, Frame* fr, Enviroment* env) {
	bc_Object* src = AtVector(fr->VariableTable, 1);
	bc_Object* srcOffset = AtVector(fr->VariableTable, 2);
	bc_Object* dst = AtVector(fr->VariableTable, 3);
	bc_Object* dstOffset = AtVector(fr->VariableTable, 4);
	bc_Object* length = AtVector(fr->VariableTable, 5);
	int srcLen = ARRAY_VALUE(src)->Length;
	int dstLen = ARRAY_VALUE(dst)->Length;
	int cpyLen = bc_ObjectToInt(length);
	//添え字がマイナス
	if (bc_ObjectToInt(srcOffset) < 0 ||
		bc_ObjectToInt(dstOffset) < 0) {
		NativeThrowVM(fr, bc_NewSimplefException(fr, "index must be positive: %d - %d", bc_ObjectToInt(srcOffset),bc_ObjectToInt(dstOffset)));
		return;
	}
	//添え字がはみ出している
	if ((bc_ObjectToInt(srcOffset) + cpyLen) > srcLen ||
		(bc_ObjectToInt(dstOffset) + cpyLen) > dstLen) {
		NativeThrowVM(fr, bc_NewSimplefException(fr, "index must be less than size of array: %d - %d", bc_ObjectToInt(srcOffset), bc_ObjectToInt(dstOffset)));
		return;
	}
	for (int i = bc_ObjectToInt(srcOffset);
			 i < (bc_ObjectToInt(srcOffset) + bc_ObjectToInt(length));
			 i++) {
		int a = (i - bc_ObjectToInt(srcOffset)) + bc_ObjectToInt(dstOffset);
		VectorItem e = AtVector(ARRAY_VALUE(src), i);
		AssignVector(ARRAY_VALUE(dst), a, e);
	}
}

static void delete_self(VectorItem item) {
	bc_Object* e = (bc_Object*)item;
	bc_DestroyObject(e);
}